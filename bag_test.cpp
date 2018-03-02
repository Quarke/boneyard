#include <stdio.h>
#include <string>
#include <iostream>

#include "bag.h"

int main(void) {
  Bag * b = new Bag("businessBeSnoozin");
  b->print();

  b->setName("Timothy");

  b->addContent("thing1");
  b->addContent("thing2");

  b->print();

  b->removeContent("thing2");

  b->print();

  b->removeContent("12312");

  b->print();

  return 0;
}
