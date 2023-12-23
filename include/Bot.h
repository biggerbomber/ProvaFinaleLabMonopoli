//@Casucci Leonardo 2073980

#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot: public Player {
public:
	Bot(int);
	bool gestisci_casella(Tile);
};

#endif