/* Implementation for the class GameState (GameState.cpp) */
#include <iostream>
#include <fstream>

#include "gamestate.h"

GameState::GameState() {
   name = "";
   equipped = "";
   hp = 100;
   maxItems = 1;

   weapons["letter opener"] = 1;
   weapons["flashlight"] = 1;
   weapons["whiskey"] = 1;
   weapons["pistol"] = 3;
   weapons["shotgun"] = 4;
   weapons["bolt action rifle"] = 5;
   weapons["shiv"] = 2;
   weapons["pillow"] = 6;
   weapons["instruments"] = 2;
   weapons["hammer"] = 2;
}

// Getters
std::string GameState::getName() {
   return name;
}

std::string GameState::getEquipped() {
   return equipped;
}

int GameState::getHp(){
    return hp;
}

int GameState::getMaxItems(){
    return maxItems;
}

std::set<std::string> GameState::getItems(){
    return items;
}

std::string GameState::getItem(std::string item){
    for(std::string s: items){
        if(s.compare(item) == 0)
            return s;
    }
    return "invalid";
}

std::unordered_map<std::string, Node> GameState::getNodeMap(){
  return nodeMap;
}

std::unordered_map<std::string, long> GameState::getWeapons(){
    return weapons;
}

long GameState::getWeapon(std::string w){
    auto it = weapons.find(w);
    if(it != weapons.end()){
        //valid weapon
        return it->second;
    }
    return 0;
}

std::string GameState::getNextNode(std::string direction, Node * n){
  if(direction.compare("north") == 0){
      return n->exitNorth;
  }
  else if(direction.compare("south") == 0){
      return n->exitSouth;
  }
  else if(direction.compare("east") == 0){
      return n->exitEast;
  }
  else if(direction.compare("west") == 0){
      return n->exitWest;
  }
  else{
      return "invalid";
  }
}
// End Getters

// Setters
void GameState::setName(std::string new_name) {
   name = new_name;
}

void GameState::setEquipped(std::string new_equipped) {
   equipped = new_equipped;
}

void GameState::setHp(int new_hp){
    hp = new_hp;
}

void GameState::setMaxItems(int new_max_items){
    maxItems = new_max_items;
}

void GameState::createNodeMap(){
  std::ifstream ifs("script.json");

  Json::Value obj;
  reader.parse(ifs, obj); // reader can also read strings

  // Create an empty unordered_map and
  Node n;
  GameState gameState;

  for(Json::Value::iterator i = obj.begin(); i !=obj.end(); ++i){
      Json::Value key = i.key();
      Json::Value value = (*i);

      n.enterDescription = value["enterDescription"].asString();
      n.title = value["title"].asString();
      n.enemy = value["enemy"].asString();
      n.exitNorth = value["exitNorth"].asString();
      n.exitSouth = value["exitSouth"].asString();
      n.exitEast = value["exitEast"].asString();
      n.exitWest = value["exitWest"].asString();
      n.onEnter = value["onEnter"].asString();
      n.onLeave = value["onLeave"].asString();
      n.extra1 = value["extra1"].asString();
      n.extra2 = value["extra2"].asString();
      n.extra3 = value["extra3"].asString();

      for(auto itr : value["object"]){
          n.objects.push_back(itr.asString());
      }

      std::string stringKey = key.asString();
      nodeMap[stringKey] = n;
  }

}

void GameState::createEnemyMap(){
   std::ifstream ifs("enemy.json");

  Json::Value obj;
  reader.parse(ifs, obj); // reader can also read strings

  // Create an empty unordered_map and
  Enemy e;
  for(Json::Value::iterator i = obj.begin(); i !=obj.end(); ++i){
      Json::Value key = i.key();
      Json::Value value = (*i);

      e.name = value["name"].asString();
      e.health_current = value["health_current`"].asInt();
      e.health_max = value["health_max"].asInt();
      e.damage_person = value["damage_person"].asInt();


      std::string stringKey = key.asString();
      enemies[stringKey] = e;
  }
}


// End Setters


// Modifiers

int GameState::addItem(std::string item){
    if(items.size() < static_cast<unsigned long>(maxItems)){
        items.insert(item);
        return 0;
    }
    return -1;
}

int GameState::removeItem(std::string item){
    auto it = items.find(item);
    items.erase(it);
    if(it != items.end())
        return 0;
    else
        return -1;
}

void GameState:: clearItems(){
    items.clear();
}
void GameState::print() {
   std::cout << name << ", " << equipped << std::endl;
}

