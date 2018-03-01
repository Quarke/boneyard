/* Implementation for the class Hand (Hand.cpp) */
#include <iostream>

#include "hand.h"

using namespace std;

// Constructor, with member initializer list to initialize the
//  component Author instance
Hand::Hand(string side) {   // Must use member initializer list to construct object
   // Call setters to validate price and qtyInStock
   side = side;
   item = nullptr;

   usable = true;
}

string Hand::getSide() const {
   return side;
}

string Hand::getItem() const {
   return item;
}

bool Hand::getUsable() {
   return usable;
}

// Validate price, which shall be positive
void Hand::setItem(string new_item) {
   item = new_item;
}

void Hand::setUsable(bool b) {
  usable = b;
}

// print in the format ""Hand-name" by author-name (gender) at email"
void Hand::print() const {
   cout << "'" << side << ", " << item << "' by " << endl;
}
