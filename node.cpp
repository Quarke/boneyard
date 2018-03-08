#include "node.h"
#include <string>
#include <iostream>

Node::Node(){}

Node::Node(std::string ttl, std::string enterDesc, std::string nme, std::string en, std::string es,
        std::string ee, std::string ew, std::string one, std::string onl, std::vector<std::string> search,
        std::vector<std::string> find, std::vector<std::string> searchT, std::vector<std::string> objs) {

    title = ttl;
    enterDescription = enterDesc;
    enemy = nme;
    exitNorth = en;
    exitSouth = es;
    exitEast = ee;
    exitWest = ew;
    onEnter = one;
    onLeave = onl;
    searchables = search;
    findables = find;
    searchText = searchT;
    objects = objs;
}

bool Node::objectExists(std::string obj){
    auto it = find(objects.begin(), objects.end(), obj);
    if(it != objects.end())
        return true;
    else
        return false;
}

int Node::getSearchableIndex(std::string search){
    int loc = -1;
    for(int i = 0; i < searchables.size(); i++){
        if(searchables[i].compare(search) == 0)
            loc = i;
    }
    return loc;
}

void Node::addObject(std::string obj){
    objects.push_back(obj);
}

void Node::print(){
  std::cout << title << ", " << enterDescription << ", " << enemy << std::endl;
}
