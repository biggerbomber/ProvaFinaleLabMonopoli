//@Casucci Leonardo 2073980

#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
public:
	Human(int, Position, MonopolyGame*);
	bool gestisci_casella(std::shared_ptr<Tile>);
};

#endif