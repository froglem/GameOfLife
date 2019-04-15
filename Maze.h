#pragma once
#include<vector>

template <class T>
using Matrix = std::vector<std::vector<T>>;


class Point {

public:
	bool m_current_cell{ false }, m_old_cell{ false };
	bool operator==(const Point& pt) const {
		return m_current_cell == pt.m_current_cell;
	}
};

class Maze {

	friend class GameBoardWidget;

public:
	
	void loafFromFile(std::string configfileName);
	unsigned int getNumberOfRows() const;
	unsigned int getNumberOfColumns() const;
	void Maze::computeMaze();

//
private:

	unsigned int number_of_rows{ 0 }, number_of_columns{ 0 };
	bool merge_rows{ false }, merge_columns{ false };
	const unsigned int max_when_alive = 3, min_when_alive = 2, new_life_value = 3;
	Matrix<Point> game_maze;

	std::string convertMazetoRLE() const;
	void add_to_maze(const char symbol, int number, int& current_row, int& current_column);
	unsigned int Maze::count_alive(int row, int column) const;
};