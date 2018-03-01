/* Header for Character class (Character.h) */
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "hand.h"
#include "feet.h"
#include "bag.h"

class Character {
private:
  std::string name;

  Hand left_hand;
  Hand right_hand;

  Feet feet;

  Bag bag;

  std::string equipped;

public:
  Character(const std::string name);

  std::string getName();
  std::string getEquipped();

  Hand getLeftHand();
  Hand getRightHand();
  Feet getFeet();
  Bag getBag();

  void setName(const std::string name);

  void print() const;

};

#endif
