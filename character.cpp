/* Implementation for the class Character (Character.cpp) */
#include <iostream>

#include "character.h"
#include "bag.h"

using namespace std;

Character::Character(string n): bag("basic bag") {
   name = n;
   equipped = "Nothing";

   boots = "basic boots";
}

string Character::getName() {
   return name;
}

string Character::getEquipped() {
   return equipped;
}

string Character::getBoots() {
   return boots;
}

// Validate price, which shall be positive
void Character::setName(string new_name) {
   name = new_name;
}

void Character::setEquipped(string new_equipped) {
   equipped = new_equipped;
}

// Validate price, which shall be positive
void Character::setBoots(string new_boots) {
   name = new_boots;
}

void Character::print() {
   cout << name << ", " << equipped << endl;
}

Bag Character::getBag() {
  return bag;
}
