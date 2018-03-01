/* Header for Foot class (Foot.h) */
#ifndef FEET_H
#define FEET_H

#include <string>

class Feet {
private:
   std::string item;
   bool usable;

public:
   Feet();
          // & specifies pass by reference, const for non-mutable
   std::string getItem() const;
   bool getUsable();

   void setItem(const std::string item);
   void setUsable(bool s);

   void print() const;
};

#endif
