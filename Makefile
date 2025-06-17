CFLAGS = -Wall -g

PROGRAM = escalona

Objs = escalona.o queue.o

all: escalona

debug: clean
	make CFLAGS="$(CFLAGS) -DDEBUG" all

escalona: $(Objs)
	gcc $(Objs) $(CFLAGS) -o escalona

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c


clean:
	rm -rf *~ *.o

purge: clean
	rm -rf escalona