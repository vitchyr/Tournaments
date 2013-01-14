#define TRIALS 100000

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include "team.h"
#include "bracket.h"

#define USER_INPUT 0
#define TEAMS 16
#define TYPE 1
#define NUM_TYPES 1


using namespace std;

Team ** makeTeams(int num_teams){
	Team ** teams = new Team*[num_teams];
	int i;
	for (i = 0; i < num_teams; i++){
		teams[i] = new Team;//(rand() % 100 / 100.0);
		teams[i] -> setID(i);
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


void printResults(int * prediction, Team ** results, int num_teams){
	cout << endl << "  ****  Results  ****  " << endl;
	int i;
	for (i = 0; i < num_teams; i++){
		if ((i != 0) && !(i & (i - 1)))
			cout << "\t---" << endl;
		cout << "Team " << results[i] -> getID() << "\t(" 
			 << results[i] -> getPlace() << " pred: " 
			 << results[i] -> getPred() << ")" << "at score "
			 << results[i] -> getScore() << endl;
	}
}

int main(){
	srand(time(0));
	string mystr;
	int num_teams, system = 0;
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
	
	/* One time code
	teams = makeTeams(num_teams);
	prediction = predict(teams, num_teams);
	if (system == 1){
		Bracket tournament (num_teams, teams);
		tournament.play();
		results = tournament.getResults();
	}
	printResults(prediction, results, num_teams);
	delete[] teams, prediction, results;
	*/

	//Simulations
	Team ** teams, ** results;
	int i, *prediction;
	double data[num_teams];
	double add = 1.0/(double)TRIALS;
	for (i=0; i<TRIALS; i++){
		teams = makeTeams(num_teams);
		prediction = predict(teams, num_teams);
		if (system == 1){
			Bracket tournament (num_teams, teams);
			tournament.play();
			results = tournament.getResults();
		}
		int j;
		for(j = 0; j<num_teams; j++){
			if((results[j] -> getPlace() == 
				results[j] -> getPred()))
				data[j] += add;
		}
		//printResults(prediction, results, num_teams);
		delete[] teams, prediction, results;
	}
	ofstream myfile;
	myfile.open ("output.dat");
	cout << "place\taccuracy\n";
	myfile << "place\taccuracy\n";
	cout.precision(ceil(log10((double) TRIALS)));
	for(i=0; i<num_teams; i++){
		cout << i+1 << "\t" << fixed << data[i] << endl;
		myfile << i+1 << "\t" << fixed << data[i] << endl;
	}
	myfile.close();
}
