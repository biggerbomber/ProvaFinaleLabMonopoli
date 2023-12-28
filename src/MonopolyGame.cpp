//@Barbato alberto 2073961

//monopolygame.cpp
#include "MonopolyGame.h"
#include "Bot.h"
#include "Human.h"
#include "algorithm"
#include <memory>

MonopolyGame::MonopolyGame(MonopolyGame::PlayerType pt) {
  srand((unsigned)time(0));
  m_game_type = pt;
  switch (pt)
  {
  case MonopolyGame::PlayerType::BOT:
    m_players[0] = std::make_shared<Bot>(0, m_board.get_partenza());
    break;
  case MonopolyGame::PlayerType::HUMAN:
    m_players[0] = std::make_shared<Human>(0, m_board.get_partenza());
    break;
  default:
    throw std::invalid_argument("What?");
    break;
  }

  for (int i = 1; i < N_PLAYER; i++)
  {
    m_players[i] = std::make_shared<Bot>(i, m_board.get_partenza());
  }

  std::array<MonopolyGame::TurnoPlayer, N_PLAYER> dadi_inizio;
  for (int i = 0; i < N_PLAYER; i++)
  {
    dadi_inizio[i] = { m_players[i]->get_tag(), roll_dice()};
    m_log.log(EventType::TIRO_DADI, dadi_inizio[i].p_tag, dadi_inizio[i].n_dice);
  }
  
  gestisci_turni(dadi_inizio, 0, 4, &m_log);


  std::cout << "Turni di Gioco:" << std::endl;
  for (int i = 0; i < N_PLAYER; i++)
  {
    m_num_turno[i] = dadi_inizio[i].p_tag;
    std::cout << m_num_turno[i] << " ";
  }
  std::cout << std::endl;
}

void MonopolyGame::run()
{
  int num_eliminati = 0;
  int turno = 0;
  int numturni = 0;
  while (num_eliminati + 1 != N_PLAYER)
  {
    turno %= 4;
    std::vector<std::shared_ptr<Player>>vet(4);
    for (int i = 0; i < N_PLAYER; i++) {
      vet[i] = m_players[i];
    }
    m_board.print(std::cout, vet);
    std::shared_ptr<Player>& p_attivo = m_players[m_num_turno[turno]];
    if (p_attivo->get_eliminato()) {
      turno++;
      continue;
    }
    int roll = roll_dice();
    m_log.log(EventType::TIRO_DADI, p_attivo->get_tag(),roll);

    if (m_board.avanza_e_controlla(p_attivo->get_posizione(), roll))
    {
      m_log.log(EventType::PASSAGGIO_VIA, p_attivo->get_tag());
      p_attivo->riscuoti(FIORINI_PASSAGGIO_VIA);
    }

    m_log.log(EventType::ARRIVO, p_attivo->get_tag(), p_attivo->get_posizione());
    std::shared_ptr<Tile> t_attiva = m_board.get_tile(p_attivo->get_posizione());

    EventType ris = EventType::ARRIVO;

    while (ris != EventType::FINE_TURNO && ris!=EventType::ELIMINAZIONE)
    {
      ris = p_attivo->gestisci_casella(t_attiva);
      switch (ris)
      {
      case ACQUISTO_TERRENO:
        gestisci_acquisto_terreno(t_attiva, p_attivo);
        m_log.log(ris, p_attivo->get_tag(), p_attivo->get_posizione());
        ris = EventType::FINE_TURNO;
        break;

      case COSTRUZIONE_CASA:
        migliora_terreno(ris, t_attiva, p_attivo);
        m_log.log(ris, p_attivo->get_tag(), p_attivo->get_posizione());
        ris = EventType::FINE_TURNO;
        break;

      case COSTRUZIONE_ALBERGO:
        migliora_terreno(ris, t_attiva, p_attivo);
        m_log.log(ris, p_attivo->get_tag(), p_attivo->get_posizione());
        ris = EventType::FINE_TURNO;
        break;

      case PAGAMENTO_PERNOTTAMENTO:
        gestisci_pagamento_pernottamento(t_attiva, p_attivo);
        m_log.log(ris, p_attivo->get_tag(),
          p_attivo->get_posizione(),
          t_attiva->get_proprietario()->get_tag(),
          t_attiva->get_costo_pernottamento());
        ris = EventType::FINE_TURNO;
        break;

      case SHOW_COMMAND:
        show();
        break;

      case ELIMINAZIONE:
        gestisci_eliminazione(t_attiva, p_attivo);
        num_eliminati++;
        break;

      default:
        break;
      }
    }
    m_log.log(ris, p_attivo->get_tag(), p_attivo->get_posizione());

    //std::cin.get();
    turno++;
    numturni++;
    if (numturni >= MAX_TURNI) {
      break;
    }
  }
  if (numturni >= MAX_TURNI) {
    std::vector<int> pos_max_fiorini;
    int max_fiorini = -1;
    for (int i = 0; i < N_PLAYER; i++) {
      if (!m_players[i]->get_eliminato()){
        if (m_players[i]->get_budget() > max_fiorini) {
          pos_max_fiorini.resize(0);
          pos_max_fiorini.push_back(i);
          max_fiorini = m_players[i]->get_budget();
        }
        else if (m_players[i]->get_budget() == max_fiorini) {
          pos_max_fiorini.push_back(i);
        }
      }
    }

    std::cout << "Max turni raggiunto, la vittoria e' di : ";
    for (int i = 0; i < pos_max_fiorini.size(); i++) {
      std::cout << i;
      if (i != pos_max_fiorini.size() - 1) {
        std::cout << " e ";
      }
    }
    std::cout << " con " << max_fiorini << " fiorini" << std::endl;
  }
  else
  {
    for (int i = 0; i < N_PLAYER; i++) {
      if (!m_players[i]->get_eliminato())
      {
        m_log.log(EventType::VITTORIA, m_players[i]->get_tag());
        break;
      }
    }
  }
  std::cout << "Numero turni : " << numturni << std::endl;
}

