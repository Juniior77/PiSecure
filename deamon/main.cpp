#include <cstdlib>
#include <iostream>

int main(){
	std::cout << "Lancement du deamon PiSecure !" << std::endl;
	int code_retour = std::system("raspivid -o - -t 9999999 -w 480 -h 320 -fps 25 --hflip | cvlc -vvv stream:///dev/stdin --sout '#standard{access=http,mux=ts,dst=:8080}' :demux=h264");
	std::cout << "Le deamon est en cours d'execution !" << code_retour << std::endl;
	return EXIT_SUCCESS;
	
}
