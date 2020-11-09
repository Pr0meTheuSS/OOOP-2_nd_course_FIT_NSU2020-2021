
#ifndef WORD_HPP
#define WORD_HPP

#include <iostream>
#include <string>

class Word{
	
	private:
		std::string word;
		unsigned int count;
	
	public:
		
	
		Word(std::string S, unsigned int C);
	
		std::string get_word();
	
		unsigned int get_count();
	
		void output_in_CSV(FILE * out);
					
		operator <(const Word& W);
	
		~Word();
				
};
#endif 
