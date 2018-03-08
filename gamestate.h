/* Header for GAMESTATE class (GAMESTATE.h) */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <json/json.h>

#include <string>
#include <set>
#include <unordered_map>

#include "node.h"
#include "enemy.h"

class GameState {
private:
  std::string name;
  std::string equipped;
  int hp;
  int maxItems;
  std::set<std::string> items;

  std::unordered_map<std::string, Node> nodeMap;
  std::unordered_map<std::string, Enemy> enemies;
  std::unordered_map<std::string, long> weapons;

public:
  GameState();

  void createNodeMap();
  void createEnemyMap();
  Node * getNextNode(std::string input, Node * n);
  bool checkNextNode(std::string input, Node * n);

  std::set<std::string> getItemSet();
  void addItem(std::string item);
  void setEquipped(std::string new_equipped);
  std::string getItem(std::string item);
  bool removeItem(std::string item);
  std::unordered_map<std::string, Node> getNodeMap();
  Node * getNode(std::string input);

  void print();

};

#endif
