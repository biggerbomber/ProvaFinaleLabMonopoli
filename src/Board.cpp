//@Pinton Mattia

//##################### INCLUDES #####################
#include "Board.h"	 	
#include "Player.h"
#include "Position.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "Tile.h"
//##################### COSTRUTTORE #####################
Board::Board()
{
	std::vector<Tile::TileType> shuffledeck;
	//std::cout <<"PUSH ARRAY AUX" << "\n";
	for (int i = 0; i < (BOARD_SIZE-SIDE_TILES); i++) {
		if (i < ECO_TILES) {
			shuffledeck.push_back(Tile::TileType::ECONOMICA);
			//std::cout << "E ";
		}
		else if (i < STD_TILES+ECO_TILES ) {
			shuffledeck.push_back(Tile::TileType::STANDARD);
			//std::cout << "S ";
		}
		else{
			shuffledeck.push_back(Tile::TileType::LUSSO);
			//std::cout << "L ";
		}
	}
	//std::cout << "\n\n SHUFFLE \n";
	std::random_shuffle(shuffledeck.begin(), shuffledeck.end() );

	for (int i = 0; i < BOARD_SIZE; i++) {
		if (i % (BOARD_SIZE / 4) == 0) {
			m_tiles[i] = std::make_shared<Tile>(Tile::TileType::ANGOLARE,Position(i));
			//std::cout << "(A)";
		}
		else {
			m_tiles[i] = std::make_shared<Tile>(shuffledeck.back(),Position(i));
			//std::cout << shuffledeck.back();
			shuffledeck.pop_back();
		}
	}
	
}
//##################### FUNZIONI #####################

std::ostream& Board::print(std::ostream& os, std::vector<std::shared_ptr<Player>> arr) const {

	const int N_ELEM_RIGHE = (BOARD_SIZE / 4) + 1; // numero elementi riga in alto e in basso
	const int N_ELEM_COLONNE = (BOARD_SIZE / 4) - 1; //tutti e 4 gli angoli sono compresi fra gli elementi delle righe

	//STAMPA PRIMA RIGA
	for (int i = N_ELEM_COLONNE + N_ELEM_RIGHE, p = 0; i < N_ELEM_COLONNE + 2 * N_ELEM_RIGHE; i++) {
		os << " |" << *m_tiles[i];
		while (p < arr.size()) {
			if (arr[p] && (i == arr[p]->get_posizione().get_valore())) {
				os << arr[p]->get_tag();
			}
			p++;
		}
		p = 0;
		os << "| ";
	}
	os << "\n";

	//STAMPA COLONNE
	for (int i = 0, c1 = N_ELEM_COLONNE + N_ELEM_RIGHE - 1, c2 = N_ELEM_RIGHE * 2 + N_ELEM_COLONNE, p = 0;
		i < N_ELEM_COLONNE; i++) {

		os << " |" << *m_tiles[c1];
		while (p < arr.size()) {
			if (arr[p] && (c1 == arr[p]->get_posizione().get_valore())) {
				os << arr[p]->get_tag();
			}
			p++;
		}
		p = 0;
		os << "|                                ";
		os << " |" << *m_tiles[c2];
		while (p < arr.size()) {
			if (arr[p] && (c2 == arr[p]->get_posizione().get_valore())) {
				os << arr[p]->get_tag();
			}
			p++;
		}
		p = 0;
		os << "|\n";
		c1--;
		c2++;
	}

	//STAMPA ULTIMA RIGA
	for (int i = N_ELEM_RIGHE - 1, p = 0; i >= 0; i--) {
		os << " |" << *m_tiles[i];
		while (p < arr.size()) {
			if (arr[p] && (i == arr[p]->get_posizione().get_valore())) {
				os << arr[p]->get_tag();
			}
			p++;
		}
		p = 0;
		os << "| ";
	}
	return os << "\n";
}

bool Board::avanza_e_controlla(Position& p, int n) const {//retsituisce true se si passa dal via
	int old_pos = p.get_valore();
	p.set_valore((old_pos + n) % BOARD_SIZE);
	if (p.get_valore() < old_pos) {
		return true;
	}
	else return false;
}

bool Board::is_valid_position(Position p) const {
	if (p.get_valore() > 0 && p.get_valore() < BOARD_SIZE)return true;
	else return false;
}




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
