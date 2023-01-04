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


using namespace std;

// Exceptions
/*...*/

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

public:
	
	// Default Constructor
	word_search_puzzle_solver() {
		board_start = board;
	}


	// EFFECTS: Takes input from an input file and stores each
	// letter inside of a tile. Also calculates width and height
	void take_input(void) {
		istringstream string_in;
		
		// -----------------------------
		// Left off on taking input to create board
		// Also, don't forget word bank
		// -----------------------------



	}



	// EFFECTS: Runs solver
	void run_solver(void) {
		
	}


	// EFFECTS: Creates board based on dimensions (width and height)
	// The place_mines() function will be responsible for placing mines after
	// make_board() is called
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

};