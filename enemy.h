#ifndef ENEMY_H_H
#define ENEMY_H

#include <string>
#include "hand.h"
#include "feet.h"
#include "bag.h"

class Enemy{
private:
  std::string name;

  Ability power;
  Kill kill_method;

public:
  Enemy(const std::string name);

  std::string getName();
  std::string getAbility();
  std::string getKillMethod();

  void setName(const std::string name);
  void setAbility(const std::string power);
  void setKillMethod(const std::string kill_method);

  void print() const;

};

#endif