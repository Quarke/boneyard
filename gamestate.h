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

  // Reader is deprecated, we are supposed to use a CharReaderBuilder and streams instead
  // Which is newer better practice, but it works so fuck it
  Json::Reader reader;

public:
  GameState();

  // Getters
  std::string getName();
  std::string getEquipped();
  int getHp();
  int getMaxItems();
  std::set<std::string> getItems();
  std::string getItem(std::string item);
  std::unordered_map<std::string, Node> getNodeMap();
  std::string getNextNode(std::string, Node * n);
  std::unordered_map<std::string, long> getWeapons();
  long getWeapon(std::string);
  //Setters
  void setName(const std::string n);
  void setEquipped(const std::string e);
  void setHp(int new_hp);
  void setMaxItems(int max);

  void createNodeMap();
  void createEnemyMap();

  // Modifiers
  int addItem(std::string item);
  int removeItem(std::string item);

  bool hasItem(std::string item);
  void clearItems();

  void print();

};

#endif
