//@Casucci Leonardo 2073980

#include "../include/Bot.h"

Bot::Bot(int tag, Position p,MonopolyGame* pmg) {// problema qui " impossibile fare riferimento al costruttore predefinito player, e' una funzione eliminata"
    m_tag = tag;
    m_posizione = p;
    m_budget = 100; //budget di partenza
    mg = pmg;

}

bool Bot::gestisci_casella(std::shared_ptr<Tile> t) {
    srand((unsigned)time(0));
    int i;
    if (t->get_tile_type() != Tile::TileType::ANGOLARE) {
        if (!t->has_proprietario()) {
            srand((unsigned)time(0));
            i = (rand() % 4) + 1;
            if (i == 1) { // 1 numero puramente arbitrario ma con P(1)=1/4
                aggiungi_possedimento(t);
                
            }
        }
        else {
            if (t->get_proprietario()->get_tag() == m_tag) {
                i = (rand() % 4) + 1;
                if (i == 1 && t->get_costo_miglioramento()<m_budget) {
                    switch (t->get_build_type()) {
                    case Tile::BuildType::VUOTA :
                        paga(t->get_costo_miglioramento());
                        t->set_build_type(Tile::BuildType::CASA);
                        break;
                    case Tile::BuildType::CASA :
                        paga(t->get_costo_miglioramento());
                        t->set_build_type(Tile::BuildType::ALBERGO);
                        break;
                    case Tile::BuildType::ALBERGO :
                        std::cout << "Miglioramento massimo già raggiunto\n";
                        break;
                    }  
                }
            }
            else {
                if (!paga(t->get_costo_pernottamento())) {
                    eliminato = true;
                    libera_possedimenti(m_possedimenti);
                    return false;
                }
            }
        }
    }
    return true;
}