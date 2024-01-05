//@Casucci Leonardo 2073980

#include "Human.h"

Human::Human(int tag, Position p)
{
    m_tag = tag;
    m_posizione = p;
    m_budget = BUDGET_PARTENZA; //budget di partenza
}

EventType Human::gestisci_casella(std::shared_ptr<Tile> t)
{   
    std::string risposta="";
    if (t->get_tile_type()!=Tile::TileType::ANGOLARE) {
        if (!t->has_proprietario()) {
            if (t->get_costo_terreno() < m_budget) {
                while (risposta!="N" || risposta!="n") {
                    std::cout << "Vuoi acquistare il terreno?(Y/N)\n";
                    std::cout << "Terreno: "<<t->get_tile_type()<<", Costo:"<<t->get_costo_terreno()<< "\n";
                    std::cin >> risposta;
                    if (risposta == "Y" || risposta == "y") {
                        return EventType::ACQUISTO_TERRENO;
                    }
                    else if (risposta == "show" || risposta == "SHOW") {
                            return EventType::SHOW_COMMAND;
                    }
                    else if (risposta != "N" || risposta != "n") {
                        std::cout << "Risposta non valida.\n";
                    }
                }
            }
        }
        else {
            if (t->get_proprietario() == m_tag) {
                std::cout << "Il terreno e' gia' in tuo possesso, vuoi migliorarlo?(Y/N)\n";
                std::cout << "Costruzione attuale: " << stampa_terreno(t->get_build_type()) << " , Costo miglioramento: " << t->get_costo_miglioramento() << '\n';
                while (risposta != "N" || risposta != "n") {
                    std::cin >> risposta;
                    if (risposta == "Y" || risposta == "y") {
                        if (t->get_costo_miglioramento() < m_budget) {
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
                        return EventType::FINE_TURNO;
                    }
                    else if (risposta == "show" || risposta == "SHOW") {
                        return EventType::SHOW_COMMAND;
                    }
                    else if(risposta!="N" || risposta!="n") {
                        std::cout << "Risposta non valida.\n";
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
    return EventType::FINE_TURNO; // e' usato quando non devi fare nulla di particolare
}

static std::string stampa_terreno(Tile::BuildType b) {
    switch (b) {
        case Tile::BuildType::VUOTA:
            return "VUOTA";
        case Tile::BuildType::CASA:
            return "VUOTA";
        case Tile::BuildType::ALBERGO:
            return "ALBERGO";
        default:
            return "Terreno non valido";
    }

    
}