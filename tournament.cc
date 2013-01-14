#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>
#include "team.h"
#include "bracket.h"

#define TEAMS 16
#define TYPE 1
#define USER_INPUT 1
#define NUM_TYPES 1

using namespace std;

Team ** makeTeams(int num_teams){
	srand (time(NULL));
	Team ** teams = new Team*[num_teams];
	int i;
	for (i = 0; i < num_teams; i++){
		teams[i] = new Team();
		(*(teams[i])).setID(i);
	}
	return teams;
}

bool deref_comp(Team* one, Team* two){
	return *one < *two;
}

int * predict(Team ** teams, int num_teams){
	int * prediction = new int[num_teams];
	vector<Team*> team_vector (teams, teams + num_teams);
	vector<Team*>::iterator it;
	sort (team_vector.begin(), team_vector.end(), deref_comp);
	int i = 0;
	for (it=team_vector.end()-1; it != team_vector.begin()-1; it--){
		prediction[i] = (*it) -> getID();
		(*it) -> setPred(i + 1);
		i++;
	}
	return prediction;
}

int main(){
	Team ** teams, ** results;
	string mystr;
	int num_teams, system = 0, *prediction;
#if USER_INPUT
	while (system == 0){
		string mystr;
		num_teams;
		cout << "How many teams? ";
		getline (cin, mystr);
		stringstream(mystr) >> num_teams;
		cout << "What tournament system do you want to use?"<<endl;
		cout << "	1 - Bracket" << endl;
		cout << "	q - Quit" << endl;
		getline (cin, mystr);
		if (mystr == "q"){
			break;
		}
		stringstream(mystr) >> system;
		if (system < NUM_TYPES || system > NUM_TYPES){
			system = 0;
		}
	}
#else
	num_teams = TEAMS;
	system = TYPE;
#endif
	teams = makeTeams(num_teams);
	prediction = predict(teams, num_teams);
	if (system == 1){
		Bracket tournament (num_teams, teams);
		tournament.play();
		results = tournament.getResults();
	}
	cout << "Results" << endl;
	int i;
	for (i = 0; i < num_teams; i++){
		if ((i != 0) && !(i & (i - 1)))
			cout << "\t---" << endl;
		cout << "Team " << results[i] -> getID() << "\t(" 
			 << results[i] -> getPlace() << " pred: " 
			 << results[i] -> getPred() << ")" << endl;
	}
	delete[] teams;
}
