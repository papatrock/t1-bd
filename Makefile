CFLAGS = -Wall -g -Wbad-function-cast \
	  -Wmissing-prototypes \
	  -Wnested-externs \
	  -Wold-style-definition \
	  -Wstrict-prototypes \
	  -Wwrite-strings

PROGRAM = escalona

Objs = escalona.o queue.o seriabilidade.o visao-equivalente.o

all: escalona

debug: clean
	make CFLAGS="$(CFLAGS) -DDEBUG" all

escalona: $(Objs)
	gcc $(Objs) $(CFLAGS) -o escalona

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

seriabilidade.o: seriabilidade.c seriabilidade.h
	gcc $(CFLAGS) -c seriabilidade.c

visao-equivalente.o: visao-equivalente.c visao-equivalente.h
	gcc $(CFLAGS) -c visao-equivalente.c


clean:
	rm -rf *~ *.o

purge: clean
	rm -rf escalona