#include <stdio.h>
#include <string>
#include <iostream>

#include "gamestate.h"

int main(void) {
  GameState gameState;
  gameState.createNodeMap();
  gameState.createEnemyMap();

  std::string ed = "";
  for (auto const& i : gameState.getNodeMap()) {
    std::cout << i.first << " - " << i.second.desc << std::endl;
    break;
  }


  std::string s("boatYard");
  Node it = gameState.getNodeMap().at(s);

  Node k = gameState.getNodeMap().at("asd");
  std::cout << k << std::endl;

  std::cout << it.desc << std::endl;


  //gameState.print();

  return 0;
}
