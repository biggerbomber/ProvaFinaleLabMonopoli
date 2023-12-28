//@Casucci Leonardo 2073980

#include "Player.h"
#include "Logger.h"

bool Player::paga(int somma) { //metodo che ti da informazioni sulla buona riuscita del pagamento oltre che effettuarlo se possibile
	if (somma > 0 && somma < m_budget) {
		m_budget -= somma;
		return true;
	}
	return false;
}

void Player::riscuoti(int somma) { // NO-THROW-GUARANTEE se si prova a riscuotere una somma negativa il metodo termina senza modificare il budget
	if (somma < 0 ) {
		return;
	}
	m_budget += somma;
}

void Player::aggiungi_possedimento(std::shared_ptr<Tile> p) {//non fa controlli
		m_possedimenti.push_back(p);
}

//H-F

void libera_possedimenti(std::vector<std::shared_ptr<Tile>>& v) {
	for (int i = 0; i < v.size(); i++) {
		v[i]->rimuovi_proprietario();
		v[i]->set_build_type(Tile::BuildType::VUOTA);
		v[i]->set_proprietario(nullptr); //non valido
	}
	v.resize(0);
}

void migliora_terreno(EventType e,std::shared_ptr<Tile> t, std::shared_ptr<Player>p ) {
	switch (e) {
	case EventType::COSTRUZIONE_CASA:
		p->paga(t->get_costo_miglioramento());
		t->set_build_type(Tile::BuildType::CASA);
		break;
	case EventType::COSTRUZIONE_ALBERGO:
		p->paga(t->get_costo_miglioramento());
		t->set_build_type(Tile::BuildType::ALBERGO);
		break;
	default:
		break;
	}
}

void gestisci_acquisto_terreno(std::shared_ptr<Tile> t, std::shared_ptr<Player> p) {
	p->paga(t->get_costo_terreno());
	p->aggiungi_possedimento(t);
	t->set_proprietario(p);
}

void gestisci_pagamento_pernottamento(std::shared_ptr<Tile> t, std::shared_ptr<Player> p, std::shared_ptr<Player> p_prop) {
	p->paga(t->get_costo_pernottamento());
	p_prop->riscuoti(t->get_costo_pernottamento());
}

void gestisci_eliminazione(std::shared_ptr<Tile> t, std::shared_ptr<Player> p_eliminato, std::shared_ptr<Player> p_prop){
	p_prop->riscuoti(p_eliminato->get_budget()); //il proprietario della tile riscuote tutto quello che puo' riscuotere
	p_eliminato->paga(p_eliminato->get_budget()); //setto il budget del giocatore a 0
	p_eliminato->set_eliminato(true);
	libera_possedimenti(p_eliminato->get_possedimenti());
}