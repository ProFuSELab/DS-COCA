CC=g++
all: main

arbi_mass_ds.o: arbi_mass_ds.cpp ../../condmatrix.h
	${CC} -c arbi_mass_ds.cpp

condmatrix.o: ../../condmatrix.h ../../condmatrix.cpp
	${CC} -c ../../condmatrix.cpp

main: arbi_mass_ds.o condmatrix.o
	${CC} -o arbi_mass_ds arbi_mass_ds.o condmatrix.o

clean:
	rm *.o arbi_mass_ds
