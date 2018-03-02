#include <stdio.h>
#include <string>
#include <iostream>

#include "enemy.h"

int main(void) {
  Enemy *e = new Enemy("orc", "fire", "sword");
  e->print();

  return 0;
}
