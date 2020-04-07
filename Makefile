C = gcc
CFLAGS = -g
TARGET : example.out

OBJS = gluethread/glthread.o graph.o topologies.o

example.out : example.o ${OBJS}
	${CC} ${CFLAGS} example.o ${OBJS} -o example.out 

example.o : example.c
	${CC} ${CFLAGS} -c example.c -o example.o

gluethread/glthread.o : gluethread/glthread.c
	${CC} ${CFLAGS} -c -I gluethread gluethread/glthread.c -o \
	gluethread/glthread.o

graph.o : graph.c
	${CC} ${CFLAGS} -c -I . graph.c -o graph.o

topologies.o : topologies.c
	${CC} ${CFLAGS} -c -I . topologies.c -o topologies.o

clean:
	rm *.o
	rm gluethread/glthread.o
	rm *.out
				
