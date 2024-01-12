//@Casucci Leonardo 2073980

#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"
#include "Tile.h"
#include "EventType.h" 
#include <vector>
#include <memory>

/*
Classe astratta per la gestione dei giocatori :
Viene specializzata in Bot e Human.
All'interno di player vengono definite una serie di
funzioni utili alla modifica delle variabili membro:
-funzioni di get.
-funzioni di set per posizione, eliminato e possedimento (aggiungi_possedimento).
-funzioni di set per modificare budget (paga/riscuoti)
che sono separate perché rappresentano due operazioni diverse.

La funzione virtuale pura e' gestisci casella, viene chiamata sul giocatore e
gli fa prendere una decisione in base alla casella su cui si trova.
In questo modo gestisci casella può essere chiamato su un vettore di Player*
contenente Human e Bot e il compilatore chiamerà la funzione corretta tramite
Virtual Table.
*/

class Player {
public:

  // funzioni in-line
  const static int BUDGET_PARTENZA = 100;
  std::vector<std::shared_ptr<Tile>>& get_possedimenti() { return m_possedimenti; }

  Position& get_posizione() { return m_posizione; }

  int get_budget() { return m_budget; }

  bool get_eliminato() { return m_eliminato; }

  int get_tag() { return m_tag; }

  void set_posizione(Position p) { m_posizione = p; }

  void set_eliminato(bool b) { m_eliminato = b; }

  //funzioni implementate sul file cpp

  bool paga(int);

  void riscuoti(int);

  void aggiungi_possedimento(std::shared_ptr<Tile>);

  virtual EventType gestisci_casella(std::shared_ptr<Tile>) = 0;


protected:

  int m_tag{ -1 };

  std::vector<std::shared_ptr<Tile>> m_possedimenti;

  Position m_posizione{ 0 };

  int m_budget{ 0 };

  bool m_eliminato{ false };

};

/*
Funzioni helper definite su player e usate su MonopolyGame.
Gestiscono le azioni che deve fare il gioco per eseguire l'azione del player:
(Se il player vuole migliorare il terreno--> migliora_terreno...)
*/
void libera_possedimenti(std::vector<std::shared_ptr<Tile>>&);
void migliora_terreno(EventType, std::shared_ptr<Tile>, std::shared_ptr<Player>);
void gestisci_acquisto_terreno(std::shared_ptr<Tile>, std::shared_ptr<Player>);
void gestisci_pagamento_pernottamento(std::shared_ptr<Tile>, std::shared_ptr<Player>, std::shared_ptr<Player>);
void gestisci_eliminazione(std::shared_ptr<Tile>, std::shared_ptr<Player>, std::shared_ptr<Player>);

#endif