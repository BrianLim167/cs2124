#ifndef NOBLE
#define NOBLE

#include <iostream>
#include <string>
#include <vector>
#include "Warrior.h"

namespace WarriorCraft {
  class Warrior;
  
  class Noble {
  public:
    Noble(const std::string& name);
  
    std::string get_name() const;

    bool is_alive() const;

    //recruit a new warrior to the army, returning true if successful
    bool hire(Warrior& warrior);

    //fire a warrior from the army, returning true if successful
    bool fire(Warrior& warrior, bool hide_message=false);

    //fight another noble's army
    void battle(Noble& other);

    //print facts about the noble's army
    void display();
    
    friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
  private:
    std::string name;
    std::vector<Warrior*> army;
    bool alive;
    int strength;

    //change the health of the army based on the damage ratio
    void damage_army(float ratio);
  };
}

#endif
