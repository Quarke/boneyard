/* Enemy Class */

#include "enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(string n, string power, string kill_method): ability(power),kill(kill_method) {   
   name = n;
   ability = power; 
   kill = kill_method; 
   
}

string Enemy::getName() {
   return name;
}

string Enemy::getAbility() {
   return ability;
}

Bag Enemy::getKillMethod() {
  return kill;
}

void Enemy::setName(string new_name) {
   name = new_name;
}

void Enemy::setAbility(string new_ability)
{
    ability = new_ability; 
    
}

void Enemy::setKillMethod(string new_killmethod)
{
    kill   = new_killmethod; 
    
}
