//@Barbato Alberto 2073961


#ifndef TILE_H
#define TILE_H
#include "Position.h"
#include <array>
#include <iostream>
#include <memory>

class Tile{
public:
  static const int N_TILE_TYPE=4;
  enum TileType { ANGOLARE, ECONOMICA, STANDARD, LUSSO};
  static const int N_BUILD_TYPE=3;
  enum BuildType { VUOTA, CASA, ALBERGO };

  Tile(TileType,Position);

  TileType get_tile_type() const { return m_tile_type; };
  BuildType get_build_type() const { return m_build_type; };
  int get_proprietario() const;
  int get_costo_terreno() const;
  int get_costo_pernottamento() const;
  int get_costo_miglioramento() const;
  Position get_position()const { return m_pos; };

  void set_tile_type(TileType tt) { m_tile_type = tt; };
  void set_build_type(BuildType bt) { m_build_type = bt; };
  void set_proprietario(int);
  void set_position(Position p) { m_pos = p; };
  void rimuovi_proprietario() { m_posseduta = false; };

  bool has_proprietario() const { return m_posseduta; };
private:
  TileType m_tile_type;
  BuildType m_build_type;
  Position m_pos;
  bool m_posseduta{ false };
  int m_proprietario;
};


std::ostream& operator<<(std::ostream&,const Tile&);
std::ostream& operator<<(std::ostream&,const Tile::TileType&);
std::ostream& operator<<(std::ostream&,const Tile::BuildType&);




#endif