#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "team.h"
#include "bracket.h"
using namespace std;

Bracket::Bracket(int _num_teams, Team ** _teams){
	int _rounds = ceil(log((double) _num_teams)/log(2.0));
	results = new Team*[_num_teams];
	construct(_num_teams, _rounds, _teams);
}

Bracket::Bracket(int _num_teams, int _rounds, Team ** _results, 
				Team ** _teams){
	results = _results;
	construct(_num_teams, _rounds, _teams);
}

void Bracket::construct(int _num_teams, int _rounds, 
						Team ** _teams){
	num_teams = _num_teams;
	rounds = _rounds;
	byes = (int) pow(2,rounds) - num_teams;
	teams = _teams;
}

void Bracket::play(){
	int games_played = (int) pow(2, rounds -1) - byes;
	Team * winners[num_teams - games_played], *losers[games_played];
	int i;

	//play games
	for (i = 0; i < games_played; i++){
		if(Team::leftWins(teams[2*i], teams[2*i + 1])){
			winners[i] = teams[2*i];
			losers[i] = teams[2*i+1];
		} else {
			winners[i] = teams[2*i+1];
			losers[i] = teams[2*i];
		}
	}

	//add people who got byes
	for (i = games_played*2; i < num_teams; i++){
		winners[i - games_played] = teams[i];
	}
	
	/* this is if you don't want a losers bracket
	for (i=0; i < games_played; i++){
		results[games_played + byes + i] = losers[i];
		losers[i] -> setPlace(games_played + byes + 1);
	}
	*/
	
	/* SORT LOSERS
	 * Let them play in another tournament
	 * Then, add 2**(round they lost in - 1) to their new place
	 */
	if(rounds < 2){ //a two person tournament: all losers get 2nd
		losers[0] -> setPlace(2);
		results[1] = losers[0];
	} else {
		if(games_played > 1){ 	/* Due to byes, a team may be
								 * the only team to lose in a round
								 * in which case they don't need
								 * to play another tournament */
			Bracket losers_b (games_played, losers);
			losers_b.play();
			Team ** lb_results = losers_b.getResults();
			int j;
			for (i=0; i < games_played; i++){
				for (j=0; j < games_played; j++){
					if (losers[i] -> getID() == 
						lb_results[j] -> getID()){
						lb_results[j] -> setPlace(lb_results[j] -> 
							getPlace() + games_played + byes);
						/* games_played + byes = 
						 * 2**(round they lost in -1) */
					}
				}
			}
			for (i=0; i < games_played; i++){
				results[games_played + byes + i] = lb_results[i];
			}
		} else {
			losers[0] -> setPlace(1 + games_played + byes);
			//*1* replaces "lb_results[j] -> getPlace()" since
			//if this person played a tournament one their own
			//they would receive first place
			results[games_played + byes] = losers[0];
		}
	}

	if (rounds > 1){ //next round
		byes = 0;
		Bracket tournament(num_teams - games_played, rounds-1, 
							results, winners);
		tournament.play();
	} else { //champion!
		winners[0] -> setPlace(1);
		results[0] = winners[0];
	}
}

Team ** Bracket::getResults(){
	return results;
}

void Bracket::setRounds(int _rounds){
	rounds = _rounds;
}

int Bracket::getRounds(){
	return rounds;
}

void Bracket::printTeams(Team** teams, int size){
	cout << "[";
	int i;
	for (i=0; i < size; i++){
		cout << teams[i] -> getID() << " ";
	}
	cout << "]" << endl;
}
