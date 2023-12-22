//@Barbato Alberto 2073961


#ifndef TILE_H
#define TILE_H
#include <array>
#include <iostream>

class Tile{
public:
    const static int N_TILE_TYPE=4;
    enum TileType { ANGOLARE, ECONOMICA, STANDARD, LUSSO};
    const static int N_BUILD_TYPE=3;
    enum BuildType { VUOTA, CASA, ALBERGO };

    const static std::array<int,N_TILE_TYPE> s_costo_tereno;
    const static std::array<std::array<int,N_TILE_TYPE>,N_BUILD_TYPE> s_costo_miglioramento;
    const static std::array<std::array<int,N_TILE_TYPE>,N_BUILD_TYPE> s_costo_pernottamento;


    Tile(TileType);

    TileType get_tile_type() const;
    BuildType get_build_type() const;
    //Enum player get

    void set_tile_type(TileType);
    void set_build_type(BuildType);
     //Enum player set
private:
    TileType m_tile_type;
    BuildType m_build_type;
    //Da aggiungere referendce all enum di monopli game PROPRIETARIO

};


std::ostream& operator<<(std::ostream&,const Tile&);
std::ostream& operator<<(std::ostream&,const Tile::TileType&);
std::ostream& operator<<(std::ostream&,const Tile::BuildType&);




#endif