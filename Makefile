FLAGS=-Wall -pedantic
LIBS=-lGL -lGLU -lglut -lGLEW
IDIR=include
SDIR=src
OUT=biggly_graphics

${OUT}: ${SDIR}/*.cpp
	g++ -o $@ $< ${FLAGS} ${LIBS}

clean:
	rm biggly_graphics