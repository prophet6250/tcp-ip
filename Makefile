C = gcc
CFLAGS = -g -lm
TARGET : main.exe

OBJS = gluethread/glthread.o graph.o topologies.o net.o utils.o 

main.exe : main.o ${OBJS}
	${CC} ${CFLAGS} main.o ${OBJS} -o main.exe

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

utils.o: utils.c
	$(CC) $(CFLAGS) -c -I . utils.c -o utils.o

clean:
	rm *.o
	rm gluethread/glthread.o
	rm *.exe
				
