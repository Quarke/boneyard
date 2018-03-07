#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy{
public:
  Enemy();
  Enemy(const std::string name, int pdamage, int chealth, int mhealth);

  std::string name;
  int health_current, health_max, damage_person;

  std::string getName();
  int getPersonDamage();
  int getSelfDamage();
  int getMaxHealth();
  int getCurrentHealth();

  void setName(const std::string name);
  void setCurrentHealth(int c_health);
  void setMaxHealth(int m_health);
  void setPersonDamage(int p_damage);

  void print() const;
};

#endif
