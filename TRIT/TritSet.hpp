class TritSet{
	private:
		vector<AtomTrit> Set;
	public:
		TritSet(int size){};

		operator |(){};
		operator &(){};
		operator !(){};
		
		~TritSet(int size){};	 
};

