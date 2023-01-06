// Word Search Puzzle Solver
// By: Benjamin Yee
// Email: yeebenja@umich.edu
// LinkedIn: https://www.linkedin.com/in/yeebenja

#include <iostream>
#include <string>
#include "assert.h"
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

// Exceptions
class Invalid_Character {};
class Invalid_Direction {};
class Invalid_Arguments {};

// Found_word class
class found_word {
private:
	string word;
	string direction;
	int tile_index;
	int row_index;
	int column_index;
	int width;
	int height;
public:
	// Custom Constructor
	found_word(string word_in, string direction_in, int tile_index_in, int width_in,
		int height_in) :
		word(word_in), direction(direction_in), tile_index(tile_index_in),
		width(width_in), height(height_in) {
		column_index = tile_index_in % width_in;
		row_index = (tile_index_in - column_index) / width;
	}

	// EFFECTS: Prints location and direction of found word inside
	// board.
	void print_results(void) {
		cout << word << " found at tile " << tile_index << " / " << "row " << row_index;
		cout << ", col " << column_index << " due " << direction << endl;
	}
};

// Word Search Puzzle Solver Class
class word_search_puzzle_solver {
private:

	struct Tile {	
		// Note: Tile is just "plain old data". No need
		// to use dynamic programming
		
		char letter; // Represents what letter the tile represents
		// Tile pointers that point to other tiles around current tile
		Tile* north;
		Tile* northeast;
		Tile* east;
		Tile* southeast;
		Tile* south;
		Tile* southwest;
		Tile* west;
		Tile* northwest;
	};
	Tile* board[20000]; // MAX SIZE = 20000, change as needed
	Tile** board_start; // points to beginning of board[]
	int width;
	int height;
	int total_number_of_tiles;
	string input_board_filename;
	string word_bank_filename;
	vector<string> word_bank;

public:
	
	// Custom Constructor
	word_search_puzzle_solver(string input_board_filename_in, string word_bank_filename_in) :
	input_board_filename(input_board_filename_in), word_bank_filename(word_bank_filename_in){
		board_start = board;
	}

	// Destructor
	~word_search_puzzle_solver() {
		// Make sure to delete all dynamically allocated
		// tiles in board[]
		for (size_t i = 0; i < total_number_of_tiles; ++i) delete board[i];
	}
	
	// EFFECTS: Runs solver
	void run_solver(void) {
		take_input();
		print_board();
		run_solver_helper();
	}

	// EFFECTS: Goes through all words in word bank and
	// runs find_word() function on each word.
	void run_solver_helper(void) {
		for (auto current_word : word_bank) {
			find_word(current_word);
		}
	}

	// EFFECTS: Given a word, finds the cooridates of word
	// inside board.
	void find_word(string current_word) {
		for (size_t i = 0; i < total_number_of_tiles; ++i) {
			// Run function return_word_in_direction for each tile
			Tile* current_tile = board[i];
			if (current_word == return_word_in_direction(current_tile, "north", current_word.length())) {
				found_word found_word_inst(current_word.c_str(), "north", i, width, height);
				found_word_inst.print_results();
			}
			if (current_word == return_word_in_direction(current_tile, "northeast", current_word.length())) {
				found_word found_word_inst(current_word.c_str(), "northeast", i, width, height);
				found_word_inst.print_results();
			}
			if (current_word == return_word_in_direction(current_tile, "east", current_word.length())) {
				found_word found_word_inst(current_word.c_str(), "east", i, width, height);
				found_word_inst.print_results();
			}
			if (current_word == return_word_in_direction(current_tile, "southeast", current_word.length())) {
				found_word found_word_inst(current_word.c_str(), "southeast", i, width, height);
				found_word_inst.print_results();
			}
			if (current_word == return_word_in_direction(current_tile, "south", current_word.length())) {
				found_word found_word_inst(current_word.c_str(), "south", i, width, height);
				found_word_inst.print_results();
			}
			if (current_word == return_word_in_direction(current_tile, "southwest", current_word.length())) {
				found_word found_word_inst(current_word.c_str(), "southwest", i, width, height);
				found_word_inst.print_results();
			}
			if (current_word == return_word_in_direction(current_tile, "west", current_word.length())) {
				found_word found_word_inst(current_word.c_str(), "west", i, width, height);
				found_word_inst.print_results();
			}
			if (current_word == return_word_in_direction(current_tile, "northwest", current_word.length())) {
				found_word found_word_inst(current_word.c_str(), "northwest", i, width, height);
				found_word_inst.print_results();
			}
		}
	}

