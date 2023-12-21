//@Barbato Alberto 2073961


#ifndef PLAYER_H
#define PLAYER_H
#include "Player.h"
#include <vector>

class Tile{
public:
    enum TileType { ANGOLARE, ECONOMICA, STANDARD, LUSSO};
    enum BuildType { VUOTA, CASA, ALBERGO };

    const static std::vector<int> s_costo_tereno;

    int a;
    Tile();

};






#endif