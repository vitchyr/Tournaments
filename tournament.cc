#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "team.h"
#include "bracket.h"
using namespace std;

int main(){
	string mystr;
	int system = 0;
	while (system == 0){
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
	if (system == 1){
		Bracket tournament;
	}
}
