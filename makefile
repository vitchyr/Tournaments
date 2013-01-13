CC=g++
CFLAGS = -Wall -I.

play: tournament.o team.o bracket.o
	g++ -o play tournament.o team.o bracket.o

tournament.o: tournament.cc
	g++ -c tournament.cc

team.o: team.cc team.h
	g++ -c team.cc

bracket.o: bracket.cc bracket.h
	g++ -c bracket.cc

make clean:
	rm -f *o
