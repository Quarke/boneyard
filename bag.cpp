/* Implementation for the class Bag (Bag.cpp) */
#include <iostream>
#include "bag.h"

using namespace std;

// Constructor, with member initializer list to initialize the
Bag::Bag(std::string n) : capacity(10), contents() {   // Must use member initializer list to construct object
   // Call setters to validate price and qtyInStock
   name = n;
   count = 0;

   usable = true;
}


//Getters
string Bag::getName() {
   return name;
}

string Bag::getContents() {
  string rc = "";

  for(string s : contents) {
    rc += s + ", ";
  }
  return rc;
}

int Bag::getCapacity() {
  return capacity;
}

int Bag::getCount() {
  return count;
}

bool Bag::getUsable() {
   return usable;
}

// Setters
void Bag::setName(string n) {
   name = n;
}

void Bag::setCapacity(size_t c) {
  if( contents.size() < c ) {
    capacity = c;
  }
}

void Bag::setUsable(bool b) {
  usable = b;
}

//Modifiers
int Bag::addContent(string item){
  if( contents.size() < (size_t)capacity ){
    auto rc = contents.insert(item);
    count++;

    return 1;
  }

  return -1;
}

string Bag::removeContent(string item) {
  contents.erase(item);
}

// print in the format ""Bag-name" by author-name (gender) at email"
void Bag::print() const {
   cout << "'" << name << "' by " << endl;
}
