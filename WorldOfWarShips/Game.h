#pragma once
#include "Player.h"

class Game
{
private:
	std::vector<Player> _players;

	bool is_game_over() {
		for (size_t i = 0; i < this->_players.size(); i++)
			if (this->_players[i].is_lose())
				return true;
		return false;
	};

	Cell ask_player(size_t player_id) {
		return this->_players[player_id].fire();
	};

	void hit_player(size_t player_id, Cell& C) {
		this->_players[player_id].hit_cell(C);
	};



public:
	Game(/*тут должны быть состояния игрков 1 и 2*/) {
		this->_players.push_back(Player(/*тут должно быть состояние игрока 1*/));
		this->_players.push_back(Player(/*тут должно быть состояние игрка 2*/));
	};

	void GameLoop() {
		int i = 0;
		while (!is_game_over()) {
			Cell move = ask_player(i % 2);
			hit_player((i + 1) % 2, move);
			i++;
		}
	};

	~Game() { this->_players.clear(); };

};
