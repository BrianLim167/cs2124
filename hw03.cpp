/*
  Brian Lim
  hw03.cpp
  Armed medieval warrior fighting game

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
void run(const string& filename);
void do_warrior(vector<Warrior>& warriors, string warrior_name,
		string weapon_name, int strength);
void do_battle(vector<Warrior>& warriors, string name1, string name2);
void do_status(const vector<Warrior>& warriors);


class Warrior {
public:
  Warrior(const string& warrior_name, const string& weapon_name,
	  int strength) :
    name(warrior_name), weapon(weapon_name, strength) {}
  
  string get_warrior_name() const {
    return name;
  }

  string get_weapon_name() const {
    return weapon.get_name();
  }

  int get_strength() const {
    return weapon.get_strength();
  }

  void set_strength(int new_strength) {
    weapon.set_strength(new_strength);
  }
  
  friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
  class Weapon {
  public:
    Weapon(const string& new_name, int new_strength) :
      name(new_name), strength(new_strength) {}
    
    string get_name() const {
      return name;
    }
    
    int get_strength() const {
      return strength;
    }

    void set_strength(int new_strength) {
      strength = new_strength;
    }
    
    friend ostream& operator<<(ostream& os, const Weapon& weapon){
      os << "weapon: " << weapon.name << ", " << weapon.strength;
      return os;
    }
  private:
    string name;
    int strength;
  };
  
  string name;
  Weapon weapon;
};
ostream& operator<<(ostream& os, const Warrior& warrior) {
  os << "Warrior: " << warrior.name << ", " << warrior.weapon;
  return os;
}



int main() {

  const string INPUT_FILE = "warriors.txt";
  run(INPUT_FILE);

}


//execute a single command from the user input
void run(const string& filename) {

  ifstream ifs(filename.c_str());
  
  vector<Warrior> warriors;

  string token;
  while (ifs >> token) {
    //determine which command to execute
    if (token == "Warrior") {
      string warrior_name;
      string weapon_name;
      int strength;
      ifs >> warrior_name >> weapon_name >> strength;
      do_warrior(warriors, warrior_name, weapon_name, strength);
    } else if (token == "Battle") {
      string name1;
      string name2;
      ifs >> name1 >> name2;
      do_battle(warriors, name1, name2);
    } else if (token == "Status") {
      do_status(warriors);
    } else {
      cerr << "invalid command " << token;
    }
  }
  ifs.close();
  
}

//do the warrior command, which creates a new warrior
void do_warrior(vector<Warrior>& warriors, string warrior_name,
		string weapon_name, int strength) {

  warriors.push_back(Warrior(warrior_name, weapon_name, strength));

}

//do the battle command, which makes warriors fight
void do_battle(vector<Warrior>& warriors, string name1, string name2) {

  size_t warrior1_ind = warriors.size();
  size_t warrior2_ind = warriors.size();

  //find the indices of the involved warriors
  for (size_t i = 0; i < warriors.size(); i++) {
    if (warriors[i].get_warrior_name() == name1) {
      warrior1_ind = i;
    }
    if (warriors[i].get_warrior_name() == name2) {
      warrior2_ind = i;
    }
  }
  
  if (warrior1_ind == warriors.size() || warrior2_ind == warriors.size()) {
    return;
  }

  cout << warriors[warrior1_ind].get_warrior_name() << " battles "
       << warriors[warrior2_ind].get_warrior_name() << endl;

  //determine if a fighter is already dead
  if (warriors[warrior1_ind].get_strength() <= 0 &&
      warriors[warrior2_ind].get_strength() <= 0) { //1 and 2 dead
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
  } else if (warriors[warrior1_ind].get_strength() > 0 &&
             warriors[warrior2_ind].get_strength() <= 0) { //only 2 dead
    cout << "He's dead, " << warriors[warrior1_ind].get_warrior_name() << endl;
  } else if (warriors[warrior1_ind].get_strength() <= 0 &&
             warriors[warrior2_ind].get_strength() > 0) { //only 1 dead
    cout << "He's dead, " << warriors[warrior2_ind].get_warrior_name() << endl;
  }

  else { //both alive

    //warriors lose strength from fighting
    int strength1 = warriors[warrior1_ind].get_strength();
    int strength2 = warriors[warrior2_ind].get_strength();
    warriors[warrior1_ind].set_strength(max(0, strength1 - strength2));
    warriors[warrior2_ind].set_strength(max(0, strength2 - strength1));

    //determine outcome of fight
    if (warriors[warrior1_ind].get_strength() <= 0 &&
        warriors[warrior2_ind].get_strength() <= 0) { //1 and 2 killed
      cout << "Mutual Annihilation: "
	   << warriors[warrior1_ind].get_warrior_name()
           << " and " << warriors[warrior2_ind].get_warrior_name()
           << " die at each other's hands" << endl;
    } else if (warriors[warrior1_ind].get_strength() <= 0) { //only 1 killed
      cout << warriors[warrior2_ind].get_warrior_name() << " defeats "
           << warriors[warrior1_ind].get_warrior_name() << endl;
    } else { //only 2 killed
      cout << warriors[warrior1_ind].get_warrior_name() << " defeats "
           << warriors[warrior2_ind].get_warrior_name() << endl;
    }
  }
  
}

//do the status command, which displays all the warriors and their strengths
void do_status(const vector<Warrior>& warriors) {

  cout << "There are: " << warriors.size() << " warriors" << endl;

  for (size_t i = 0; i < warriors.size(); i++) {
    cout << warriors[i] << endl;
  }

}
