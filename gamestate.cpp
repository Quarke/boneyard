/* Implementation for the class GameState (GameState.cpp) */
#include <iostream>
#include <fstream>

#include "gamestate.h"



GameState::GameState() {
   name = "";
   equipped = "";
   hp = 100;
   maxItems = 1;
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

    // Reader is deprecated, we are supposed to use a CharReaderBuilder and streams instead
    // Which is newer better practice, but it works so fuck it
    Json::Reader reader;
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


// End Setters


// Modifiers

void GameState::addItem(std::string item){
    if(items.size() < static_cast<unsigned long>(maxItems))
        items.insert(item);
}

void GameState::removeItem(std::string item){
    items.erase(item);
}

void GameState:: clearItems(){
    items.clear();
}
void GameState::print() {
   std::cout << name << ", " << equipped << std::endl;
}

