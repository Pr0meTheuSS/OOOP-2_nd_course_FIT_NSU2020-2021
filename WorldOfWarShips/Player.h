#pragma once
#include <vector>
#include "Board.h"
#include <math.h>
#include <iostream>

inline Cell input() {
	/*
	переходник для увеличения гибкости чтения данных о положении кораблей при установке их на карте
	Возможно и консольное чтение, и получение данных от модуля обратотки событий мыши
	*/
	size_t x;
	size_t y;
	printf("\nEnter x:\n");
	std::cin >> x;
	printf("\nEnter y:\n");
	std::cin >> y;
	return Cell(x, y);
}



inline size_t ship_len(Cell start, Cell end) {
	return max(start.get_x(), end.get_x()) - min(start.get_x(), end.get_x()) + max(start.get_y(), end.get_y()) - min(start.get_y(), end.get_y()) + 1u;
}

class Player {

private:
	Board* _own_board;
	Board* _enemy_board;
	bool _is_lose;
public:

	Player() {
		this->_own_board = new Board(10, 10);
		this->_enemy_board = new Board(10, 10);
		this->_is_lose = false;
	};

	void set_ships() {
		int ship_number = 0;
		while (ship_number != 10) {
			Cell start = input();
			Cell end = input();
			if (start.get_x() != end.get_x() && start.get_y() != end.get_y()) {// если начало и конец не лежат на одной вертикали или горизонтали
				printf("Error of ship position\n");
			}
			if (ship_number == 0) {
				if (ship_len(start, end) != 4u)
					continue;
			}
			if (ship_number == 1 || ship_number == 2) {
				if (ship_len(start, end) != 3u)
					continue;
			}
			if (ship_number == 3 || ship_number == 4 || ship_number == 5) {
				if (ship_len(start, end) != 2u)
					continue;
			}
			if (ship_number == 6 || ship_number == 7 || ship_number == 8 || ship_number == 9) {
				if (ship_len(start, end) != 1u)
					continue;
			}

			this->_own_board->is_collizion(start, end);
			set_ship(start, end);
			ship_number++;
		}
	}
	void set_ship(Cell start, Cell end) {
		/*
		На входе - валидные данные о позиции корабля с правильной длиной и с правильным взаимным расположением кормы и носа
		Так как ответственность за валидность данных лежит на вызывающем методе set_ships()
		*/
		size_t x_pos = min(start.get_x(), end.get_x());
		size_t y_pos = min(start.get_y(), end.get_y());

		for (size_t i = 0; i < ship_len(start, end); i++) {
			this->_own_board->set_deck(Cell(x_pos, y_pos));
			if (start.get_x() == end.get_x())
				y_pos++;
			else
				x_pos++;
		}
	};

	Cell fire() {

		Cell target = input();

		while (this->_enemy_board->hit_cell(target))
			target = input();

		return target;
	};

	void hit_cell(Cell& C) {
		this->_own_board->hit_cell(C);
	}

	bool check_is_lose() {
		return this->_own_board->is_army_destroyed();
	}
	bool is_lose() {
		check_is_lose();
		return this->_is_lose;
	};

	~Player() {
		delete this->_own_board;
		delete this->_enemy_board;
	};
};

