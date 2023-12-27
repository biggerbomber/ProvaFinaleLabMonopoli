//@Pinton Mattia

//##################### INCLUDES #####################
#include "Board.h"	 	
#include "Player.h"	 	
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
	//FUNZIONANTE
	/*
	for (int i = 0; i < Board::BOARD_SIZE; i++) {
		os << " |" << *b.get_tile(Position(i));
		if (b.get_tile(Position(i))->has_proprietario())os << "P| ";
	}
	*/
	os << "\n\n\n\n";
	for (int i = 14; i < 22; i++) {
		os << " |" << *b.get_tile(Position(i));
		if (b.get_tile(Position(i))->has_proprietario())os << "P";
		os << "| ";
	}
	os << "\n";
	for (int i = 0, c1=13,c2 = 22; i < 6; i++) {
		os << " |" << *b.get_tile(Position(c1));
		if (b.get_tile(Position(c1))->has_proprietario())os << "P";
		os << "|                               ";
		os << " |" << *b.get_tile(Position(c2));
		if (b.get_tile(Position(c2))->has_proprietario())os << "P";
		os << "| \n";
		c1--;
		c2++;
	}
	for (int i = 7; i >= 0 ; i--) {
		os << " |" << *b.get_tile(Position(i));
		if (b.get_tile(Position(i))->has_proprietario())os << "P";
		os << "| ";
	}
	os << "\n\n\n\n";
	return os;
}

std::ostream& Board::print(std::ostream& os, std::vector<std::shared_ptr<Player>> arr) const {
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
