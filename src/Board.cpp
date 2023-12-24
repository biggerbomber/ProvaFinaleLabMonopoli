//@Pinton Mattia

//##################### INCLUDES #####################
#include "../include/Board.h"	 	
#include <algorithm>
#include <iostream>
#include <vector>
#include "../include/Tile.h"
//##################### COSTRUTTORE #####################
Board::Board()
{
	static int ECO_TILES = 8;
	static int STD_TILES = 10;
	static int LUX_TILES = 6;
	static int SIDE_TILES = 4;

	std::vector<Tile::TileType> shuffledeck(BOARD_SIZE);
	for (int i = 0; i < (BOARD_SIZE-SIDE_TILES); i++) {
		if (i < ECO_TILES) {
			shuffledeck.push_back(Tile::TileType::ECONOMICA);
		}
		else if (i < STD_TILES) {
			shuffledeck.push_back(Tile::TileType::STANDARD);
		}
		else{
			shuffledeck.push_back(Tile::TileType::LUSSO);
		}
	}
	std::random_shuffle(shuffledeck.begin(), shuffledeck.end());

	for (int i = 0; i < BOARD_SIZE; i++) {
		if (i % (BOARD_SIZE / 4) == 0) {
			m_tiles[i] = std::make_shared<Tile>(Tile::TileType::ANGOLARE);
		}
		else {
			m_tiles[i] = std::make_shared<Tile>(shuffledeck.back());
			shuffledeck.pop_back();
		}
	}
	
}
//##################### FUNZIONI #####################
std::shared_ptr<Tile> Board::get_tile(Position& p) {
	return m_tiles[p.get_valore()];
}

//##################### OUTPUT OSTREAM #####################

std::ostream& operator<<(std::ostream& os, const Board& b) {
	return os;
}