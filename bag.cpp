/* Implementation for the class Bag (Bag.cpp) */
#include <iostream>
#include "bag.h"

using namespace std;

// Constructor, with member initializer list to initialize the
Bag::Bag(std::string n) : contents(), capacity(10) {   // Must use member initializer list to construct object
   // Call setters to validate price and qtyInStock
   name = n;
}


//Getters
string Bag::getName() {
   return name;
}

string Bag::getContents() const{
  string rc = "Contents: ";

  for(string s : contents) {
    rc += s + ", ";
  }
  return rc;
}

unsigned long Bag::getCapacity() {
  return capacity;
}

unsigned long Bag::getSize() {
  return contents.size();
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

//Modifiers
void Bag::addContent(string item){
  if( contents.size() < capacity ){
    contents.insert(item);
  }
}

string Bag::removeContent(string item) {
  contents.erase(item);
  return item;
}

void Bag::removeAll() {
  contents.clear();
}

// print in the format ""Bag-name" by author-name (gender) at email"
void Bag::print() const {
   cout << name << getContents() << endl;
}
