/* Header for Foot class (Foot.h) */
#ifndef BAG_H
#define BAG_H

#include <string>
#include <iostream>
#include <set>

class Bag {
private:
   std::string name;
   std::set<std::string> contents;

   int capacity;
   int count;

   bool usable;

public:
  //Contructor
  Bag(const std::string name);

  //Getters
  std::string getName();
  std::string getContents();

  int getCapacity();
  int getCount();

  bool getUsable();
  //Getters

  //Setters
  void setName(std::string name);
  void setCapacity(size_t c);
  void setUsable(bool s);

  //Setters

  //Modifiers
  int addContent(std::string item);
  std::string removeContent(std::string item);

  bool contains(std::string item);
  std::string getItem(std::string obj);
  std::string getItem(int index);


  void print() const;
};

#endif
