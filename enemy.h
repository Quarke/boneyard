#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy{
private:
  std::string name;

  std::string power;
  std::string kill_method;

public:
  Enemy(const std::string name, std::string p, std::string k);

  std::string getName();
  std::string getAbility();
  std::string getKillMethod();

  void setName(const std::string name);
  void setAbility(const std::string power);
  void setKillMethod(const std::string kill_method);

  void print() const;

};

#endif
