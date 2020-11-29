#pragma once
#include <vector>
#include <map>
#include <string>
#include "Block.h"

class Executor
{
private:
	std::map <size_t, Block*> _blocks;

public:
	Executor() = default;
	
	Executor(const Executor& E) {
		for (auto it = E._blocks.begin(); it != E._blocks.end(); ++it) 
			this->_blocks[it->first] = it->second;
	}
	
	void add_block(size_t id, std::string cmd, std::vector < std::string > args) {

		if (this->_blocks.count(id) > 0)
			throw "\nError: class Executor: command id is not unique\n";

		if (cmd == "readfile")
			this->_blocks[id] = new Readfile(args);
		else
			if (cmd == "writefile")
				this->_blocks[id] = new Writefile(args);
			else
				if (cmd == "sort")
					this->_blocks[id] = new Sort();
				else
					if (cmd == "grep")
						this->_blocks[id] = new Grep(args);
					else
						if (cmd == "replace")
							this->_blocks[id] = new Replace(args);
						else
							if (cmd == "dump")
								this->_blocks[id] = new Dump(args);

							else
								throw "\nException in class Executor: Unknown command in constructor\n";

	};



	void process_requests(std::vector<size_t> id_block_chain) {
		std::vector<std::string>buff;
		for (size_t i = 0; i < id_block_chain.size(); i++) {
			if (this->_blocks.count(id_block_chain[i]) == 0)
				throw "\nError on class Executor: block id does not exist\n";
			else
				buff = this->_blocks[id_block_chain[i]]->process_request(buff);
		}
	};

	~Executor() { this->_blocks.clear(); };

};