//@Barbato alberto 2073961

#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
#include "Position.h"
#include <array>
class Board{
public:
    const static int BOARD_SIZE = 28;
    Board();

    Position get_partenza()const {return Position(0);}

    const std::shared_ptr<Tile>& get_tile(Position p) const { return m_tiles[p.get_valore()]; };

    void set_tile(const Tile&, const Position&);

    bool avanza_e_controlla(Position&,int) const;//retsituisce true se si passa dal via

    bool is_valid_position(Position) const;

    std::shared_ptr<Tile> get_tile(Position& p) { return m_tiles[p.get_valore()]; };
    //TODO: Funzione PrintBoard che prende un ostream e un array di shared_prt<Player>(Eventualmente a nullptr) per poter stampare le i player o no, a seconda 
    //da espandere se serve
    std::ostream& print(std::ostream&, std::vector<std::shared_ptr<Player>>) const;
private:
    std::array<std::shared_ptr<Tile>,BOARD_SIZE> m_tiles;
};

std::ostream& operator<<(std::ostream&, const Board&);


#endif