	// EFFECTS: Returns word starting at position in board. Will go in
	// any linear direction i.e. N, NE, E, SE, S, SW, W, NW
	string return_word_in_direction(Tile* current_tile, string direction, int string_length) {
	
		vector<char> word_from_wordsearch_vect;
		Tile* tile_ptr = current_tile;

		if (direction == "north") {
			for (int i = 0; i < string_length; ++i) {
				word_from_wordsearch_vect.push_back(tile_ptr->letter);
				tile_ptr = move_tile(tile_ptr, "north");
				if (tile_ptr == nullptr) break;
			}
		}
		else if (direction == "northeast") {
			for (int i = 0; i < string_length; ++i) {
				word_from_wordsearch_vect.push_back(tile_ptr->letter);
				tile_ptr = move_tile(tile_ptr, "northeast");
				if (tile_ptr == nullptr) break;
			}
		}
		else if (direction == "east") {
			for (int i = 0; i < string_length; ++i) {
				word_from_wordsearch_vect.push_back(tile_ptr->letter);
				tile_ptr = move_tile(tile_ptr, "east");
				if (tile_ptr == nullptr) break;
			}
		}
		else if (direction == "southeast") {
			for (int i = 0; i < string_length; ++i) {
				word_from_wordsearch_vect.push_back(tile_ptr->letter);
				tile_ptr = move_tile(tile_ptr, "southeast");
				if (tile_ptr == nullptr) break;
			}
		}
		else if (direction == "south") {
			for (int i = 0; i < string_length; ++i) {
				word_from_wordsearch_vect.push_back(tile_ptr->letter);
				tile_ptr = move_tile(tile_ptr, "south");
				if (tile_ptr == nullptr) break;
			}
		}
		else if (direction == "southwest") {
			for (int i = 0; i < string_length; ++i) {
				word_from_wordsearch_vect.push_back(tile_ptr->letter);
				tile_ptr = move_tile(tile_ptr, "southwest");
				if (tile_ptr == nullptr) break;
			}
		}
		else if (direction == "west") {
			for (int i = 0; i < string_length; ++i) {
				word_from_wordsearch_vect.push_back(tile_ptr->letter);
				tile_ptr = move_tile(tile_ptr, "west");
				if (tile_ptr == nullptr) break;
			}
		}
		else if (direction == "northwest") {
			for (int i = 0; i < string_length; ++i) {
				word_from_wordsearch_vect.push_back(tile_ptr->letter);
				tile_ptr = move_tile(tile_ptr, "northwest");
				if (tile_ptr == nullptr) break;
			}
		}
		else {
			Invalid_Direction obj1;
			throw obj1;
		}
		string word_from_wordsearch_str(word_from_wordsearch_vect.begin(), word_from_wordsearch_vect.end());
		return word_from_wordsearch_str;
	}

	// EFFECTS: Given a current tile and a direction, returns a 
	// Tile pointer that is in the given direction from the perspective
	// of the current tile.
	Tile* move_tile(Tile* current_tile, string direction) {
		if (direction == "north") return current_tile->north;
		else if (direction == "northeast") return current_tile->northeast;
		else if (direction == "east") return current_tile->east;
		else if (direction == "southeast") return current_tile->southeast;
		else if (direction == "south") return current_tile->south;
		else if (direction == "southwest") return current_tile->southwest;
		else if (direction == "west") return current_tile->west;
		else if (direction == "northwest") return current_tile->northwest;
		else {
			Invalid_Direction obj1;
			throw obj1;
		}
		return nullptr;
	}

