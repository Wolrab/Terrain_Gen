FLAGS=-Wall -pedantic

LIBS=-lGL -lglut -lGLEW

IDIR=include
SDIR=src

SRC=${wildcard ${SDIR}/*.cpp}
OUT=world_gen

${OUT}: ${SRC}
	g++ -I${IDIR} -o $@ $^ ${FLAGS} ${LIBS}

clean:
	rm world_gen