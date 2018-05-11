CC=g++
all: main

specialization_all_mass_ds.o: specialization_all_mass_ds.cpp
	${CC} -c specialization_all_mass_ds.cpp

main: specialization_all_mass_ds.o
	${CC} -o specialization_all_mass_ds specialization_all_mass_ds.o 

clean:
	rm *.o specialization_all_mass_ds 
