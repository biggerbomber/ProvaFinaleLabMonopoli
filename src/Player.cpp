//@Casucci Leonardo 2073980

#include "../include/Player.h"

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

void Player::aggiungi_possedimento(std::shared_ptr<Tile> p) {
	if (paga(p->get_costo_terreno())) {
		p->set_proprietario(m_tag);
		m_possedimenti.push_back(p);
	}
}

void libera_possedimenti(std::vector<std::shared_ptr<Tile>> v) {
	for (int i = 0; i < v.size(); i++) {
		v[i]->rimuovi_proprietario();
		v[i]->set_build_type(Tile::BuildType::VUOTA);
		v[i]->set_proprietario(-1); //non valido
	}
	v.resize(0);
}