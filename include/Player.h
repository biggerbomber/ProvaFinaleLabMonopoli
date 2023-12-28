//@Casucci Leonardo 2073980

#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include "Tile.h"
#include "EventType.h" 
#include <vector>
#include <memory>


class Player{
    public:
        
        // funzioni in-line
        const static int BUDGET_PARTENZA = 100;
        std::vector<std::shared_ptr<Tile>>& get_possedimenti(){return m_possedimenti;}
        
        Position& get_posizione(){return m_posizione;}
        
        int get_budget(){return m_budget;}

        bool get_eliminato() { return m_eliminato; }

        int get_tag() { return m_tag; }

        void set_posizione(Position p) { m_posizione = p; }

        void set_eliminato(bool b) { m_eliminato = b; }

        //funzioni implementate sul file cpp
        
        bool paga(int);

        void riscuoti(int); 

        void aggiungi_possedimento(std::shared_ptr<Tile>);

        virtual EventType gestisci_casella(std::shared_ptr<Tile>) =0;


    protected:
        
        int m_tag{ -1 };
        
        std::vector<std::shared_ptr<Tile>> m_possedimenti;

        Position m_posizione{ 0 };
        
        int m_budget{ 0 };
        
        bool m_eliminato{ false };

};

//H-F
void libera_possedimenti(std::vector<std::shared_ptr<Tile>>&);
void migliora_terreno(EventType, std::shared_ptr<Tile>, std::shared_ptr<Player>);
void gestisci_acquisto_terreno(std::shared_ptr<Tile>, std::shared_ptr<Player>);
void gestisci_pagamento_pernottamento(std::shared_ptr<Tile>, std::shared_ptr<Player>, std::shared_ptr<Player>);
void gestisci_eliminazione(std::shared_ptr<Tile>, std::shared_ptr<Player>, std::shared_ptr<Player>);

#endif