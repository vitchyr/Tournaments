#include <iostream>
#include <stdlib.h>
#include "team.h"

#define LEVELS 1000

using namespace std;

Team::Team(){
	score = makeRScore();
}

Team::Team(double _score){
	score = _score;
}

bool Team::operator < (Team other) const{ 
	/* so far, no tie breaker system
	 * do not use rand() here for a tie breaker. It will cause
	 * a segmentation fault since this function is called from
	 * sort() */
	if (this -> getScore() == other.getScore()){
		return ((this -> getID()) < other.getID());
	}
	return this -> getScore() < other.getScore();
}

//assumes that there are LEVEL different skill ranges
double Team::makeRScore(){
	return rand() % LEVELS / (double) LEVELS;
}

void Team::newRScore(){
	score = makeRScore();
}

double Team::getScore() const{
	return score;
}

void Team::setID(int new_ID){
	ID = new_ID;
}

int Team::getID() const{
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
