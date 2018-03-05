#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy{
private:
  std::string name;

  int health_CURRENT;
  int damage_person;
  int damage_self;
  int health_MAX;

public:
  Enemy(const std::string name, int pdamage, int sdamage, int chealth, int mhealth);

  std::string getName();
  int getDamage_Self();
  int getDamage_Person();
  int getMaxHealth();
  int getCurrentHealth();

  void setName(const std::string name);
  void setCurrentHealth(int c_health);
  void setMaxHealth(int m_health);
  void setSelfDamage(int s_damage);
  void setPersonDamage(int p_damage);

  void print() const;
};

#endif
