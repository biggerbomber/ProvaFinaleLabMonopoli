//@Casucci Leonardo 2073980

#include "Human.h"

Human::Human(int tag, Position p)
{
    m_tag = tag;
    m_posizione = p;
    m_budget = 100; //budget di partenza
}

EventType Human::gestisci_casella(std::shared_ptr<Tile> t)
{   
    std::string risposta="";
    if (t->get_tile_type()!=Tile::TileType::ANGOLARE) {
        if (!t->has_proprietario()) {
            if (t->get_costo_terreno() < m_budget) {
                while (risposta!="N") {
                    std::cout << "Vuoi acquistare il terreno?(Y/N)\n";
                    std::cin >> risposta;
                    if (risposta == "Y") {
                        return EventType::ACQUISTO_TERRENO;
                    }
                    else if (risposta == "show" && risposta == "SHOW") {
                            return EventType::SHOW_COMMAND;
                    }
                    else if (risposta != "N") {
                        std::cout << "Risposta non valida.\n";
                    }
                }
            }
        }
        else {
            if (t->get_proprietario()->get_tag() == m_tag) {
                std::cout << "Il terreno e' già in tuo possesso, vuoi migliorarlo?(Y/N)\n";
                std::cout << "Costruzione attuale: " << t->get_build_type() << " , Costo miglioramento: " << t->get_costo_miglioramento()<<'\n';
                std::cin >> risposta;
                while (risposta != "N") {
                    if (risposta == "Y") {
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
                    else if (risposta == "show" && risposta == "SHOW") {
                        return EventType::SHOW_COMMAND;
                    }
                    else if(risposta!="N") {
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
