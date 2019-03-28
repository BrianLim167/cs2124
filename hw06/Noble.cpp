#include "Noble.h"
using namespace std;

namespace WarriorCraft {
  
  Noble::Noble(const string& name) : name(name) {
    alive = true;
    strength = 0;
  }
  
  string Noble::get_name() const {
    return name;
  }

  bool Noble::is_alive() const {
    return alive;
  }

  //recruit a new warrior to the army, returning true if successful
  bool Noble::hire(Warrior& warrior) {
    if (warrior.get_noble() != nullptr) return false;
    if (!alive) return false;
    warrior.set_noble(this);
    army.push_back(&warrior);
    strength += warrior.get_strength();
    return true;
  }

  //fire a warrior from the army, returning true if successful
  bool Noble::fire(Warrior& warrior, bool hide_message/*=false*/) {
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
	if (!hide_message) {
	  cout << "You don't work for me anymore " << warrior.get_name()
	       << "! -- " << get_name() << endl;
	}
	warrior.set_noble(nullptr);
	return true;
      }
    }
  }

  //fight another noble's army
  void Noble::battle(Noble& other) {
    cout << get_name() << " battles " << other.get_name() << endl;
    
    if (!is_alive() && !other.is_alive()) {
      cout << "Oh, NO!	They're both dead!  Yuck!" << endl;
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
  void Noble::display() {
    cout << *this << endl;
  }

  ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.get_name() << " has an army of " << noble.army.size();
    for (size_t i = 0; i < noble.army.size(); i++) {
      os << endl << '\t' << *(noble.army[i]);
    }
    return os;
  }

  
  //change the health of the army based on the damage ratio
  void Noble::damage_army(float ratio) {
    strength = 0; //noble's strength must be recalculated
    for (size_t i = 0; i < army.size(); i++) {
      army[i]->set_strength((1 - ratio) * army[i]->get_strength());
      strength += army[i]->get_strength();
    }
    if (strength == 0) {
      alive = false;
    }
  }

}
