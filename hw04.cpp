/*
  Brian Lim
  hw04.cpp
  Armed medieval army fighting game

  BUGS:
  -Allows creating warriors of the same name
  -Allows warrior to fight itself
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

class Warrior;
class Noble;
void run(const string& filename);
void do_warrior(vector<Warrior>& warriors, string name, int strength);
void do_battle(vector<Warrior>& warriors, string name1, string name2);
void do_status(const vector<Warrior>& warriors);

class Warrior {
public:
  Warrior(const string& name, int strength) : name(name), strength(strength) {
    noble = nullptr;
  }
  
  string get_name() const {
    return name;
  }

  int get_strength() const {
    return strength;
  }

  void set_strength(int strength) {
    this->strength = strength;
  }

  Noble* get_noble() const {
    return noble;
  }

  void set_noble(Noble* noble) {
    this->noble = noble;
  }
  
  friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
  string name;
  int strength;
  Noble* noble;
};
ostream& operator<<(ostream& os, const Warrior& warrior) {
  os << warrior.get_name() << ": " << warrior.get_strength();
  return os;
}

class Noble {
public:
  Noble(const string& name) : name(name) {
    alive = true;
    strength = 0;
  }
  
  string get_name() const {
    return name;
  }

  bool is_alive() const {
    return alive;
  }

  //recruit a new warrior to the army, returning true if successful
  bool hire(Warrior& warrior) {
    if (warrior.get_noble() != nullptr) return false;
    if (!alive) return false;
    warrior.set_noble(this);
    army.push_back(&warrior);
    strength += warrior.get_strength();
    return true;
  }

  //fire a warrior from the army, returning true if successful
  bool fire(Warrior& warrior) {
    if (warrior.get_noble() != this) return false;
    if (!alive) return false;
    for (size_t i = 0; i < army.size(); i++) {
      if (army[i] == &warrior) {
	
	//bubble warrior to the end and pop to preserve order
	for (size_t j = i; j < army.size() - 1; j++) {
	  Warrior* swapping = army[j];
	  army[j] = army[j+1];
	  army[j+1] = swapping;
	}
	army.pop_back();
	
	strength -= warrior.get_strength();
	cout << warrior.get_name() << ", you're fired! -- " << get_name() << endl;
	warrior.set_noble(nullptr);
	return true;
      }
    }
  }

  //fight another noble's army
  void battle(Noble& other) {
    cout << get_name() << " battles " << other.get_name() << endl;
    
    if (!is_alive() && !other.is_alive()) {
      cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
    } else if (!is_alive()) {
      cout << "He's dead " << other.get_name() << endl;
    } else if (!other.is_alive()) {
      cout << "He's dead " << get_name() << endl;
    } else if (strength > other.strength) {
      damage_army(1.0 * other.strength / strength);
      other.damage_army(1);
      cout << get_name() << " defeats " << other.get_name() << endl;
    } else if (strength < other.strength) {
      damage_army(1);
      other.damage_army(1.0 * strength / other.strength);
      cout << other.get_name() << " defeats " << get_name() << endl;
    } else {
      damage_army(1);
      other.damage_army(1);
      cout << "Mutual Annihalation: " << get_name() << " and "
	   << other.get_name() << " die at each other's hands" << endl;
    }
  }

  //print facts about the noble's army
  void display() {
    cout << get_name() << " has an army of " << army.size() << endl;
    for (size_t i = 0; i < army.size(); i++) {
      cout << '\t' << *(army[i]) << endl;
    }
  }

private:
  string name;
  vector<Warrior*> army;
  bool alive;
  int strength;

  //change the health of the army based on the damage ratio
  void damage_army(float ratio) {
    strength = 0; //noble's strength must be recalculated
    for (size_t i = 0; i < army.size(); i++) {
      army[i]->set_strength((1 - ratio) * army[i]->get_strength());
      strength += army[i]->get_strength();
    }
    if (strength == 0) {
      alive = false;
    }
  }
};

int main() {
  Noble art("King Arthur");
  Noble lance("Lancelot du Lac");
  Noble jim("Jim");
  Noble linus("Linus Torvalds");
  Noble billie("Bill Gates");

  Warrior cheetah("Tarzan", 10);
  Warrior wizard("Merlin", 15);
  Warrior theGovernator("Conan", 12);
  Warrior nimoy("Spock", 15);
  Warrior lawless("Xena", 20);
  Warrior mrGreen("Hulk", 8);
  Warrior dylan("Hercules", 3);

  jim.hire(nimoy);
  lance.hire(theGovernator);
  art.hire(wizard);
  lance.hire(dylan);
  linus.hire(lawless);
  billie.hire(mrGreen);
  art.hire(cheetah);

  jim.display();
  lance.display();
  art.display();
  linus.display();
  billie.display();

  art.fire(cheetah);
  art.display();
  
  art.battle(lance);
  jim.battle(lance);
  linus.battle(billie);
  billie.battle(lance);


  // NEW OUTPUT CODE
  cout << "==========\n"
       << "Status after all battles, etc.\n";
  jim.display();
  lance.display();
  art.display();
  linus.display();
  billie.display();

}
