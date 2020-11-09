#include "TXTtoCSV.hpp"

using namespace std;
using namespace TXTtoCSV;


		TXTtoCSV(const char * file_name, char * output_file_name){
			this->input_file = fopen(file_name, "rb");
			if(this->input_file == NULL)
				throw "Error: can't open this file\n";	

			this->output_file = fopen(output_file_name, "a");
			if(this->output_file == NULL)
				throw "Error: can't open this file\n";
		};
		
		void build_dict(){
			string str_word = "";
			char tmp_char;

			while(fscanf(this->input_file, "%c", &tmp_char) > 0){
				
				if(isalpha(int(tmp_char)))
					str_word.append(&tmp_char, 1);
				
				else{
					if(str_word != ""){
						if(this->dict.count(str_word))
							this->dict.at(str_word) += 1u;
						else			
							this->dict.insert(pair<string, unsigned int>(str_word, 1u));
						str_word.assign("");						
					}
				}
			}
		};
				
		void build_array(){
			
			map<string, unsigned int>::iterator It;
		
			for( It = this->dict.begin(); It != dict.end();++It)
				this->array.push_back(Word(It->first, It->second));
		
			sort(this->array.begin(), this->array.end());
		};
		
		build_CSV(){	
		
			this->build_dict();
			this->build_array();
		
			for(int i = this->array.size() - 1; i >= 0; i--)
				this->array[i].output_in_CSV(this->output_file);
		};
		
		~TXTtoCSV(){fclose(this->input_file); fclose(this->output_file);};
};


