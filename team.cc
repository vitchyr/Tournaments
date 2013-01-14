#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "team.h"
using namespace std;

Team::Team(){
	score = makeRScore();
}

Team::Team(double _score){
	score = _score;
}

bool Team::operator < (Team other) const{
	if ((*this).getScore() == other.getScore()){
		srand ( time(NULL));
		return rand() % 2;
	}
	return (*this).getScore() < other.getScore();
}

//assumes that there are 100 different skill ranges
double Team::makeRScore(){
	return rand() % 100 / 100.0;
}

double Team::getScore() const{
	return score;
}

void Team::setID(int new_ID){
	ID = new_ID;
}

int Team::getID(){
	return ID;
}

bool Team::leftWins(Team * one, Team * two){
	if (*one < *two)
		return false;
	return true;
}

void Team::setPlace(int _place){
	place = _place;
}

int Team::getPlace(){
	return place;
}

void Team::setPred(int _pred){
	pred = _pred;
}

int Team::getPred(){
	return pred;
}
