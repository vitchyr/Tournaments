class Bracket{
	int num_teams, rounds, byes, *results;
	Team * teams;
	public:
		Bracket(int, Team *);
		void play();
		int * getResults();
};
