//@Casucci Leonardo 2073980

#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot: public Player {
public:
	Bot(std::shared_ptr<Player>, Position);
	bool gestisci_casella(std::shared_ptr<Tile>);
};

#endif