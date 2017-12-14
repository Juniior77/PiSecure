#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp" 
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <cstdio>
#include <ctime>
#include "GPIOClass.h"

#define FIABILITE 8
#define STOP_RECORD 10

using namespace std;
using namespace cv;

/** Function Headers */
void showVideo(Mat frame);
void enregistrementFormatAvi();
bool dectetionHumain( Mat frame);

/** Global variables */
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
 
bool mouvement = false;
int countFiabilite = 0;
bool enregistrement = false;
int countStop = 0;
time_t start = time(0);

//**********************************************************************
//Fonction principale, 
//**********************************************************************
int main(int argc,char **argv) 
{     
	Mat rawMat;
    cvNamedWindow("Capture Frame",1);
    
    
    //Chargement des xml haarcascade, si erreur, on quit le programme avec code -1
    if( !face_cascade.load( face_cascade_name ) ){ cout << "Problème lors du chargement du fichier xml: haarcascade_frontalface_alt.xml" << endl; return -1; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ cout << "Problème lors du chargement du fichier xml: haarcascade_eye_tree_eyeglasses.xml" << endl; return -1; };
   
    string inputstate;
    GPIOClass* gpio7 = new GPIOClass("7"); //create new GPIO object to be attached to  GPIO7
    gpio7->export_gpio(); //export GPIO7
    cout << " GPIO pins exported" << endl;
    gpio7->setdir_gpio("in"); //GPIO7 set to iutput
    cout << " Set GPIO pin directions" << endl;
   
	VideoCapture capture;
	capture.open("http://127.0.0.1:8080/");

	//Ouverture du flux, si erreur, on quit le programme avec code -10
	if(!capture.isOpened()){
		//Erreur d'ouverture du flux
		cout << "Problème d'ouverture du flux video" << endl;
		return -10;
	}
   
	while(1)
    {
        //usleep(2000000);  // Attend pendant 2seconde
        gpio7->getval_gpio(inputstate); //Lit l'etat du GPIO 17
        cout << "Etat GPIO: " << inputstate << endl;
        capture.read(rawMat);
        //imshow("Capture Frame", rawMat);
 //       if((cvWaitKey(1) & 255) == 27 ) break;  
        if(inputstate == "1") // if input pin is at state "0" i.e. button pressed
        {
			mouvement = true;
            cout << "Mouvement repérée, on fait une analyse OpenCV !"<<endl;
            
            while(mouvement == true)
            {
				if(!capture.read(rawMat)){
					//Erreur de capture du flux
					//cout << "Erreur de capture du flux !"<<endl;
					return -11;
				}
				imshow("Capture Frame", rawMat);
				if(dectetionHumain(rawMat)){
					cout << "Humain detecté !" << endl;
					if(countFiabilite >= FIABILITE){
						enregistrement = true;
						cout << "On enregistre !!!" << endl;
						countFiabilite = 0;
						std::system("python3 smsFree.py");
						start = time(0);
						enregistrementFormatAvi();
						break;
					}
					countFiabilite++;
						
				}
				else{
					/*countStop ++;
					if(countStop >= STOP_RECORD){
						countStop = 0;
						mouvement = false;
						enregistrement = false;
						break;
					}*/
					countFiabilite = 0;
					cout << "Fausse alerte !" << endl;
					break;
				}
				if((cvWaitKey(1) & 255) == 27 ) break;  
			}
        }
        else
        {
			cout << "La maison est vide :)"<<endl;
		}
		imshow("Capture Frame", rawMat);
		if((cvWaitKey(1) & 255) == 27 ) break;  
    }
}
//**********************************************************************
//Affiche la frame dans la fenetre openCv (Pour DEBUG)
//**********************************************************************
void showVideo(Mat frame)
{
  imshow( "Capture Frame", frame );
}

//**********************************************************************
//Enregitrement du flux sur un fichier nommer par la date de l'event
//**********************************************************************
void enregistrementFormatAvi(){

	//On genere un String contenant la date et l'heure
	//time_t mTime;
	//time(&mTime);
	//String mNameTime = ctime(&mTime);
	
	std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
    String mNameTime = buffer;
	//cout << mNameTime << endl;
	
	//On modifier le fichier "video.php"
	std::ofstream file;
	file.open("/var/www/html/video.php", std::ios_base::app);

	//Modification du fichier php
	file << "<div class=\"jumbotron\">" << endl;
	file << "<center>" << endl;
	file <<	"<h3>Video: "+mNameTime+"</h3>" << endl;
	file << "<embed type=\"application/x-vlc-plugin\"" << endl;
    file << "name=\"video"+mNameTime+"\"" << endl;
    file << "autoplay=\"yes\" loop=\"no\" width=\"480\" height=\"320\"" << endl;
    file << "target=\"/video/"+mNameTime+".avi\" />" << endl;
    file << "<br />" << endl;
    file << "<br />" << endl;
    file << "<button type=\"button\" class=\"btn btn-primary\" href=\"/video/"+mNameTime+".avi\">Telecharger</button>" << endl;
    file << "</center>" << endl;
	file << "</div>" << endl;

	file.close();
	
	VideoCapture captureEnr;
	captureEnr.open("http://127.0.0.1:8080/");

	//Ouverture du flux, si erreur, on quit le programme avec code -10
	if(!captureEnr.isOpened()){
		//Erreur d'ouverture du flux
		cout << "Problème d'ouverture du flux video" << endl;
	}
	
	//On recupere la taille largeur et hauteur de notre flux video
	double dWidth = captureEnr.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = captureEnr.get(CV_CAP_PROP_FRAME_HEIGHT);
	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
	
	VideoWriter video("/var/www/html/video/"+mNameTime+".avi", CV_FOURCC('M','J','P','G'),25,frameSize,true);
	
	Mat frame;
	
	while(enregistrement == true){
		if(!captureEnr.read(frame)){
			cout << "Erreur lors de la lecture du flux video" << endl;
		}
		video.write(frame);
		if ( difftime( time(0), start) >= 30) break;
	}
	video.release();
	std::system("python3 smsFreeVideo.py");
	cout << "Enregistrement terminé !" << endl;
	usleep(2000000);  // Attend pendant 2seconde
} 
//**********************************************************************
//Detection d'humain avec algo haarcascade
//**********************************************************************
bool dectetionHumain( Mat frame)
{
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
  
  //cout <<"Etat faces: " << faces.size() << endl;
  if(faces.size() > 0)
  {
	  return true;
  }
  /*for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 255, 255 ), 4, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );
  }*/
  return false;
 }