	// EFFECTS: Takes input from an input file and stores each
	// letter inside of a tile. Also sets width and height and
	// stores words in word bank vector.
	void take_input(void) {
		
		ifstream fin1;
		fin1.open(input_board_filename);
		// Set width and height
		string width_str, height_str;
		fin1 >> width_str >> height_str;
		width = stoi(width_str);
		height = stoi(height_str);

		// After getting width and height, create board
		// Don't forget to calculate total number of tiles after
		// getting width and height
		calculate_total_number_of_tiles();
		make_board();
		// Take in letters
		string current_letter;
		int idx = 0;
		while (fin1 >> current_letter) {
			// If lowercase letter, then change to uppercase
			// use lowercase to uppercase
			const char* char_ptr = current_letter.c_str();
			Tile* current_tile = board[idx];
			current_tile->letter = lowercase_to_uppercase(char_ptr);
			++idx;
		}

		// -----------------------------
		// Also, don't forget to create word bank vector
		// -----------------------------
		ifstream fin2;
		fin2.open(word_bank_filename);
		string current_word;
		while (fin2 >> current_word) {
			// I need to find a way to capitalize words from word bank
			// Example:
			// Credit: https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
			//std::string str = "Hello World";
			//std::transform(str.begin(), str.end(), str.begin(), ::toupper);
			string temp_str = current_word;
			transform(temp_str.begin(), temp_str.end(), temp_str.begin(), ::toupper);
			word_bank.push_back(temp_str);
		}
		// Just for better organization, sort word_bank alphabetically
		sort(word_bank.begin(), word_bank.end());
	}

