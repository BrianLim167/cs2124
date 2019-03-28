#ifndef WARRIOR
#define WARRIOR

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"

namespace WarriorCraft {
  class Noble;
  
  class Warrior {
  public:
    Warrior(const std::string& name, int strength);
    std::string get_name() const;
    int get_strength() const;
    void set_strength(int strength);
    Noble* get_noble() const;
    void set_noble(Noble* noble);
    void runaway();
    friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
  private:
    std::string name;
    int strength;
    Noble* noble;
  };
}

#endif
