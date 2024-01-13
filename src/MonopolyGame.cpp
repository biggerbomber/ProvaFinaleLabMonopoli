//@Barbato alberto 2073961

//monopolygame.cpp
#include "MonopolyGame.h"
#include "Bot.h"
#include "Human.h"
#include <algorithm>
#include <memory>


MonopolyGame::MonopolyGame(MonopolyGame::GameType pt) {
  srand((unsigned)time(0));
  m_game_type = pt;
  switch (pt)
  {
  case MonopolyGame::GameType::BOT:
    m_players[0] = std::make_shared<Bot>(0, m_board.get_partenza());
    break;
  case MonopolyGame::GameType::HUMAN:
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
    dadi_inizio[i] = { m_players[i]->get_tag(), roll_dice() };
    m_log.log(EventType::TIRO_DADI, dadi_inizio[i].p_tag, dadi_inizio[i].n_dice);
  }

  gestisci_turni(dadi_inizio, 0, N_PLAYER, &m_log);


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
  while (num_eliminati != N_PLAYER - 1)
  {
    turno %= N_PLAYER;
    EventType ris = run_turno(turno);
    if (ris == EventType::ELIMINAZIONE) {
      num_eliminati++;
    }
    turno++;
    numturni++;
    if (numturni >= MAX_TURNI) {
      break;
    }
  }

  if (numturni >= MAX_TURNI) {
    fine_partita_max_turni();
  }
  else
  {
    fine_partita_vittoria();
  }
  std::cout << "Numero turni : " << numturni << std::endl;
}

void MonopolyGame::show() {
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
    std::cout << "Giocatore " << i << ": " << m_players[i]->get_budget() << " fiorini" << std::endl;
  }

}

void MonopolyGame::log(EventType lt, int tag1, Position pos1, int tag2, int fiorini)
{
  m_log.log(lt, tag1, pos1, tag2, fiorini);
}

std::shared_ptr<Player> MonopolyGame::get_player_from_tag(int tag)
{
  for (std::shared_ptr<Player> player : m_players) {
    if (player->get_tag() == tag) {
      return player;
    }
  }
  return std::shared_ptr<Player>(nullptr);
}

int roll_dice()
{
  return (rand() % 6 + 1) + (rand() % 6 + 1);
}

void gestisci_turni(std::array<MonopolyGame::TurnoPlayer, MonopolyGame::N_PLAYER>& arr, int index_start, int index_end, Logger* l)
{
  //se il subarray e di dim=1 non devo fare nulla;
  if (index_start + 1 == index_end)
  {
    return;
  }
  //funzione per ordinare giocatori per tiro di dado
  auto compare = [](const MonopolyGame::TurnoPlayer& lhs,
    const MonopolyGame::TurnoPlayer& rhs) -> bool
    {
      return lhs.n_dice > rhs.n_dice;
    };

  std::sort(arr.begin() + index_start, arr.begin() + index_end, compare);
  int range_equal_start = index_start;
  //per ogni "range di tiro" uguali, ritira i dadi e chiama ricorivamnete questa funzione
  for (int i = index_start + 1; i <= index_end; i++)
  {

    if (i == index_end || (arr[i].n_dice != arr[range_equal_start].n_dice))
    {
      //evito di chiamare la ricorsione se mi acorgo che dim(range) =1;
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

void MonopolyGame::fine_partita_max_turni() {

  auto compare = [](const std::shared_ptr<Player>& lhs,
    const std::shared_ptr<Player>& rhs) {
      return lhs->get_budget() > rhs->get_budget();
    };
  std::sort(m_players.begin(), m_players.end(), compare);


  int max_fiorini = m_players[0]->get_budget();

  std::cout << "Max turni raggiunto, la vittoria e' di : ";
  std::cout << m_players[0]->get_tag();
  for (int i = 1; i < m_players.size(); i++) {
    if (m_players[i]->get_budget() == max_fiorini) {
      std::cout << " e " << m_players[i]->get_tag();
    }
    else {
      break;
    }
  }
  std::cout << " con " << max_fiorini << " fiorini" << std::endl;

  std::cout << "Classifica Fiorini:" << std::endl;

  std::array<int, N_PLAYER> posizioni;
  posizioni[0] = 1;
  for (int i = 1; i < N_PLAYER; i++) {
    if (m_players[i]->get_budget() == m_players[i - 1]->get_budget()) {
      posizioni[i] = posizioni[i - 1];
    }
    else {
      posizioni[i] = posizioni[i - 1] + 1;
    }
  }

  for (int i = 0; i < m_players.size(); i++) {
    std::cout << posizioni[i] << ") Giocatore : "
      << m_players[i]->get_tag()
      << " Con " << m_players[i]->get_budget()
      << " fiorini" << std::endl;
  }
}


void MonopolyGame::fine_partita_vittoria() {
  for (int i = 0; i < N_PLAYER; i++) {
    if (!m_players[i]->get_eliminato())
    {
      m_log.log(EventType::VITTORIA, m_players[i]->get_tag());
      break;
    }
  }
}

EventType MonopolyGame::run_turno(int turno)
{
  std::shared_ptr<Player>& p_attivo = m_players[m_num_turno[turno]];
  if (p_attivo->get_eliminato()) {
    return EventType::FINE_TURNO;
  }


  int roll = roll_dice();
  m_log.log(EventType::TIRO_DADI, p_attivo->get_tag(), roll);


  if (m_board.avanza_e_controlla(p_attivo->get_posizione(), roll))
  {
    p_attivo->riscuoti(FIORINI_PASSAGGIO_VIA);
    m_log.log(EventType::PASSAGGIO_VIA, p_attivo->get_tag());
  }
  m_log.log(EventType::ARRIVO, p_attivo->get_tag(), p_attivo->get_posizione());

  std::shared_ptr<Tile> t_attiva = m_board.get_tile(p_attivo->get_posizione());

  EventType ris = EventType::ARRIVO;

  while (ris != EventType::FINE_TURNO && ris != EventType::ELIMINAZIONE)
  {
    ris = gestisci_eventi(p_attivo, t_attiva);
  }
  m_log.log(ris, p_attivo->get_tag(), p_attivo->get_posizione());
  return ris;
}

EventType MonopolyGame::gestisci_eventi(std::shared_ptr<Player> p_attivo, std::shared_ptr<Tile> t_attiva)
{
  EventType ris = p_attivo->gestisci_casella(t_attiva);
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
    gestisci_pagamento_pernottamento(t_attiva, p_attivo,
      get_player_from_tag(t_attiva->get_proprietario()));
    m_log.log(ris, p_attivo->get_tag(),
      p_attivo->get_posizione(),
      t_attiva->get_proprietario(),
      t_attiva->get_costo_pernottamento());
    ris = EventType::FINE_TURNO;
    break;

  case SHOW_COMMAND:
    show();
    break;

  case ELIMINAZIONE:
    gestisci_eliminazione(p_attivo,
      get_player_from_tag(t_attiva->get_proprietario()));
    m_log.log(EventType::PAGAMENTO_PERNOTTAMENTO,
      p_attivo->get_tag(),
      p_attivo->get_posizione(),
      t_attiva->get_proprietario(),
      p_attivo->get_budget());
    break;

  default:
    break;
  }
  return ris;
}
