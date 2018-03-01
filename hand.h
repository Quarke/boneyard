/* Header for Hand class (Hand.h) */
#ifndef HAND_H
#define HAND_H

#include <string>

class Hand {
private:
   std::string side;
   std::string item;
   bool usable;

public:
   Hand(std::string side);

   std::string getSide() const;
   std::string getItem() const;
   bool getUsable();

   void setItem(const std::string item);
   void setUsable(bool s);

   void print() const;
};

#endif
