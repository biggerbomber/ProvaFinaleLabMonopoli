//@Casucci Leonardo 2073980

#include "../include/Human.h"

Human::Human(int tag, Position p, MonopolyGame* pmg)
{
    m_tag = tag;
    m_posizione = p;
    m_budget = 100; //budget di partenza
    mg = pmg;
}

bool Human::gestisci_casella(std::shared_ptr<Tile> t)
{   
    std::string risposta;
    if (t->get_tile_type()!=Tile::TileType::ANGOLARE) {
        if (!t->has_proprietario()) {
            if (t->get_costo_terreno() < m_budget) {
                std::cout << "Vuoi acquistare il terreno?(Y/N)\n";
                std::cin >> risposta;
                if (risposta == "Y") {
                    paga(t->get_costo_terreno());
                    aggiungi_possedimento(t);
                    t->set_proprietario(mg->get_player_from_tag(m_tag));
                }
                else if (risposta != "N") {
                    std::cout << "Risposta non valida.\n";
                    //contiua a chiedere fino a che la risposta non e' valida + show
                }
            }
        }
        else {
            if (t->get_proprietario()->get_tag() == m_tag) {
                std::cout << "Il terreno e' già in tuo possesso, vuoi migliorarlo?(Y/N)\n";
                std::cout << "Costruzione attuale: " << t->get_build_type() << " , Costo miglioramento: " << t->get_costo_miglioramento()<<'\n';
                std::cin >> risposta;
                if (risposta=="Y") {
                    switch (t->get_build_type()) {
                    case Tile::BuildType::VUOTA:
                        paga(t->get_costo_miglioramento());
                        t->set_build_type(Tile::BuildType::CASA);
                        break;
                    case Tile::BuildType::CASA:
                        paga(t->get_costo_miglioramento());
                        t->set_build_type(Tile::BuildType::ALBERGO);
                        break;
                    case Tile::BuildType::ALBERGO:
                        std::cout << "Miglioramento massimo già raggiunto\n";
                        break;
                    }
                }
                else if (risposta != "N") {
                    std::cout << "Risposta non valida.\n";
                }
            }
            else {
                if (!paga(t->get_costo_pernottamento())) {
                    eliminato = true;
                    libera_possedimenti(m_possedimenti);
                    t->get_proprietario()->riscuoti(m_budget);
                    paga(m_budget);
                    //devi pagare lo stesso
                    return false;
                }
                else {
                    t->get_proprietario()->riscuoti(t->get_costo_pernottamento());
                }
            }
        }
    }
    return true;
}
