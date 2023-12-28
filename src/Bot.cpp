//@Casucci Leonardo 2073980

#include "Bot.h"

Bot::Bot(int tag, Position p) {// problema qui " impossibile fare riferimento al costruttore predefinito player, e' una funzione eliminata"
    m_tag = tag;
    m_posizione = p;
    m_budget = BUDGET_PARTENZA; //budget di partenza
}

EventType Bot::gestisci_casella(std::shared_ptr<Tile> t) {
    int i;
    if (t->get_tile_type() != Tile::TileType::ANGOLARE) {
        if (!t->has_proprietario()) {
            i = (rand() % 4) + 1;
            if (i == 1 && t->get_costo_miglioramento() < m_budget) { // 1 numero puramente arbitrario ma con P(1)=1/4
                return EventType::ACQUISTO_TERRENO;
            }
        }
        else {
            if (t->get_proprietario() == m_tag) {
                i = (rand() % 4) + 1;
                if (i == 1 && t->get_costo_miglioramento()<m_budget) {
                    if (t->get_build_type() == Tile::BuildType::VUOTA) {
                        return EventType::COSTRUZIONE_CASA;
                    }
                    else if (t->get_build_type() == Tile::BuildType::CASA) {
                        return EventType::COSTRUZIONE_ALBERGO;
                    }
                    else {
                        return EventType::FINE_TURNO;
                    }
                }
            }
            else {
                if (m_budget<t->get_costo_pernottamento()) {
                    return EventType::ELIMINAZIONE;
                }
                else {
                    return EventType::PAGAMENTO_PERNOTTAMENTO;
                }
            }
        }
    }
    return EventType::FINE_TURNO;
}