#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif 
#ifndef STRING
#define STRING
#include <string>
#endif 

#ifndef WORD_HPP
#define WORD_HPP

class Word{
	
	private:
		std::string word;
		unsigned int count;
		
	public:
		
	
		Word(std::string, unsigned int );
	
		std::string get_word();
	
		unsigned int get_count();
	
		void output_in_CSV(FILE * );
					
		operator <(Word );
	
		~Word();
				
};

#endif 


