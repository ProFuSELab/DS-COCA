CC=g++
all: main

all_bl_bruteforce_fh_and_ds.o: all_bl_bruteforce_fh_and_ds.cpp ../../condmatrix.h
	${CC} -c all_bl_bruteforce_fh_and_ds.cpp

condmatrix.o: ../../condmatrix.h ../../condmatrix.cpp
	${CC} -c ../../condmatrix.cpp

main: all_bl_bruteforce_fh_and_ds.o condmatrix.o
	${CC} -o all_bl_bruteforce all_bl_bruteforce_fh_and_ds.o condmatrix.o

clean:
	rm *.o all_bl_bruteforce
