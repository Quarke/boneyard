/* Header for Character class (Character.h) */
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "bag.h"

class Character {
private:
  std::string name;
  std::string equipped;

  std::string boots;

  Bag bag;

public:
  Character(const std::string name);

  std::string getName();
  std::string getEquipped();
  std::string getBoots();

  void setName(const std::string n);
  void setEquipped(const std::string e);
  void setBoots(const std::string b);

  void print();

  Bag getBag();

};

#endif
