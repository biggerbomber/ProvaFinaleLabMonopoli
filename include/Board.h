//@Pinton Mattia 2066703

#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
#include "Position.h"
#include "Player.h"
#include <array>
class Board{
public:
    const static int BOARD_SIZE = 28;
    const static int ECO_TILES = 8;
    const static int STD_TILES = 10;
    const static int LUX_TILES = 6;
    const static int SIDE_TILES = 4;

    Board();

    Position get_partenza()const {return Position(0);}

    const std::shared_ptr<Tile>& get_tile(Position p) const { return m_tiles[p.get_valore()]; };
    
    //restituisce true se si passa dal via
    bool avanza_e_controlla(Position&,int) const;

    bool is_valid_position(Position) const;

    std::shared_ptr<Tile> get_tile(Position& p) { return m_tiles[p.get_valore()]; };

    std::ostream& print(std::ostream&, const std::vector<std::shared_ptr<Player>>&) const;
private:
    std::array<std::shared_ptr<Tile>,BOARD_SIZE> m_tiles;
};

std::ostream& operator<<(std::ostream&, const Board&);


#endif