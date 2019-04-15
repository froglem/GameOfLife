#include "Maze.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <QDebug>


void Maze::loafFromFile(std::string configfileName)
{

	std::ifstream configFile(configfileName);
	std::string line;
	auto size_set = false;
	while (std::getline(configFile, line)) {
		if (line[0] == '#') continue;
		if (!size_set) {
			line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

			auto row_size_start = line.find("y=") + 2;
			auto row_size_stop = std::find_if_not(line.begin() + row_size_start, line.end(), ::isdigit);
			number_of_rows = std::stoi(std::string(line.begin() + row_size_start, row_size_stop));

			auto column_size_start = line.find("x=") + 2;
			auto column_size_stop = std::find_if_not(line.begin() + column_size_start, line.end(), ::isdigit);
			number_of_columns = std::stoi(std::string(line.begin() + column_size_start, column_size_stop));

			game_maze = Matrix<Point>(number_of_rows, std::vector<Point>(number_of_columns));
			size_set = true;

			continue;
		}

		std::string::iterator number_start = line.end();
		auto number = 1, current_row = 0, current_column = 0;

		for (auto symbol = line.begin(); symbol < line.end(); ++symbol) {
			number = 1;
			if (isdigit(*symbol)) {
				number_start = symbol;
				symbol = std::find_if_not(number_start, line.end(), ::isdigit);
				number = std::stoi(std::string(number_start, symbol));
			}
			add_to_maze(*symbol, number, current_row, current_column);
		}

	}

	configFile.close();
}

void Maze::add_to_maze(const char symbol, int number, int& current_row, int& current_column)
{
	if (symbol == 'o') {
		for (auto iter = 0; iter < number; ++iter) {
			game_maze[current_row][current_column + iter].m_current_cell = game_maze[current_row][current_column + iter].m_old_cell = true;
		}
		current_column += number;
	}
	else if (symbol == 'b') current_column += number;
	else if (symbol == '$') {
		current_column = 0;
		current_row += 1;
	}
}

unsigned int Maze::getNumberOfRows() const
{
	return number_of_rows;
}

unsigned int Maze::getNumberOfColumns() const
{
	return number_of_columns;
}

std::string Maze::convertMazetoRLE() const
{
	std::string outputString{};

	outputString += "x = " + std::to_string(getNumberOfColumns()) +
		" y = " + std::to_string(getNumberOfRows()) + "\n";



	for (auto row = 0u; row < number_of_rows; ++row) {
		auto iter = game_maze[row].begin();
		while (iter < game_maze[row].end()) {
			auto isAlive = (*iter).m_current_cell;
			auto iterStop = std::find_if_not(iter + 1, game_maze[row].end(), [&iter](const auto& element) {return *iter == element; });
			if (!(iterStop == game_maze[row].end() && !isAlive)) {
				auto len = iterStop - iter;
				outputString += len > 1 ? std::to_string(iterStop - iter) : "";
				outputString += isAlive ? "o" : "b";
			}
			iter = iterStop;
		}

		if (row != number_of_rows - 1)outputString += "$";
	}

	outputString += "!";

	return outputString;
}

void Maze::computeMaze()
{
	for (auto row = 0u; row < number_of_rows; ++row) {
		for (auto column = 0u; column < number_of_columns; ++column) {
			auto counter = count_alive(row, column);
			if (min_when_alive <= counter && counter <= max_when_alive && game_maze[row][column].m_old_cell) game_maze[row][column].m_current_cell = true;
			else if (new_life_value == counter && counter && !game_maze[row][column].m_old_cell) game_maze[row][column].m_current_cell = true;
			else game_maze[row][column].m_current_cell = false;
		}
	}

	for (auto row = 0u; row < number_of_rows; ++row) {
		for (auto column = 0u; column < number_of_columns; ++column) {
			game_maze[row][column].m_old_cell = game_maze[row][column].m_current_cell;
		}
	}
}

unsigned int Maze::count_alive(int row, int column) const
{
	auto counter = 0;

	if ((row - 1 >= 0) && (game_maze[row - 1][column].m_old_cell)) ++counter;
	if ((row - 1 >= 0) && (column - 1 >= 0) && (game_maze[row - 1][column - 1].m_old_cell)) ++counter;
	if ((row - 1 >= 0) && (column + 1 < number_of_columns) && (game_maze[row - 1][column + 1].m_old_cell)) ++counter;

	if ((column - 1 >= 0) && (game_maze[row][column - 1].m_old_cell)) ++counter;
	if ((column + 1 < number_of_columns) && (game_maze[row][column + 1].m_old_cell)) ++counter;

	if ((row + 1 < number_of_rows) && (game_maze[row + 1][column].m_old_cell)) ++counter;
	if ((row + 1 < number_of_rows) && (column - 1 >= 0) && (game_maze[row + 1][column - 1].m_old_cell)) ++counter;
	if ((row + 1 < number_of_rows) && (column + 1 < number_of_columns) && (game_maze[row + 1][column + 1].m_old_cell)) ++counter;

	if (merge_rows) {
		if (column == 0 && game_maze[row][number_of_columns - 1].m_old_cell) ++counter;
		if (column == number_of_columns - 1 && game_maze[row][0].m_old_cell) ++counter;

		if (column == 0 && (row - 1 >= 0) && game_maze[row - 1][number_of_columns - 1].m_old_cell) ++counter;
		if (column == number_of_columns - 1 && (row - 1 >= 0) && game_maze[row - 1][0].m_old_cell) ++counter;

		if (column == 0 && (row + 1 < number_of_rows) && game_maze[row + 1][number_of_columns - 1].m_old_cell) ++counter;
		if (column == number_of_columns - 1 && (row + 1 < number_of_rows) && game_maze[row + 1][0].m_old_cell) ++counter;
	}

	if (merge_columns) {
		if (row == 0 && game_maze[number_of_rows - 1][column].m_old_cell) ++counter;
		if (row == number_of_rows - 1 && game_maze[0][column].m_old_cell) ++counter;

		if (row == 0 && (column - 1 >= 0) && game_maze[number_of_rows - 1][column - 1].m_old_cell) ++counter;
		if (row == number_of_rows - 1 && (column - 1 >= 0) && game_maze[0][column - 1].m_old_cell) ++counter;

		if (row == 0 && (column + 1 < number_of_columns) && game_maze[number_of_rows - 1][column + 1].m_old_cell) ++counter;
		if (row == number_of_rows - 1 && (column + 1 < number_of_columns) && game_maze[0][column + 1].m_old_cell) ++counter;
	}

	if (merge_columns && merge_rows) {
		if (row == 0 && column == 0 && game_maze[number_of_rows - 1][number_of_columns - 1].m_old_cell) ++counter;
		if (row == 0 && column == number_of_columns - 1 && game_maze[number_of_rows - 1][0].m_old_cell) ++counter;

		if (row == number_of_rows - 1 && column == 0 && game_maze[0][number_of_columns - 1].m_old_cell) ++counter;
		if (row == number_of_rows - 1 && column == number_of_columns - 1 && game_maze[0][0].m_old_cell) ++counter;
	}


	return counter;
}