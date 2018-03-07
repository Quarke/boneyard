#include <stdio.h>
#include <string>
#include <iostream>

#include "enemy.h"

int main(void) {
  Enemy *e = new Enemy("Tom", 100 , 100, 30, 50 );
  e->print();

  return 0;
}
