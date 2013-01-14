class Team{
	double score;
	int ID, place, pred;
	public:
		Team();
		Team(double);
		bool operator < (Team) const;
		double makeRScore();
		double getScore() const;
		void setID(int);
		int getID();
		static bool leftWins(Team*, Team*);
		void setPlace(int);
		int getPlace();
		void setPred(int);
		int getPred();
};
