//@Casucci Leonardo 2073980

#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
public:
	Human(int, Position,std::shared_ptr<Player>*, Logger*);
	bool gestisci_casella(std::shared_ptr<Tile>);
};

#endif