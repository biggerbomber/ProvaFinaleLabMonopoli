//@Casucci Leonardo 2073980

#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {
public:
	Human(int, Position);
	EventType gestisci_casella(std::shared_ptr<Tile>);
};

static std::string stampa_build(Tile::BuildType);

#endif