void MonopolyGame::show(){
  std::vector<std::shared_ptr<Player>> temp;
  for (int i = 0; i < N_PLAYER; i++) {
    if (!m_players[i]->get_eliminato())
    {
      temp.push_back(m_players[i]);
    }
  }
  m_board.print(std::cout, temp);

  stampa_possedimenti();
  stampa_fiorini();
}

void MonopolyGame::stampa_possedimenti() {
  std::cout << "Possedimenti per Giocatore: " << std::endl;
  for (int i = 0; i < N_PLAYER; i++)
  {
    std::cout << "Giocatore " << i << ":";
    std::vector<std::shared_ptr<Tile>> poss = m_players[i]->get_possedimenti();
    for (int i = 0; i < poss.size(); i++)
    {
      std::cout << " " << poss[i]->get_position();
    }
    std::cout << std::endl;
  }
}

void MonopolyGame::stampa_fiorini()
{
  std::cout << "Fiorini per Giocatore: " << std::endl;
  for (int i = 0; i < N_PLAYER; i++)
  {
    std::cout << "Giocatore " << i << ": " << m_players[i]->get_budget() << " fiorini"<<std::endl;
  }

}

void MonopolyGame::log(EventType lt, int tag1, Position pos1, int tag2, int fiorini)
{
  m_log.log(lt, tag1, pos1, tag2, fiorini);
}

std::shared_ptr<Player> MonopolyGame::get_player_from_tag(int)
{
  return std::shared_ptr<Player>(new Bot(0,0));
}

int roll_dice()
{
  return (rand()%6+1)+(rand()%6+1);
}

void gestisci_turni(std::array<MonopolyGame::TurnoPlayer, MonopolyGame::N_PLAYER>& arr, int index_start, int index_end,Logger* l)
{
  if (index_start + 1 == index_end)
  {
    return;
  }
  auto compare = [](const MonopolyGame::TurnoPlayer& lhs,
                  const MonopolyGame::TurnoPlayer& rhs) -> bool
    {
      return lhs.n_dice > rhs.n_dice;
    };

  std::sort(arr.begin() + index_start, arr.begin() + index_end, compare);
  int range_equal_start = index_start;

  for (int i = index_start+1; i <= index_end; i++)
  {

    if (i==index_end || (arr[i].n_dice != arr[range_equal_start].n_dice))
    {
      if (range_equal_start + 1 == i)
      {
        range_equal_start = i;
        continue;
      }
      for (int j = range_equal_start; j < i; j++)
      {
        arr[j].n_dice = roll_dice();
        l->log(EventType::TIRO_DADI, arr[j].p_tag, arr[j].n_dice);
      }

      gestisci_turni(arr, range_equal_start, i, l);
      range_equal_start = i;
    }

  }

  return;
}
 