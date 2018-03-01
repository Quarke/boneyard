/* Implementation for the class Feet (Feet.cpp) */
#include <iostream>

#include "feet.h"

using namespace std;

// Constructor, with member initializer list to initialize the
//  component Author instance
Feet::Feet() {   // Must use member initializer list to construct object
   // Call setters to validate price and qtyInStock
   item = nullptr;

   usable = true;
}

string Feet::getItem() const {
   return item;
}

bool Feet::getUsable() {
   return usable;
}

// Validate price, which shall be positive
void Feet::setItem(string new_item) {
   item = new_item;
}

void Feet::setUsable(bool b) {
  usable = b;
}

// print in the format ""Feet-name" by author-name (gender) at email"
void Feet::print() const {
   cout << "'" << item << "' by " << endl;
}
