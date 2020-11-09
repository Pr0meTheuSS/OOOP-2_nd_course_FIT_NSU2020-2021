#include "Word.hpp"
#include "TXTtoCSV.hpp"

using namespace std; 

int main(void){
	try{
		TXTtoCSV Data = TXTtoCSV("input.txt");
		Data.build_CSV("output.csv");
	}
	catch(...){
		printf("Error: can't convert TXT to CSV");
		exit(0);	
	};
}
