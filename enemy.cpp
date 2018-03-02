/* Enemy Class */

#include "enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(string n, string p, string k) {
   name = n;
   power = p;
   kill_method = k;
}

string Enemy::getName() {
   return name;
}

string Enemy::getAbility() {
   return power;
}

string Enemy::getKillMethod() {
  return kill_method;
}

void Enemy::setName(string new_name) {
   name = new_name;
}

void Enemy::setAbility(string new_ability) {
    power = new_ability;
}

void Enemy::setKillMethod(string new_killmethod) {
    kill_method = new_killmethod;
}

// print in the format ""Bag-name" by author-name (gender) at email"
void Enemy::print() const {
   cout << name << ", " << power << ", " << kill_method << endl;
}
