//Leonardo Casucci

#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include "Tile.h"
#include <vector>

class Player{
    public:
        
        std::vector<Position>& get_possedimenti(){return m_possedimenti;}
        
        Position& get_posizione(){return m_posizione;}
        
        int get_budget(){return m_budget;}

        int get_tag() { return m_tag; }
        
        bool paga(int);// se ho abbastanz soldi paga (budget-int) e restituisci true altrimenti false 

        void riscuoti(int); // budget+int  NO-THROW-GUARANTEE, se int<0 termina senza fare nulla (non devi usare riscutore per pagare)

        void aggiungi_possedimento(Position);

        virtual bool gestisci_casella() =0;


    protected:
        
        int m_tag;
        
        std::vector<Position> m_possedimenti;
        
        Position m_posizione;
        
        int m_budget;
};

#endif