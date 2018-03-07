/* Enemy Class */

#include "enemy.h"
#include <iostream>

Enemy::Enemy(){}

Enemy::Enemy(std::string n, int chealth, int mhealth, int pdamage) {
   name = n;
   health_current = chealth; 
   health_max = mhealth; 
   damage_person = pdamage; 
}

std::string Enemy::getName() {
   return name;
}

int Enemy::getCurrentHealth() {
   return health_current;
}

int Enemy::getMaxHealth() {
  return health_max; 
}

int Enemy::getPersonDamage() {
  return damage_person; 
}

void Enemy::setName(std::string new_name) {
   name = new_name;
}

void Enemy::setMaxHealth(int new_maxhealth) {
    health_max = new_maxhealth; 
}
void Enemy::setCurrentHealth(int new_currenthealth) {
    health_current = new_currenthealth; 
}
void Enemy::setPersonDamage(int new_persondamage) {
    damage_person = new_persondamage; 
}

// print in the format ""Bag-name" by author-name (gender) at email"
void Enemy::print() const {
   std::cout << name << ", " << health_max << ", " << health_current << ", " << damage_person << std::endl;
}
