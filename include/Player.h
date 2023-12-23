//@Casucci Leonardo 2073980

#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include "Tile.h"
#include <vector>

void libera_possedimenti(std::vector<Tile>); //H-F

class Player{
    public:
        
        // funzioni in-line

        std::vector<Tile>& get_possedimenti(){return m_possedimenti;}
        
        Position& get_posizione(){return m_posizione;}
        
        int get_budget(){return m_budget;}

        int get_tag() { return m_tag; }

        //funzioni implementate sul file cpp
        
        bool paga(int);

        void riscuoti(int); 

        void aggiungi_possedimento(Tile);

        virtual bool gestisci_casella(Tile) =0;


    protected:
        
        int m_tag;
        
        std::vector<Tile> m_possedimenti;
        
        Position m_posizione;
        
        int m_budget;
        
        bool eliminato = false;
};

#endif