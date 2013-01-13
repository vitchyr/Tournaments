class Team{
	double score;
	int ID;
	public:
		Team();
		Team(double);
		bool operator < (Team) const;
		double makeRScore();
		double getScore() const;
		void setID(int);
		int getID();
		static Team * play(Team*, Team*);
};
