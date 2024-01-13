//@Pinton Mattia

//##################### INCLUDES #####################
#include "Board.h"	 	
#include "Player.h"
#include "Position.h"
#include "MonopolyGame.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "Tile.h"
//##################### COSTRUTTORE #####################
Board::Board()
{
	//creo un array seecondario dove metto tutte le tile tranne gli angoli che verranno aggiunto dopo
	std::vector<Tile::TileType> shuffledeck;
	for (int i = 0; i < (BOARD_SIZE-SIDE_TILES); i++) {
		if (i < ECO_TILES) {
			//nelle posizioni da 0 a (#ecotiles - 1) metto tiles di tipo ECO
			shuffledeck.push_back(Tile::TileType::ECONOMICA);
		}
		else if (i < STD_TILES+ECO_TILES ) {
			//nelle posizioni da #ecotiles a (#ecotiles+  #stdtiles - 1) metto tiles di tipo STD
			shuffledeck.push_back(Tile::TileType::STANDARD);
		}
		else{
			//nelle posizioni rimanenti metto tiles di tipo LUSSO
			shuffledeck.push_back(Tile::TileType::LUSSO);
		}
	}
	//ora faccio lo shuffle dell'array secondario
	std::random_shuffle(shuffledeck.begin(), shuffledeck.end() );

	//posiziono la tile casuale nell'array finale facendo il pop nell'array ausiliario
	for (int i = 0; i < BOARD_SIZE; i++) {
		//se la posizione corrente è divisibile per 4, allora sono in un angolo della tabella 
		if (i % (BOARD_SIZE / 4) == 0) {
			m_tiles[i] = std::make_shared<Tile>(Tile::TileType::ANGOLARE,Position(i));
		}
		else {
			m_tiles[i] = std::make_shared<Tile>(shuffledeck.back(),Position(i));
			shuffledeck.pop_back();
		}
	}
	
}
//##################### FUNZIONI #####################


std::ostream& Board::print(std::ostream& os, std::vector<std::shared_ptr<Player>>& arr) const {

	constexpr int N_ELEM_RIGHE = (BOARD_SIZE / 4) + 1; // numero elementi riga in alto e in basso
	constexpr int N_ELEM_COLONNE = (BOARD_SIZE / 4) - 1; //tutti e 4 gli angoli sono compresi fra gli elementi delle righe
	constexpr int TILE_WIDTH = 4 + MonopolyGame::N_PLAYER + 2; //=> ' ' + '|' + "TipoTerreno" + "TipoStruttura" + no.players + '|' + ' '
	constexpr int INDENTAZIONE = 4; //quanti spazi fra le coordinate numeriche e la prima colonna del tabellone

	//STAMPA COORDINATE NUMERICHE
	//il primo numero dipende dall'indetazione
	for (int i = 0; i < INDENTAZIONE + (TILE_WIDTH / 2); i++) {
		os << " ";
	}
	//dopo i primi spazi stampo il primo numero
	os << "1";
	//da qui in poi i numeri saranno sempre circa a meta' tile
	for (int i = 2; i <= N_ELEM_RIGHE; i++) {
		for (int j = 1; j < TILE_WIDTH; j++) {
			os << " ";
		}
		os << i;
	}

	//-------------------- STAMPA PRIMA RIGA --------------------
	os << "\n\nA";
	for (int i = 0; i < INDENTAZIONE; i++) {
		os << " ";
	}
	//devo stampare gli elementi della terza segmentazione 
	//segmentazioni dell' array di Board:
	//( base inferiore tabellone -> colonna sinistra -> [base superiore] -> colonna detra )
	for (int i = N_ELEM_COLONNE + N_ELEM_RIGHE, p = 0; i < N_ELEM_COLONNE + 2 * N_ELEM_RIGHE; i++) {
		os << " |" << *m_tiles[i];
		//gestione per la visulizzazione dei player presenti sulla tabella attuale
		while (p < arr.size()) {
			if (arr[p] && (i == arr[p]->get_posizione().get_valore())) {
				//se la tile che sto ispezionando contiene il player della cella [p] dell'array dei player
				//passata alla funzione, stapo il tag del player
				os << arr[p]->get_tag();
			}
			else {
				//ho deciso di tenere costante la lunghezza dei tile, quindi devo rimpiazzare il tag
				// del giocatore che non e' presente con uno spazio
				os << " ";
			}
			p++; //avanzo nell'ispezione dell'array dei player
		}
		p = 0;
		os << "| ";
	}

	//-------------------- STAMPA COLONNE --------------------
	char caratt = 'B';
	os << "\n\n";
	//devo stampare contemporaneamente gli elementi delle due colonne 
	//(base inferiore tabellone -> [colonna sinistra] -> base superiore -> [colonna detra])
	for (int i = 0, c1 = N_ELEM_COLONNE + N_ELEM_RIGHE - 1, c2 = N_ELEM_RIGHE * 2 + N_ELEM_COLONNE, p = 0; // c1 : colonna sx, c2: colonna dx
		i < N_ELEM_COLONNE; i++) {

		//stampo gli spazi iniziali
		os << "\n" << caratt;
		for (int j = 0; j < INDENTAZIONE; j++) {
			os << " ";
		}

		//stampa di tile
		os << " |" << *m_tiles[c1];
		while (p < arr.size()) {
			if (arr[p] && (c1 == arr[p]->get_posizione().get_valore())) {
				os << arr[p]->get_tag();
			}
			else {
				os << " ";
			}
			p++;
		}
		p = 0;
		os << "| ";
		//spazio fra le due colonne
		for (int i = 0; i < N_ELEM_COLONNE * TILE_WIDTH; i++) {
			os << " ";
		}
		//stampa della seconda tile
		os << " |" << *m_tiles[c2];
		while (p < arr.size()) {
			if (arr[p] && (c2 == arr[p]->get_posizione().get_valore())) {
				os << arr[p]->get_tag();
			}
			else {
				os << " ";
			}
			p++;
		}
		p = 0;
		os << "|\n\n";
		c1--;
		c2++;
		caratt++;
	}

	//-------------------- STAMPA ULTIMA RIGA --------------------
	//devo stampare contemporaneamente gli elementi della base inferiore 
	//( [base inferiore tabellone] -> colonna sinistra -> base superiore -> colonna detra )
	os << "\n" << caratt;
	for (int i = 0; i < INDENTAZIONE; i++) {
		os << " ";
	}
	for (int i = N_ELEM_RIGHE - 1, p = 0; i >= 0; i--) {
		if (i != 0) {
			os << " |" << *m_tiles[i];
		}
		else {
			os << " |P ";
		}
		while (p < arr.size()) {
			if (arr[p] && (i == arr[p]->get_posizione().get_valore())) {
				os << arr[p]->get_tag();
			}
			else {
				os << " ";
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
	p.set_valore((old_pos + n) % BOARD_SIZE); // se supero board size, prende solo il resto ( riparte da 0 )
	//se la vecchia posizione e' maggiore della nuova, necessariamente sono passato dal via
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
