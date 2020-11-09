#ifndef TXTTOCSV_HPP
#define TXTTOCSV_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Word.hpp"
#include <algorithm>

using namespace std;

class TXTtoCSV{

	private:
		FILE * input_file;
		FILE * output_file;
		map <string, unsigned int> dict;
		vector <Word> array;

	public:
		TXTtoCSV(const char * file_name);
		
		void build_dict(){};
		
		
		void build_array();
		build_CSV(char * output_file_name);
		
		~TXTtoCSV();
};
#endif
