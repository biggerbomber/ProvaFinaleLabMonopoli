//@Casucci Leonardo 2073980

#ifndef BOT_H
#define BOT_H

#include "Player.h"

/*
Classe che deriva Player, ha un costruttore e sovrascrive gestisci_casella.
*/

class Bot: public Player {
public:
	Bot(int, Position);
	EventType gestisci_casella(std::shared_ptr<Tile>);
};

#endif