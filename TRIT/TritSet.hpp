class TritSet{
	private:
		vector<AtomTrit> Set;
	public:
		TritSet(size_t size);

		operator |(const TritSet& TS);
		operator &(const TritSet& TS);
		operator !(const TritSet& TS);
		
		~TritSet(){};	 
};

