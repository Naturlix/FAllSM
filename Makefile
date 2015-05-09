CC=g++

CFLAGS= -c -I/usr/local/include/opencv -I/usr/local/include/Box2D

LIB= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lopencv_highgui -lopencv_videoio -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lBox2D


all: box2d clean

box2d: main.o
	$(CC) main.o -o box2d $(LIB)


main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp 


clean:
	rm -rf *.o 
