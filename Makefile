C = gcc
CFLAGS = -g
TARGET : main.out

OBJS = gluethread/glthread.o graph.o topologies.o net.o

main.out : main.o ${OBJS}
	${CC} ${CFLAGS} main.o ${OBJS} -o main.out 

main.o : main.c
	${CC} ${CFLAGS} -c main.c -o main.o

gluethread/glthread.o : gluethread/glthread.c
	${CC} ${CFLAGS} -c -I gluethread gluethread/glthread.c -o \
	gluethread/glthread.o

graph.o : graph.c
	${CC} ${CFLAGS} -c -I . graph.c -o graph.o

topologies.o : topologies.c
	${CC} ${CFLAGS} -c -I . topologies.c -o topologies.o

net.o: net.c
	$(CC) $(CFLAGS) -c -I . net.c -o net.o

clean:
	rm *.o
	rm gluethread/glthread.o
	rm *.out
				
