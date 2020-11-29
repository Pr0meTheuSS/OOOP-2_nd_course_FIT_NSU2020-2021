#include <iostream>
#include "WorkFlow.h"

int main(char ** argv, int argc)
{
	//if (argc != 2) {
	//	std::cerr << "\nException of args_count\n";
	//	exit(0);
	//}

	//else {
	try {
		WorkFlow WF("Workflow.txt");
	}
	catch (const char* exception) {
			std::cerr << exception;
			exit(0);
		}
		return 0;
}


