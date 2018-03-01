/* Implementation for the class Character (Character.cpp) */
#include <iostream>

#include "character.h"

using namespace std;

Character::Character(string n): left_hand("left"), right_hand("right"), feet(), bag("basic backpack") {   // Must use member initializer list to construct object
   // Call setters to validate price and qtyInStock
   name = n;
   equipped = "Nothing";
}

string Character::getName() {
   return name;
}

string Character::getEquipped() {
   return equipped;
}

Bag Character::getBag() {
  return bag;
}

Hand Character::getLeftHand() {
  return left_hand;
}

Hand Character::getRightHand() {
  return right_hand;
}

Feet Character::getFeet() {
  return feet;
}

// Validate price, which shall be positive
void Character::setName(string new_name) {
   name = new_name;
}


// print in the format ""Character-name" by author-name (gender) at email"
void Character::print() const {
   cout << "'" << name << ", " << equipped << "' by " << endl;
}
