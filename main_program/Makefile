#macros:
CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99

qsolve: qsolve.o qsolve.h
	${CC} ${CFLAGS} -o qsolve qsolve.c -lm

qsolve.o: qsolve.h

t1: t1.o qsolve.o cunit.o
	${CC} -o t1 t1.o qsolve.o cunit.o -lm

test: t1
	./t1

touch:
	touch *.h
#make ignores the returned status on commands that begin with a dash so that make won't terminate if the command returns a failure status; in this example, who cares if there is no core file?
clean:
	rm -f *.o core qsolve

#each shell command after the dependency line is run and in a different shell for each

qsolve_run: qsolve_run.o qsolve.o
	${CC} -o qsolve_run qsolve_run.o qsolve.o -lm

run: qsolve_run
	./qsolve_run

cunit.o: cunit.h
t1.o: cunit.h qsolve.h
qsolve_run.o: qsolve.h
