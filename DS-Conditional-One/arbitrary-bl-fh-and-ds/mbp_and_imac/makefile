CC=g++
all: main

arbi_bl_fh_and_ds.o: arbi_bl_fh_and_ds.cpp ../../condmatrix.h
	${CC} -c arbi_bl_fh_and_ds.cpp

condmatrix.o: ../../condmatrix.h ../../condmatrix.cpp
	${CC} -c ../../condmatrix.cpp

main: arbi_bl_fh_and_ds.o condmatrix.o
	${CC} -o arbi_bl arbi_bl_fh_and_ds.o condmatrix.o

clean:
	rm *.o arbi_bl
