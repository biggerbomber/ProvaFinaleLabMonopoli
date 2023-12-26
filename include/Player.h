//@Casucci Leonardo 2073980

#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include "MonopolyGame.h"
#include "Tile.h"
#include <vector>
#include <memory>

class MonopolyGame;

class Player{
    public:
        
        // funzioni in-line

        std::vector<std::shared_ptr<Tile>>& get_possedimenti(){return m_possedimenti;}
        
        Position& get_posizione(){return m_posizione;}
        
        int get_budget(){return m_budget;}

        int get_tag() { return m_tag; }

        //funzioni implementate sul file cpp
        
        bool paga(int);

        void riscuoti(int); 

        void aggiungi_possedimento(std::shared_ptr<Tile>);

        virtual bool gestisci_casella(std::shared_ptr<Tile>) =0;


    protected:
        
        int m_tag{ -1 };
        
        std::vector<std::shared_ptr<Tile>> m_possedimenti;
        
        Position m_posizione{ 0 };
        
        int m_budget{ 0 };
        
        bool m_eliminato{ false };

        MonopolyGame* mg = nullptr;
};

//H-F
void libera_possedimenti(std::vector<std::shared_ptr<Tile>>);
void migliora_terreno(MonopolyGame*, std::shared_ptr<Tile>, Player*);

#endif