#which comliler
CC=g++
#where are lib filename
LIB=-framework OpenGL -framework GLUT -framework Foundation
OpenGL: OpenGL.o
	${CC} -o OpenGL OpenGL.o ${LIB}
OpenGL.o: OpenGL.cpp
	$(CC) -c OpenGL.cpp -o OpenGL.o $(LIB)
clean:
	rm -rf *.o

