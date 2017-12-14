LIBS = -I/usr/local/lib/ 
CFLAGS = -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_imgcodecs -lopencv_features2d -lopencv_videoio
objects= main.o GPIOClass.o

picam: $(objects) 
	g++ $(objects) -o picam $(LIBS)$(CFLAGS)

main.o: main.cpp GPIOClass.h
	g++ main.cpp -c
	
GPIOClass.o: GPIOClass.cpp GPIOClass.h
	g++ GPIOClass.cpp -c
	
.PHONY: clean
clean:
	rm picam $(objects)
