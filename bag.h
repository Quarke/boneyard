/* Header for Bag class (Bag.h) */
#ifndef BAG_H
#define BAG_H

#include <string>
#include <iostream>
#include <set>

class Bag {
private:
   std::string name;
   std::set<std::string> contents;

   unsigned long capacity;

public:
  //Contructor
  Bag(const std::string name);

  //Getters
  std::string getName();
  std::string getContents() const;

  unsigned long getCapacity();
  unsigned long getSize();
  //Getters

  //Setters
  void setName(std::string name);
  void setCapacity(size_t c);

  //Setters

  //Modifiers
  void addContent(std::string item);
  std::string removeContent(std::string item);

  bool contains(std::string item);
  std::string getItem(std::string obj);
  void removeAll();


  void print() const;
};

#endif
