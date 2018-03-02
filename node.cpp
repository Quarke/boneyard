#include "node.h"


Node::Node(){}
Node::~Node(){}

Node::Node(std::string ttl, std::string enterDesc, std::string nme, std::string en, std::string es,
        std::string ee, std::string ew, std::string one, std::string onl, std::string e1,
        std::string e2, std::string e3, std::vector<std::string> objs){

    this->title = ttl;
    this->enterDescription = enterDesc;;
    this->enemy = nme;
    this->exitNorth = en;
    this->exitSouth = es;
    this->exitEast = ee;
    this->exitWest = ew;
    this->onEnter = one;
    this->onLeave = onl;
    this->extra1 = e1;
    this->extra2 = e2;
    this->extra3 = e3;
    this->objects = objs;
}