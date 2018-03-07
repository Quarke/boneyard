/* Enemy Class */

#include "enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(string n, int chealth, int mhealth, int pdamage, int sdamage) {
   name = n;
   health_CURRENT = chealth; 
   health_MAX = mhealth; 
   damage_self = sdamage; 
   damage_person = pdamage; 
}

string Enemy::getName() {
   return name;
}

int Enemy::getCurrentHealth() {
   return health_CURRENT;
}

int Enemy::getMaxHealth() {
  return health_MAX; 
}

int Enemy::getPersonDamage() {
  return damage_person; 
}

int Enemy::getSelfDamage() {
  return damage_self; 
}

void Enemy::setName(string new_name) {
   name = new_name;
}

void Enemy::setMaxHealth(int new_maxhealth) {
    health_MAX = new_maxhealth; 
}
void Enemy::setCurrentHealth(int new_currenthealth) {
    health_CURRENT = new_currenthealth; 
}
void Enemy::setPersonDamage(int new_persondamage) {
    damage_person = new_persondamage; 
}
void Enemy::setSelfDamage(int new_selfdamage) {
    damage_self = new_selfdamage; 
}

// print in the format ""Bag-name" by author-name (gender) at email"
void Enemy::print() const {
   cout << name << ", " << health_MAX << ", " << health_CURRENT << ", " << damage_person << ", " << damage_self << endl;
}
