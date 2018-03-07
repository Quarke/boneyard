#include "node.h"
#include <string>
#include <iostream>

Node::Node(){}

Node::Node(std::string ttl, std::string enterDesc, std::string nme, std::string en, std::string es,
        std::string ee, std::string ew, std::string one, std::string onl, std::vector<std::string> search,
        std::vector<std::string> find, std::vector<std::string> searchT, std::vector<std::string> objs) {

    this->title = ttl;
    this->enterDescription = enterDesc;
    this->enemy = nme;
    this->exitNorth = en;
    this->exitSouth = es;
    this->exitEast = ee;
    this->exitWest = ew;
    this->onEnter = one;
    this->onLeave = onl;
    this->searchables = search;
    this->findables = find;
    this->searchText = searchT;
    this->objects = objs;
}

int Node::objectExists(std::string obj){
    auto it = find(objects.begin(), objects.end(), obj);
    if(it != objects.end())
        return 0;
    else
        return -1;
}

int Node::searchableExists(std::string search){
    auto it = find(searchables.begin(), searchables.end(), search);
    if(it != searchables.end())
        return 0;
    else
        return -1;
    // int loc = -1;
    // for(int i = 0; i < searchables.size(); i++){
    //     if(searchables[i].compare(search) == 0)
    //         loc = i;
    // }
    // return loc;
}

void Node::addObject(std::string obj){
    objects.push_back(obj);
}
/*
int addObject(std::string obj){
    objects.
}*/

void Node::print(){
  std::cout << title << ", " << enterDescription << ", " << enemy << std::endl;
}
