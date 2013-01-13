#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "team.h"
#include "bracket.h"
using namespace std;

Bracket::Bracket(int _num_teams, Team * _teams){
	num_teams = _num_teams;
	rounds = ceil(log((double) num_teams)/log(2.0));
	byes = (int) pow(2,rounds) - num_teams;
	results = new int[num_teams];
	teams = _teams;
}

void Bracket::play(){
	Team * winner;
	winner = Team::play(teams, teams + 1);
	cout << "The winner between " << teams->getID() << " and " << (teams+1)->getID() << " is " << winner->getID() << endl;
}

int * Bracket::getResults(){
	return results;
}
