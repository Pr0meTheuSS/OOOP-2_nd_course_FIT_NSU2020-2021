#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class Block
{

public:
	virtual std::vector<std::string > process_request(std::vector<std::string> args) = 0;
};

class Readfile : public Block {
private:
	std::string _input_filename;
public:
	
	Readfile(std::vector<std::string> args) {
		if (args.size() != 1)
			throw "\nIn class Readfile: vector args's size is not right\n";
		this->_input_filename = args[0]; 
	};

	std::vector<std::string> process_request(std::vector<std::string >data) {

		if (!data.empty())
			throw "\nIn class Readfile: data is not empty!\n";

		std::ifstream in(this->_input_filename.c_str());
	
		if (!in.is_open())
			throw "\nCannot open this file\n";
		
		std::vector<std::string >ret_data;
		ret_data.push_back("");
		
		std::string buff;
		while (std::getline(in, buff))
		{
			buff.push_back('\n');
			ret_data.push_back(buff);
		}

		return ret_data;
	}
};


class Writefile : public Block {
private:
	std::string _output_filename;
public:

	Writefile(std::vector<std::string> args) {
		if (args.size() != 1)
			throw "\nIn class Writefile: vector args's size is not right\n";
		this->_output_filename = args[0];
	};

	std::vector<std::string > process_request(std::vector<std::string >data) {

		std::ofstream out(this->_output_filename);

		if (!out.is_open())
			throw "\nCannot open this file\n";
	
		for(size_t i = 0; i < data.size(); i++)
			out << data[i];
		
		out.close();

		std::vector<std::string >ret;
		ret.clear();
		return ret;// возврат пустого  вектора, мне не нравится
	}
};

class Dump : public Block {
private:
	std::string _output_filename;
public:

	Dump(std::vector<std::string> args){
		if (args.size() !=  1)
			throw "\nIn class Dump: vector args's size is not right\n";
		this->_output_filename = args[0];
	};

	std::vector <std::string> process_request(std::vector<std::string >data) {

		std::ofstream out(this->_output_filename);

		if (!out.is_open())
			throw "\nCannot open this file\n";
	
		for (size_t i = 0; i < data.size(); i++)
			out << data[i];
		return data;
		out.close();
	}
};


class Grep : public Block {
private:
	std::string _to_find;
public:

	Grep(std::vector <std::string> args){
		if (args.size() != 1)
			throw "\nIn class Grep: vector args's size is not right\n";
		this->_to_find= args[0];
	};

	std::vector<std::string > process_request(std::vector<std::string>data) {

		std::vector<std::string > ret;

		size_t data_size = data.size();
		for (size_t i = 0; i < data_size; i++)
			if (data[i].find(this->_to_find, 0) != std::string::npos)
				ret.push_back(data[i]);
	
		return ret;
	}
};

class Sort :public Block {
public:
	Sort() = default;
	std::vector<std::string > process_request(std::vector<std::string>data) {

		std::sort(data.begin(), data.end());

		return data;
	}
	~Sort() = default;
};


class Replace:public Block {
	std::string _word1;
	std::string	_word2;
public:
	Replace(std::vector < std::string > args) {
		if(args.size() != 2)
			throw "\nIn class Replace: vector args's size is not right\n";
		this->_word1 = args[0];
		this->_word2 = args[1];
	};

	std::vector<std::string > process_request(std::vector<std::string>data) {
		
		size_t data_size = data.size();
		
		std::string whole_str;

		for (size_t i = 0; i < data_size; i++)
			whole_str += data[i];

		size_t pos = 0;
		while (pos < whole_str.size()) {
			pos = whole_str.find(this->_word1, pos);
			if (pos == std::string::npos)
				break;
			whole_str.replace(pos, this->_word1.size(), this->_word2);
			pos++;
		}	
		std::vector<std::string > ret;
		
		size_t i = 0;
		std::string buff;

		while (i < whole_str.size()) {

			buff += whole_str[i];
			
			if (whole_str[i] == '\n' || whole_str[i] == '\0' || whole_str[i] == std::string::npos || i + 1 >= whole_str.size()) {
				ret.push_back(buff);
				buff.clear();
			}
			i++;
		}
		return ret;
	}
	~Replace() { 
		// не знаю как лучше очистить память и надо ли 
		this->_word1.clear(); 
		this->_word2.clear();
		this->_word1.resize(0);
		this->_word2.resize(0);
	};
};

