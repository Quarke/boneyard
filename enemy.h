#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy{
private:
  std::string name;

  int health_CURRENT;
<<<<<<< HEAD
  int damage_person; 
  int damage_self; 
  int health_MAX;   
=======
  int damage_person;
  int damage_self;
  int health_MAX;
>>>>>>> f9e8367d1207e1c310975fba233f9b8e1357a8f5

public:
  Enemy(const std::string name, int pdamage, int sdamage, int chealth, int mhealth);

  std::string getName();
<<<<<<< HEAD
  int getSelfDamage();
  int getPersonDamage();
=======
  int getDamage_Self();
  int getDamage_Person();
>>>>>>> f9e8367d1207e1c310975fba233f9b8e1357a8f5
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
