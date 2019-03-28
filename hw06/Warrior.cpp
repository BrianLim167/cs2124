#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
  
  Warrior::Warrior(const string& name, int strength) :
    name(name), strength(strength) {
    noble = nullptr;
  }
  
  string Warrior::get_name() const {
    return name;
  }

  int Warrior::get_strength() const {
    return strength;
  }

  void Warrior::set_strength(int strength) {
    this->strength = strength;
  }

  Noble* Warrior::get_noble() const {
    return noble;
  }

  void Warrior::set_noble(Noble* noble) {
    this->noble = noble;
  }

  void Warrior::runaway() {
    cout << name << " flees in terror, abandoning his lord, "
	 << noble->get_name() << endl;
    noble->fire(*this, true);
    noble = nullptr;
  }
  
  ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.get_name() << ": " << warrior.get_strength();
    return os;
  }
}