	// EFFECTS: Creates board based on dimensions (width and height)
	void make_board(void) {
		// First, make the tiles in the board
		for (size_t i = 0; i < total_number_of_tiles; ++i) {
			board[i] = new Tile;
		}
		// Next, make assign directional tiles within each tile
		for (int i = 0; i < total_number_of_tiles; ++i) {
			Tile* temp = board[i];
			int current_row = row_index(board[i]);
			int current_col = column_index(board[i]);
			// Case 1: Corner Tile Case
			if (is_corner_tile(board[i])) {
				// Top Left Case
				if (row_index(temp) == 0 && column_index(temp) == 0) {
					temp->north = nullptr;
					temp->northeast = nullptr;
					temp->east = Tile_at(current_row, current_col + 1);
					temp->southeast = Tile_at(current_row + 1, current_col + 1);
					temp->south = Tile_at(current_row + 1, current_col);
					temp->southwest = nullptr;
					temp->west = nullptr;
					temp->northwest = nullptr;
				}
				// Top Right Case
				else if (row_index(temp) == 0 && column_index(temp) == width - 1) {
					temp->north = nullptr;
					temp->northeast = nullptr;
					temp->east = nullptr;
					temp->southeast = nullptr;
					temp->south = Tile_at(current_row + 1, current_col);
					temp->southwest = Tile_at(current_row + 1, current_col - 1);
					temp->west = Tile_at(current_row, current_col - 1);
					temp->northwest = nullptr;
				}
				// Bottom Left Case
				else if (row_index(temp) == height - 1 && column_index(temp) == 0) {
					temp->north = Tile_at(current_row - 1, current_col);
					temp->northeast = Tile_at(current_row - 1, current_col + 1);
					temp->east = Tile_at(current_row, current_col + 1);
					temp->southeast = nullptr;
					temp->south = nullptr;
					temp->southwest = nullptr;
					temp->west = nullptr;
					temp->northwest = nullptr;
				}
				// Bottom Right Case
				else if (row_index(temp) == height - 1 && column_index(temp) == width - 1) {
					temp->north = Tile_at(current_row - 1, current_col);
					temp->northeast = nullptr;
					temp->east = nullptr;
					temp->southeast = nullptr;
					temp->south = nullptr;
					temp->southwest = nullptr;
					temp->west = Tile_at(current_row, current_col - 1);
					temp->northwest = Tile_at(current_row - 1, current_col - 1);
				}
				// For debugging purposes
				else assert(false);
			}
			// Case 2: Edge Tile Case (NOT Corner Tile)
			else if (is_edge_tile(board[i])) {
				// Top Case
				if (row_index(temp) == 0) {
					temp->north = nullptr;
					temp->northeast = nullptr;
					temp->east = Tile_at(current_row, current_col + 1);
					temp->southeast = Tile_at(current_row + 1, current_col + 1);
					temp->south = Tile_at(current_row + 1, current_col);
					temp->southwest = Tile_at(current_row + 1, current_col - 1);
					temp->west = Tile_at(current_row, current_col - 1);
					temp->northwest = nullptr;
				}
				// Left Case
				else if (column_index(temp) == 0) {
					temp->north = Tile_at(current_row - 1, current_col);
					temp->northeast = Tile_at(current_row - 1, current_col + 1);
					temp->east = Tile_at(current_row, current_col + 1);
					temp->southeast = Tile_at(current_row + 1, current_col + 1);
					temp->south = Tile_at(current_row + 1, current_col);
					temp->southwest = nullptr;
					temp->west = nullptr;
					temp->northwest = nullptr;
				}
				// Right Case
				else if (column_index(temp) == width - 1) {
					temp->north = Tile_at(current_row - 1, current_col);
					temp->northeast = nullptr;
					temp->east = nullptr;
					temp->southeast = nullptr;
					temp->south = Tile_at(current_row + 1, current_col);
					temp->southwest = Tile_at(current_row + 1, current_col - 1);
					temp->west = Tile_at(current_row, current_col - 1);
					temp->northwest = Tile_at(current_row - 1, current_col - 1);
				}
				// Bottom Case
				else if (row_index(temp) == height - 1) {
					temp->north = Tile_at(current_row - 1, current_col);
					temp->northeast = Tile_at(current_row - 1, current_col + 1);
					temp->east = Tile_at(current_row, current_col + 1);
					temp->southeast = nullptr;
					temp->south = nullptr;
					temp->southwest = nullptr;
					temp->west = Tile_at(current_row, current_col - 1);
					temp->northwest = Tile_at(current_row - 1, current_col - 1);
				}
				// For debugging purposes
				else assert(false);
			}
			// Case 3: Middle Tile Case
			else {
				temp->north = Tile_at(current_row - 1, current_col);
				temp->northeast = Tile_at(current_row - 1, current_col + 1);
				temp->east = Tile_at(current_row, current_col + 1);
				temp->southeast = Tile_at(current_row + 1, current_col + 1);
				temp->south = Tile_at(current_row + 1, current_col);
				temp->southwest = Tile_at(current_row + 1, current_col - 1);
				temp->west = Tile_at(current_row, current_col - 1);
				temp->northwest = Tile_at(current_row - 1, current_col - 1);
			}
		}
	}

	// EFFECTS: Calculates total number of tiles based on width
	// and height
	void calculate_total_number_of_tiles(void) {
		total_number_of_tiles = width * height;
	}

	// EFFECTS: Returns true if tile is a corner tile
	bool is_corner_tile(Tile* temp) const {
		if ((row_index(temp) == 0 && column_index(temp) == 0) ||
			(row_index(temp) == 0 && column_index(temp) == width - 1) ||
			(row_index(temp) == height - 1 && column_index(temp) == 0) ||
			(row_index(temp) == height - 1 && column_index(temp) == width - 1)) return true;
		return false;
	}

	// EFFECTS: Returns true if tile is an edge tile and not a
	// corner tile
	bool is_edge_tile(Tile* temp) const {
		// Note: Edge NOT Corner
		if (is_corner_tile(temp)) return false;
		else if (row_index(temp) == 0 || column_index(temp) == 0 ||
			column_index(temp) == width - 1 || row_index(temp) == height - 1) return true;
		else return false;
	}

	// EFFECTS: Returns pointer to tile given row and column
	Tile* Tile_at(int row, int col) {
		return board[row * width + col];
	}

	// EFFECTS: Given row and column indexes, returns tile index
	// Example, if board is 10x10:
	// Row 0 Col 0 = Tile 0
	// Row 0 Col 5 = Tile 5
	// Row 9 Col 9 = Tile 99
	int tile_index(int row, int col) {
		return row * width + col;
	}

