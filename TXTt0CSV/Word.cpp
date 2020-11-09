#include "Word.hpp"
	
		Word(std::string W, unsigned int C){
			this->word = W;
			this->count = C;
		};
	
		Word::get_word(){return this->word;}
	
		Word::get_count(){return this->count;}
	
		Word::output_in_CSV(FILE * of){
			if(of == NULL)
				throw "Error: can't open this file\n";	
			fprintf(of, "%s, %u\n", this->get_word().c_str(),this->get_count());
		};
					
		Word::operator <(Word w_1){
			return this->count < w_1.count;
		};
		
		~Word::Word(){};		
};
