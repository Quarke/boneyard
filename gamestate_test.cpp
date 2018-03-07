#include <stdio.h>
#include <string>
#include <iostream>

#include "character.h"

int main(void) {
  Character *c = new Character("businessBeSnoozin");
  c->print();

  c->setName("Timothy");

  c->print();

  Bag b = c->getBag();

  b.addContent("things1");
  b.addContent("things2");
  b.addContent("things3");

  b.print();

  b.removeContent("things1");

  b.print();

  c->print();

  return 0;
}
