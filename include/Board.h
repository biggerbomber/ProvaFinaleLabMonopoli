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

    Position get_partenza()const;

    const Tile& get_tile(Position) const;
    Tile& get_tile(Position);

    void set_tile(const Tile&, const Position&);

    bool avanza_e_controlla(Position&,int) const;//retsituisce true se si passa dal via

    bool is_valid_position(Position) const;

    //da espandere se serve
private:
    std::array<Tile,BOARD_SIZE> m_tiles;
};

std::ostream operator<<(std::ostream&, const Board&);


#endif