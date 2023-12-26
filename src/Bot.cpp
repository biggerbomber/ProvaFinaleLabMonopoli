//@Casucci Leonardo 2073980

#include "Bot.h"

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
                mg->log(Logger::ACQUISTO_TERRENO, m_tag, m_posizione);
                // la modifica della posizione va fatta prima di chiamare gestisci casella senno non funziona 
            }
        }
        else {
            if (t->get_proprietario()->get_tag() == m_tag) {
                i = (rand() % 4) + 1;
                if (i == 1 && t->get_costo_miglioramento()<m_budget) {
                    migliora_terreno(mg, t, this);
                }
            }
            else {
                if (!paga(t->get_costo_pernottamento())) {
                    m_eliminato = true;
                    libera_possedimenti(m_possedimenti);
                    t->get_proprietario()->riscuoti(m_budget);
                    mg->log(Logger::ELIMINAZIONE, m_tag);
                    return false;
                }
                else {
                     t->get_proprietario()->riscuoti(t->get_costo_pernottamento());
                     mg->log(Logger::PAGAMENTO_PERNOTTAMENTO, m_tag, m_posizione, t->get_proprietario()->get_tag(), t->get_costo_pernottamento());
                }
            }
        }
    }
    return true;
}