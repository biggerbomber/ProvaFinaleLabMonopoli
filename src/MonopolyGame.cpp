//@Barbato alberto 2073961

//monopolygame.cpp
#include "MonopolyGame.h"
#include "Bot.h"
#include "Human.h"
#include "algorithm"
#include <memory>

MonopolyGame::MonopolyGame(MonopolyGame::PlayerType pt) {
  srand((unsigned)time(0));
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
    dadi_inizio[i] = { m_players[i]->get_tag(), 8};
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


}

void MonopolyGame::show(){}




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
    }

  }

  return;
}
 