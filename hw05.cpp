/*
  Brian Lim
  hw05.cpp
  Armed medieval army fighting game
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
struct game_info;
void run(const string& filename);
void do_noble(game_info& game, const string& name);
void do_warrior(game_info& game, const string& name, int strength);
void do_hire(game_info& game, const string& noble, const string& warrior);
void do_fire(game_info& game, const string& noble, const string& warrior);
void do_battle(game_info& game, const string& noble1, const string& noble2);
void do_status(const game_info& game);
void do_clear(game_info& game);
Noble* find_noble(const game_info& game, const string& name);
Warrior* find_warrior(const game_info& game, const string& name);

struct game_info {
  vector<Warrior*> warriors;
  vector<Noble*> nobles;
};

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
	cout << "You don't work for me anymore " << warrior.get_name()
	     << "! -- " << get_name() << endl;
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
    cout << *this << endl;
  }

  friend ostream& operator<<(ostream& os, const Noble& noble);
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
ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.get_name() << " has an army of " << noble.army.size();
    for (size_t i = 0; i < noble.army.size(); i++) {
      os << endl << '\t' << *(noble.army[i]);
    }
    return os;
}

int main() {

  const string INPUT_FILE = "nobleWarriors.txt";
  run(INPUT_FILE);
  
}

//execute the commands from the user input
void run(const string& filename) {

  ifstream ifs(filename.c_str());

  vector<Warrior*> warriors;
  vector<Noble*> nobles;

  game_info game;
  game.warriors = warriors;
  game.nobles = nobles;

  string command;
  while (ifs >> command) {
    //determine which command to execute
    if (command == "Noble") {
      string name;
      ifs >> name;
      do_noble(game, name);
    } else if (command == "Warrior") {
      string name;
      int strength;
      ifs >> name >> strength;
      do_warrior(game, name, strength);
    } else if (command == "Hire") {
      string noble;
      string warrior;
      ifs >> noble >> warrior;
      do_hire(game, noble, warrior);
    } else if (command == "Fire") {
      string noble;
      string warrior;
      ifs >> noble >> warrior;
      do_fire(game, noble, warrior);
    } else if (command == "Battle") {
      string noble1;
      string noble2;
      ifs >> noble1 >> noble2;
      do_battle(game, noble1, noble2);
    } else if (command == "Status") {
      do_status(game);
    } else if (command == "Clear") {
      do_clear(game);
    }
  }
  ifs.close();
  
}

//do the noble command, which creates a new noble
void do_noble(game_info& game, const string& name) {
  if (find_noble(game, name) == nullptr) {
    game.nobles.push_back(new Noble(name));
  } else {
    cout << "ERROR: Noble " << name << " already exists!" << endl;
  }
}

//do the warrior command, which creates a new warrior
void do_warrior(game_info& game, const string& name, int strength) {
  if (find_warrior(game, name) == nullptr) {
    game.warriors.push_back(new Warrior(name, strength));
  } else {
    cout << "ERROR: Warrior " << name << " already exists!" << endl;
  }
}

//do the hire command, which recruits a warrior to a noble's army
void do_hire(game_info& game, const string& noble, const string& warrior) {
  Noble* hirer = find_noble(game, noble);
  Warrior* hiree = find_warrior(game, warrior);
  if (hirer == nullptr) {
    cout << "ERROR: Noble " << noble << " does not exist!" << endl;
  } else if (hiree == nullptr) {
    cout << "ERROR: Warrior " << warrior << " does not exist!" << endl;
  } else {
    hirer->hire(*hiree);
  }
}

//do the fire command, which fires a warrior from a noble's army
void do_fire(game_info& game, const string& noble, const string& warrior) {
  Noble* firer = find_noble(game, noble);
  Warrior* firee = find_warrior(game, warrior);
  if (firer == nullptr) {
    cout << "ERROR: Noble " << noble << " does not exist!" << endl;
  } else if (firee == nullptr) {
    cout << "ERROR: Warrior " << warrior << " does not exist!" << endl;
  } else if (firee->get_noble() != firer) {
    cout << "ERROR: Warrior " << warrior << " is not in "
	 << noble << "'s army!" << endl;
  } else {
    firer->fire(*firee);
  }
}

//do the battle command, which makes nobles' armies fight
void do_battle(game_info& game, const string& noble1, const string& noble2) {
  Noble* battler = find_noble(game, noble1);
  Noble* battlee = find_noble(game, noble2);
  if (battler == nullptr) {
    cout << "ERROR: Noble " << noble1 << " does not exist!" << endl;
  } else if (battlee == nullptr) {
    cout << "ERROR: Noble " << noble2 << " does not exist!" << endl;
  } else {
    battler->battle(*battlee);
  }
}

//do the status command, which displays all the nobles' armies and warriors
void do_status(const game_info& game) {
  
  cout << "Status" << endl;
  cout << "======" << endl;
  cout << "Nobles:" << endl;
  for (size_t i = 0; i < game.nobles.size(); i++) {
    cout << *game.nobles[i] << endl;
  }
  if (game.nobles.empty()) {
    cout << "NONE" << endl;
  }
  cout << "Unemployed Warriors:" << endl;
  bool has_unemployed = false;
  for (size_t i = 0; i < game.warriors.size(); i++) {
    if (game.warriors[i]->get_noble() == nullptr) {
      cout << *game.warriors[i] << endl;
      has_unemployed = true;
    }
  }
  if (!has_unemployed) {
    cout << "NONE" << endl;
  }
  
}

//do the clear command, which clears all game data
void do_clear(game_info& game) {

  for (size_t i = 0; i < game.nobles.size(); i++) {
    delete game.nobles[i];
  }
  for (size_t i = 0; i < game.warriors.size(); i++) {
    delete game.warriors[i];
  }
  game.nobles.clear();
  game.warriors.clear();

}

//get the noble with the given name
Noble* find_noble(const game_info& game, const string& name) {
  for (size_t i = 0; i < game.nobles.size(); i++) {
    if (game.nobles[i]->get_name() == name) {
      return game.nobles[i];
    }
  }
  return nullptr;
}

//get the warrior with the given name
Warrior* find_warrior(const game_info& game, const string& name) {
  for (size_t i = 0; i < game.warriors.size(); i++) {
    if (game.warriors[i]->get_name() == name) {
      return game.warriors[i];
    }
  }
  return nullptr;
}

