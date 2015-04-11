CC=g++

CFLAGS= -c -I/usr/local/include/opencv

LIB= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lopencv_highgui -lopencv_videoio -lopencv_core -lopencv_imgproc -lopencv_imgcodecs


all: HolyGrail clean
	

HolyGrail: cube.o
	$(CC) cube.o -o HolyGrail $(LIB)


main.o: cube.cpp
	$(CC) $(CFLAGS) cube.cpp 


clean:
	rm -rf *.o 
