//@Casucci Leonardo 2073980

#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
public:
	Human(int);
	bool gestisci_casella(Tile);
};

#endif