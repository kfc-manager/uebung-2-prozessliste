CC=gcc
AR=ar
TARGET=proctable
CFLAGS= -Wall -pedantic -Wextra

all: proctable.o dl_proc_list.a
	${CC} ${CFLAGS} $^ -o ${TARGET}

%.a: %.o
	${AR} rc $@ $^

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o *.a ${TARGET}

