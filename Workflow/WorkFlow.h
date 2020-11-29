#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Executor.h"

class WorkFlow
{
private:
	std::ifstream _input_stream;
	Executor _exe;
public:

	WorkFlow(const char* name) {

		this->_input_stream.open(name);

		if (!this->_input_stream.is_open())
			throw "\nCannot open this file\n Workflow.h\n";

		std::string buff;
		std::vector<std::string>file_contents;
	
		while (std::getline(this->_input_stream, buff))
		{
			buff.push_back('\n');
			file_contents.push_back(buff);
		}
		
		size_t desc_line = 0;
		size_t csed_line = 0;

		for (size_t i = 0; i < file_contents.size(); i++) {

			if (file_contents[i].find("desc") != std::string::npos)
				desc_line = i;			
			if (file_contents[i].find("csed") != std::string::npos) 
				csed_line = i;			
		}

		if(csed_line <= desc_line)
			throw "\nError: Invalid synthax in workflow file, problem with \"desc\" & \"csed\" position in file\n";


	//вынести в отдельный метод 
		//это блок генерации this->_exe   на вход :
		//file_contents, 
		//на выход - Executor - результат 
		for (size_t i = desc_line + 1; i < csed_line; i++) {
			
			size_t id = 0;
			std::string cmd;
			std::vector < std::string> args;
			std::string arg;
			size_t k = 0;

			while (isdigit(file_contents[i][k])) {
				id *= 10;
				id += file_contents[i][k++] - '0';
			}
		
			while (!isalpha(file_contents[i][k]))
				k++;

			while (isalpha(file_contents[i][k]))
				cmd.push_back(file_contents[i][k++]);
			
			while (k < file_contents[i].size() && !isalpha(file_contents[i][k]))
				k++;

			if (k >= file_contents[i].size()) {
				this->_exe.add_block(id, cmd, args);
				continue;
			}

			while (k  < file_contents[i].size() ) {
				if (file_contents[i][k] != ' ' && file_contents[i][k] != '\n')
					arg.push_back(file_contents[i][k]);
				else {
					args.push_back(arg);
					arg.clear();
				}
				k++;
			}
			this->_exe.add_block(id, cmd, args);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::vector <size_t> id_block_chain;
		size_t t = 0;

		csed_line++;

		while (file_contents[csed_line][t] != '\n') {
			size_t id_block = 0;
			while (isdigit(file_contents[csed_line][t]))
			{
				id_block *= 10;
				id_block += file_contents[csed_line][t++] - '0';
			}
			id_block_chain.push_back(id_block);
			if (t == file_contents[csed_line].size() - 1)
				break;
			if (file_contents[csed_line][t] == '-' && (t + 2) < file_contents[csed_line].size() && file_contents[csed_line][t + 1] == '>')
			{
				t+=2;
				continue;
			}	
			else
				throw	"\nSynthax Error: keyword \"->\" in csed_part wrote wrong\n";
		}// имеем вектор  : id_block_chain[0] -> id_block_chain[1] -> ... -> id_block_chain[size() - 1] - порядок вызова блоков обработчиков

		// Validation !!!!!! is right that _exe.get(id_block_chain[0]).cmd == 'readfile' and _exe.get(id_block_chain[size() - 1]).cmd == 'writefile' and only with this index_id 
	
		this->_exe.process_requests(id_block_chain);// get vector id_block_chain with right order of blocks
	};
};