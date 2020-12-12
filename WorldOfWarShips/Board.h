#pragma once
#include "Cell.h"
#include <vector>


class Board {
private:
	std::vector<std::vector<Cell>> _board;

public:

	Board(size_t width, size_t height) {
		// Очень важно протестить, так как встроенные функции всегда таят в себе неприятные сюрпризы
		std::vector<Cell> tmp;
		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++)
				tmp.push_back(Cell(x, y));

			this->_board.push_back(tmp);
			tmp.clear();
		}
	};

	bool hit_cell(Cell& cell) {

		if (this->_board[cell.get_y()][cell.get_x()].is_hit())
			return false;

		this->_board[cell.get_y()][cell.get_x()].hit();
		return true;
	}

	void set_deck(Cell cell) {

		this->_board[cell.get_y()][cell.get_x()].set_deck();
	}

	bool is_army_destroyed() {

		for (size_t i = 0; i < this->_board.size(); i++)
			for (size_t t = 0; t < this->_board[i].size(); t++)
				if (this->_board[i][t].is_deck() && !this->_board[i][t].is_hit())// если есть неповреждённые палубы 
					return false;

		return true;
	};

	bool is_collizion(Cell& start, Cell& end) {

		size_t x_left_up = min(start.get_x(), end.get_x()) > 0 ? min(start.get_x(), end.get_x()) - 1 : min(start.get_x(), end.get_x());
		size_t y_left_up = min(start.get_y(), end.get_y()) > 0 ? min(start.get_y(), end.get_y()) - 1 : min(start.get_y(), end.get_y());

		size_t x_right_down = max(start.get_x(), end.get_x()) >= 10 ? max(start.get_x(), end.get_x()) - 1 : max(start.get_x(), end.get_x());
		size_t y_right_down = max(start.get_y(), end.get_y()) >= 10 ? max(start.get_y(), end.get_y()) - 1 : max(start.get_y(), end.get_y());

		for (size_t i = y_left_up; i < y_right_down; i++)
			for (size_t t = x_left_up; t < x_right_down; t++) 
				if (this->_board[i][t].is_deck())
					return true;
			
		return false;
	}


	~Board() {};

};

