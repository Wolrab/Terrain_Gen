FLAGS=-Wall -pedantic

LIBS=-lGL -lglut -lGLEW

IDIR=include
SDIR=src

SRC=${wildcard ${SDIR}/*.cpp}
OUT=biggly_graphics

${OUT}: ${SRC}
	g++ -I${IDIR} -o $@ $^ ${FLAGS} ${LIBS}

clean:
	rm biggly_graphics