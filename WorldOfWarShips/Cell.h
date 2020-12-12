#pragma once

template <typename T> T max(T val_1, T val_2) {
	return val_1 > val_2 ? val_1 : val_2;
}

template <typename T> T min(T val_1, T val_2) {
	return val_1 < val_2 ? val_1 : val_2;
}

class Cell {
private:
	size_t _x_pos;
	size_t _y_pos;
	bool _is_hit;
	bool _is_deck;
public:
	Cell(size_t x, size_t y) : _x_pos(x), _y_pos(y) {
		this->_is_hit = false;
		this->_is_deck = false;
	};

	Cell(const Cell& C) {
		this->_x_pos = C._x_pos;
		this->_y_pos = C._y_pos;
		this->_is_hit = C._is_hit;
		this->_is_deck = C._is_deck;
	};
	size_t get_x() { return this->_x_pos; }
	size_t get_y() { return this->_y_pos; }
	bool is_hit() { return this->_is_hit; }
	bool is_deck() { return this->_is_deck; }
	bool hit() { this->_is_hit = true; }
	bool set_deck() { this->_is_deck = true; };
	~Cell() {};
};