	// EFFECTS: Returns row index given pointer to tile
	// Note: row_index function is O(n) (this is super slow)
	int row_index(Tile* tile_ptr) const {
		Tile** temp = board_start;
		while (*temp != tile_ptr) ++temp;

		int board_index = temp - board_start;
		int row = (board_index - column_index(tile_ptr)) / width;
		return row;
	}

	// EFFECTS: Returns column index given pointer to tile
	// Note: column_index function is O(n) (this is super slow)
	int column_index(Tile* tile_ptr) const {
		Tile** temp = board_start;
		while (*temp != tile_ptr) ++temp;

		int board_index = temp - board_start;
		int column = board_index % width;
		return column;
	}

	// EFFECTS: Changes inputted character to uppercase.
	char lowercase_to_uppercase(const char* x) {
		if (x[0] == 'A' || x[0] == 'a') return 'A';
		else if (x[0] == 'B' || x[0] == 'b') return 'B';
		else if (x[0] == 'C' || x[0] == 'c') return 'C';
		else if (x[0] == 'D' || x[0] == 'd') return 'D';
		else if (x[0] == 'E' || x[0] == 'e') return 'E';
		else if (x[0] == 'F' || x[0] == 'f') return 'F';
		else if (x[0] == 'G' || x[0] == 'g') return 'G';
		else if (x[0] == 'H' || x[0] == 'h') return 'H';
		else if (x[0] == 'I' || x[0] == 'i') return 'I';
		else if (x[0] == 'J' || x[0] == 'j') return 'J';
		else if (x[0] == 'K' || x[0] == 'k') return 'K';
		else if (x[0] == 'L' || x[0] == 'l') return 'L';
		else if (x[0] == 'M' || x[0] == 'm') return 'M';
		else if (x[0] == 'N' || x[0] == 'n') return 'N';
		else if (x[0] == 'O' || x[0] == 'o') return 'O';
		else if (x[0] == 'P' || x[0] == 'p') return 'P';
		else if (x[0] == 'Q' || x[0] == 'q') return 'Q';
		else if (x[0] == 'R' || x[0] == 'r') return 'R';
		else if (x[0] == 'S' || x[0] == 's') return 'S';
		else if (x[0] == 'T' || x[0] == 't') return 'T';
		else if (x[0] == 'U' || x[0] == 'u') return 'U';
		else if (x[0] == 'V' || x[0] == 'v') return 'V';
		else if (x[0] == 'W' || x[0] == 'w') return 'W';
		else if (x[0] == 'X' || x[0] == 'x') return 'X';
		else if (x[0] == 'Y' || x[0] == 'y') return 'Y';
		else if (x[0] == 'Z' || x[0] == 'z') return 'Z';
		else {
			Invalid_Character exception1;
			throw exception1;
		}
	}

	// EFFECTS: Prints board with row and column numbers
	void print_board(void) {
		cout << "Word Search Puzzle Inputted:" << endl;
		// Print column
		cout << " " << " " << " ";
		for (int col = 0; col < width; ++col) {
			if (col < 10) cout << col << "  ";
			else cout << col << " ";
		}
		cout << endl;
		for (int row = 0; row < height; ++row) {
			if (row < 10) cout << row << " " << " ";
			else cout << row << " ";
			for (int col = 0; col < width; ++col) {
				Tile* current_tile = Tile_at(row, col);
				// If the tile has a mine, print X
				/*if (current_tile->has_mine == true) cout << "X" << " " << " ";
				else {
					if (current_tile->number_of_nearby_mines == 0) cout << " " << "  ";
					else cout << current_tile->number_of_nearby_mines << "  ";
				}*/
				cout << current_tile->letter << " " << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << "Summary:" << endl;
	}
};

// main function
int main(int argc, char** argv) {

	if (argc != 3) {
		Invalid_Arguments inst2;
		throw inst2;
	}

	// argv[0] is executable
	string input_board_filename = argv[1];
	string word_bank_filename = argv[2];

	word_search_puzzle_solver inst1(input_board_filename, word_bank_filename);
	inst1.run_solver();
}