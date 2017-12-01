mpic++ -I ../../lammps-11Aug17/src -c *.cpp -std=c++11
mpic++ -L ../../lammps-11Aug17/src *.o -std=c++11 -llammps -lpthread -o cga
