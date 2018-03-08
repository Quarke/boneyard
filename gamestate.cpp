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

void GameState::createNodeMap(){
  std::ifstream ifs("script.json", std::ifstream::binary);

  Json::CharReaderBuilder builder;

  Json::CharReader * reader = builder.newCharReader();

  Json::Value root;
  std::string errors;

  bool parsingSuccessful = Json::parseFromStream(builder, ifs, &root, &errors);
  delete reader;

  if ( !parsingSuccessful )
  {
    std::cout << errors << std::endl;
  }

  for( Json::Value::const_iterator outer = root.begin() ; outer != root.end() ; outer++ )
  {
      Node n;

      n.title = outer->get("title", "").asString();
      n.enemy = outer->get("enemy", "").asString();
      n.exitNorth = outer->get("exitNorth", "").asString();
      n.exitSouth = outer->get("exitSouth", "").asString();
      n.exitEast = outer->get("exitEast", "").asString();
      n.exitWest = outer->get("exitWest", "").asString();
      n.onEnter = outer->get("onEnter", "").asString();
      n.onLeave = outer->get("onLeave", "").asString();
      n.desc = outer->get("desc", "").asString();

      for(auto itr : outer->get("object", "")){
          n.objects.push_back(itr.asString());
      }
      for(auto itr : outer->get("searchables", "")){
          n.searchables.push_back(itr.asString());
      }
      for(auto itr : outer->get("findables", "")){
          n.findables.push_back(itr.asString());
      }
      for(auto itr : outer->get("searchText", "")) {
          n.searchText.push_back(itr.asString());
      }

      std::string stringKey = outer.key().asString();
      //std::cout << stringKey.c_str() << std::endl;
      std::pair<std::string, Node> p (stringKey, n);
      nodeMap.insert(p);
  }
}

void GameState::createEnemyMap() {
  std::ifstream ifs("enemy.json", std::ifstream::binary);

  Json::CharReaderBuilder builder;

  Json::CharReader * reader = builder.newCharReader();

  Json::Value root;
  std::string errors;

  bool parsingSuccessful = Json::parseFromStream(builder, ifs, &root, &errors);
  delete reader;

  if ( !parsingSuccessful )
  {
    std::cout << errors << std::endl;
  }

  for( Json::Value::const_iterator outer = root.begin() ; outer != root.end() ; outer++ )
  {
      Enemy e;

      e.name = outer->get("name", "").asString();

      e.health_current = outer->get("health_current", "").asInt();
      e.health_max = outer->get("health_max", "").asInt();
      e.damage_person = outer->get("damage_person", "").asInt();

      std::string stringKey = outer.key().asString();

      enemies[stringKey] = e;
  }
}

Node * GameState::getNextNode(std::string input, Node * n) {
  //input should be one of: north, south, east, west
  std::string rc;
  if( input.compare("north") == 0 ) {
    rc = n->exitNorth;
  }
  else if( input.compare("south") == 0 ) {
    rc = n->exitSouth;
  }
  else if( input.compare("east") == 0 ) {
    rc = n->exitEast;
  }
  else if( input.compare("west") == 0 ) {
    rc = n->exitWest;
  }

  if(rc.empty()) {
    return nullptr;
  }

  auto it = nodeMap.find(rc);
  if(it != nodeMap.end()){
    return &(it->second);
  }
  else {
    return nullptr;
  }
}


bool GameState::checkNextNode(std::string input, Node * n) {
  //input should be one of: north, south, east, west
  std::string rc;
  if( input.compare("north") == 0 ) {
    rc = n->exitNorth;
  }
  else if( input.compare("south") == 0 ) {
    rc = n->exitSouth;
  }
  else if( input.compare("east") == 0 ) {
    rc = n->exitEast;
  }
  else if( input.compare("west") == 0 ) {
    rc = n->exitWest;
  }

  if(rc.empty()) {
    return false;
  }
  return true;
}

bool GameState::removeItem(std::string item){
    size_t rc = items.erase(item);
    if(rc > 0){
      return true;
    }
    return false;
}

std::unordered_map<std::string, Node> GameState::getNodeMap(){
  return nodeMap;
}

std::set<std::string> GameState::getItemSet(){
  return items;
}

Node * GameState::getNode(std::string input) {
    auto it = nodeMap.find(input);
    if(it != nodeMap.end()) {
      return &(it->second);
    }
    return nullptr;
}

void GameState::addItem(std::string item){
    if(items.size() < static_cast<unsigned long>(maxItems))
        items.insert(item);
}

void GameState::setEquipped(std::string new_equipped) {
   equipped = new_equipped;
}

std::string GameState::getItem(std::string item){
    for(std::string s: items){
        if(s.compare(item) == 0)
            return s;
    }
    return "invalid";
}


void GameState::print() {
   for(auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
     std::cout << it->first << it->second.desc << std::endl;
   }
}
