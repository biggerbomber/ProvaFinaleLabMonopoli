//@barbato alberto 2073961
#include "MonopolyGame.h"
#include <cstring>
int main(int argc , char** argv){
  
  if (argc != 2) {
    std::cout << "Numero di paramentri da console errato , Attesi 1 Trovati : " << argc - 1 << std::endl;
    return -1;
  }
  MonopolyGame::PlayerType gameType;
  if (strcmp(argv[1],"human")==0) 
  {
    gameType = MonopolyGame::PlayerType::HUMAN;
  }
  else if(strcmp(argv[1], "computer") == 0)
  {
    gameType = MonopolyGame::PlayerType::BOT;
  }
  else {
    std::cout << "\"human\" or \"computer\" aspettato, Trovato : " << argv[1] << std::endl;
    return -1;
  }

   MonopolyGame m(gameType);
   m.run();

 
  return 0;
}