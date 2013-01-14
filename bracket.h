class Bracket{
	int num_teams, rounds, byes;
	Team ** teams, ** results;
	public:
		Bracket(int, Team **);
		Bracket(int, int, Team **, Team**);
		void construct(int, int, Team **);
		void play();
		Team ** getResults();
		void setRounds(int);
		int getRounds();
		void printTeams(Team**, int);
};
