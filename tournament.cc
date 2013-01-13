#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>
#include "team.h"
#include "bracket.h"
using namespace std;

Team * makeTeams(int num_teams){
	int i;
	Team * teams = new Team[num_teams];
	srand (time(NULL));
	for (i = 0; i < num_teams; i++){
		teams[i].setID(i);
	}
	return teams;
}

int * predict(Team * teams, int num_teams){
	int * prediction = new int[num_teams];
	vector<Team> team_vector (teams, teams + num_teams);
	vector<Team>::iterator it;
	sort (team_vector.begin(), team_vector.end());
	int i = 0;
	for (it=team_vector.end()-1; it != team_vector.begin()-1; it--){
		prediction[i] = (*it).getID();
		cout << "Team " << (*it).getID() << " with a score of " << (*it).getScore() << endl;
		i++;
	}
	return prediction;
}

int main(){
	Team * teams;
	string mystr;
	int num_teams, system = 0, *prediction, *results;
	while (system == 0){
		string mystr;
		num_teams;
		cout << "How many teams? ";
		getline (cin, mystr);
		stringstream(mystr) >> num_teams;
		cout << "What tournament system do you want to use?" << endl;
		cout << "	1 - Bracket" << endl;
		cout << "	q - Quit" << endl;
		getline (cin, mystr);
		if (mystr == "q"){
			break;
		}
		stringstream(mystr) >> system;
		if (system < 1 || system > 1){
			system = 0;
		}
	}
	teams = makeTeams(num_teams);
	prediction = predict(teams, num_teams);
	if (system == 1){
		Bracket tournament (num_teams, teams);
		tournament.play();
		results = tournament.getResults();
	}
	delete[] teams;
}
