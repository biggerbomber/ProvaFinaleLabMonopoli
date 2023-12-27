//@Casucci Leonardo 2073980

#include "Human.h"

Human::Human(int tag, Position p,std::shared_ptr<Player>* self, Logger* l)
{
    m_tag = tag;
    m_posizione = p;
    m_budget = 100; //budget di partenza
    m_self = self;
    m_log = l;
}

bool Human::gestisci_casella(std::shared_ptr<Tile> t)
{   
    std::string risposta="";
    if (t->get_tile_type()!=Tile::TileType::ANGOLARE) {
        if (!t->has_proprietario()) {
            if (t->get_costo_terreno() < m_budget) {
                while (risposta!="N") {
                    std::cout << "Vuoi acquistare il terreno?(Y/N)\n";
                    std::cin >> risposta;
                    if (risposta == "Y") {
                        aggiungi_possedimento(t);
                        mg->log(Logger::ACQUISTO_TERRENO, m_tag, m_posizione);
                        // la modifica della posizione va fatta prima di chiamare gestisci casella senno non funziona
                        break;
                    }
                    else if (risposta != "N") {
                        if (risposta == "show" && risposta == "SHOW") {
                            mg->show();
                        }
                        else {
                            std::cout << "Risposta non valida.\n";
                        }
                    }
                }
            }
        }
        else {
            if (t->get_proprietario()->get_tag() == m_tag) {
                std::cout << "Il terreno e' già in tuo possesso, vuoi migliorarlo?(Y/N)\n";
                std::cout << "Costruzione attuale: " << t->get_build_type() << " , Costo miglioramento: " << t->get_costo_miglioramento()<<'\n';
                std::cin >> risposta;
                if (risposta=="Y") {
                    migliora_terreno(mg, t, this);
                }
                else if (risposta != "N") {
                    std::cout << "Risposta non valida.\n";
                }
            }
            else {
                if (!paga(t->get_costo_pernottamento())) {
                    m_eliminato = true;
                    libera_possedimenti(m_possedimenti);
                    t->get_proprietario()->riscuoti(m_budget);
                    paga(m_budget);
                    //devi pagare lo stesso
                    mg->log(Logger::ELIMINAZIONE, m_tag);
                    return false;
                }
                else {
                    t->get_proprietario()->riscuoti(t->get_costo_pernottamento());
                    mg->log(Logger::PAGAMENTO_PERNOTTAMENTO, m_tag, m_posizione,t->get_proprietario()->get_tag(),t->get_costo_pernottamento());
                }
            }
        }
    }
    return true;
}
