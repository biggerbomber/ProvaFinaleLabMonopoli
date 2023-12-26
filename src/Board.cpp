//@Pinton Mattia

//##################### INCLUDES #####################
#include "Board.h"	 	
#include <algorithm>
#include <iostream>
#include <vector>
#include "Tile.h"
//##################### COSTRUTTORE #####################
Board::Board()
{
	static int ECO_TILES = 8;
	static int STD_TILES = 10;
	static int LUX_TILES = 6;
	static int SIDE_TILES = 4;

	std::vector<Tile::TileType> shuffledeck;
	std::cout <<"PUSH ARRAY AUX" << "\n";
	for (int i = 0; i < (BOARD_SIZE-SIDE_TILES); i++) {
		if (i < ECO_TILES) {
			shuffledeck.push_back(Tile::TileType::ECONOMICA);
			std::cout << "E ";
		}
		else if (i < STD_TILES+ECO_TILES ) {
			shuffledeck.push_back(Tile::TileType::STANDARD);
			std::cout << "S ";
		}
		else{
			shuffledeck.push_back(Tile::TileType::LUSSO);
			std::cout << "L ";
		}
	}
	std::cout << "\n\n SHUFFLE \n";
	std::random_shuffle(shuffledeck.begin(), shuffledeck.end() );

	for (int i = 0; i < BOARD_SIZE; i++) {
		if (i % (BOARD_SIZE / 4) == 0) {
			m_tiles[i] = std::make_shared<Tile>(Tile::TileType::ANGOLARE);
			std::cout << "(A)";
		}
		else {
			m_tiles[i] = std::make_shared<Tile>(shuffledeck.back());
			std::cout << shuffledeck.back();
			shuffledeck.pop_back();
		}
	}
	
}
//##################### FUNZIONI #####################
//##################### OUTPUT OSTREAM #####################

std::ostream& operator<<(std::ostream& os, const Board& b) {
	//std::string s;
	for (int i = 0; i < Board::BOARD_SIZE; i++) {
		/*
		std::cout << "casella "<< i<< ":\n";
		os << b.m_tiles[i]->get_tile_type();
		std::cout <<"\n";
		*/
		os << *b.get_tile(Position(i));
	}
	return os;
}

std::ostream& Board::print(std::ostream& os, std::vector<...> arr) const {
	for (int i = 0, p = 0; i < BOARD_SIZE; i++) {
		os << "|" << *m_tiles[i];
		while (p < arr.size()) {
			if (arr[p]) {
				os << arr[p]->get_tag();
			}

			p++;
		}
		std::cout << "sono qua" << i;
		p = 0;
	}
	return os;

	return os << "|";
}