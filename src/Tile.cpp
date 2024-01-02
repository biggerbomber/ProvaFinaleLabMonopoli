#include "Tile.h"
//@Barbato Alberto 2073961
#include "Tile.h"
#include "MonopolyGame.h"

Tile::Tile(Tile::TileType tt, Position pos) 
      :m_tile_type{ tt }, m_pos{ pos }
{
  m_build_type = Tile::BuildType::VUOTA;
  m_posseduta = false;
}

int Tile::get_proprietario() const{
  if (has_proprietario()) {
    return m_proprietario;
  }
  throw std::invalid_argument("La Tile non ha un proprietario");
}
int Tile::get_costo_terreno() const {
  std::array<int, Tile::N_TILE_TYPE> costo_terreno = { 0,6,10,20 };
  return costo_terreno[m_tile_type];
}
int Tile::get_costo_pernottamento() const {
  static std::array<std::array<int, Tile::N_BUILD_TYPE>, Tile::N_TILE_TYPE> costo_pernottamento
  { { //vuota,casa,albergo
      {0,0,0}, // terreno angolare
      {0,2,4}, // economico
      {0,4,8}, //standard
      {0,7,14} //lusso
  } }; 
  return costo_pernottamento[m_tile_type][m_build_type];
}

int Tile::get_costo_miglioramento() const {
  static std::array<std::array<int, Tile::N_BUILD_TYPE>, Tile::N_TILE_TYPE> costo_miglioramneto
  { { //vuota,casa,albergo
      {0,0,0}, // terreno angolare
      {3,3,0}, // economico
      {5,5,0}, //standard
      {10,10,0} //lusso
  } };
  return costo_miglioramneto[m_tile_type][m_build_type];
}

void Tile::set_proprietario(std::shared_ptr<Player> prop)
{
  if (prop) {
    m_posseduta = true;
    m_proprietario = prop->get_tag();
  }
}

std::ostream& operator<<(std::ostream& os, const Tile& tile) {
  os <<tile.get_tile_type() << tile.get_build_type();
  return os;
}


std::ostream& operator<<(std::ostream& os, const Tile::TileType& t_type) {

  std::array<char, Tile::N_TILE_TYPE> tiletype_charset = { ' ','E','S','L' };
  return os << tiletype_charset[t_type];
};

std::ostream& operator<<(std::ostream& os, const Tile::BuildType& b_type) {
  if (b_type == Tile::BuildType::VUOTA) {
    return os<<" ";
  }
  std::array<char, Tile::N_BUILD_TYPE> buildtype_charset = {'?','*','^'};
  return os << buildtype_charset[b_type];
};
