/*
Brian Lim
hw02.cpp
Medieval warrior fighting game

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

struct Warrior;
vector<string> get_lines(const string& filename);
vector<string> get_tokens(const string& line);
void run(const string& command, vector<Warrior>& warriors);
void do_warrior(const vector<string>& args, vector<Warrior>& warriors);
void do_battle(const vector<string>& args, vector<Warrior>& warriors);
void do_status(const vector<string>& args, const vector<Warrior>& warriors);

struct Warrior{
  string name;
  int strength;
};

int main() {

  const string INPUT_FILE = "warriors.txt";

  vector<string> commands = get_lines(INPUT_FILE);
  vector<Warrior> warriors;

  for (size_t i = 0; i < commands.size(); i++) {
    run(commands[i], warriors);
  }
  
}

//read in file contents to a list of its lines
vector<string> get_lines(const string& filename) {

  vector<string> buf;
  
  ifstream ifs(filename.c_str());
  if (!ifs) {
    cerr << "failed to open " << filename << endl;
    exit(1);
  }

  //push each line to the buffer
  string line;
  while (getline(ifs, line)) {
    buf.push_back(line);
  }
  ifs.close();

  return buf;

}

//read in a line of tokens to a list of its tokens
vector<string> get_tokens(const string& line) {

  vector<string> buf;

  stringstream linestream(line);

  string token;
  while (linestream >> token) {
    buf.push_back(token);
  }

  return buf;

}

//execute a single command from the user input
void run(const string& line, vector<Warrior>& warriors) {

  vector<string> args = get_tokens(line);

  if (args.size() == 0) {
    return;
  }

  //determine which command to execute
  if (args[0] == "Warrior") {
    do_warrior(args, warriors);
  } else if (args[0] == "Battle") {
    do_battle(args, warriors);
  } else if (args[0] == "Status") {
    do_status(args, warriors);
  } else {
    cerr << "invalid command " << args[0];
  }
  
}

//do the warrior command, which creates a new warrior
void do_warrior(const vector<string>& args, vector<Warrior>& warriors) {

  Warrior new_warrior;
  new_warrior.name = args[1];
  new_warrior.strength = atoi(args[2].c_str());
  warriors.push_back(new_warrior);

}

//do the battle command, which makes warriors fight
void do_battle(const vector<string>& args, vector<Warrior>& warriors) {

  size_t warrior1_ind = -1;
  size_t warrior2_ind = -1;

  //find the indices of the involved warriors
  for (size_t i = 0; i < warriors.size(); i++) {
    if (warriors[i].name == args[1]) {
      warrior1_ind = i;
    }
    if (warriors[i].name == args[2]) {
      warrior2_ind = i;
    }
  }
  
  if (warrior1_ind == -1 || warrior2_ind == -1) {
    return;
  }

  cout << warriors[warrior1_ind].name << " battles "
       << warriors[warrior2_ind].name << endl;

  //determine if a fighter is already dead
  if (warriors[warrior1_ind].strength <= 0 &&
      warriors[warrior2_ind].strength <= 0) { //1 and 2 dead
    cout << "Oh, NO! They're both dead! Yuck!" << endl;
  } else if (warriors[warrior1_ind].strength > 0 &&
	     warriors[warrior2_ind].strength <= 0) { //only 2 dead
    cout << "He's dead, " << warriors[warrior1_ind].name << endl;
  } else if (warriors[warrior1_ind].strength <= 0 &&
	     warriors[warrior2_ind].strength > 0) { //only 1 dead
    cout << "He's dead, " << warriors[warrior2_ind].name << endl;
  }

  else { //both alive

    //warriors lose strength from fighting
    int strength1 = warriors[warrior1_ind].strength;
    int strength2 = warriors[warrior2_ind].strength;
    warriors[warrior1_ind].strength = max(0, strength1 - strength2);
    warriors[warrior2_ind].strength = max(0, strength2 - strength1);

    //determine outcome of fight
    if (warriors[warrior1_ind].strength <= 0 &&
	warriors[warrior2_ind].strength <= 0) { //1 and 2 killed
      cout << "Mutual Annihilation: " << warriors[warrior1_ind].name
	   << " and " << warriors[warrior2_ind].name
	   << " die at each other's hands" << endl;
    } else if (warriors[warrior1_ind].strength <= 0) { //only 1 killed
      cout << warriors[warrior2_ind].name << " defeats "
	   << warriors[warrior1_ind].name << endl;
    } else { //only 2 killed
      cout << warriors[warrior1_ind].name << " defeats "
	   << warriors[warrior2_ind].name << endl;
    }
  }
  
}

//do the status command, which displays all the warriors and their strengths
void do_status(const vector<string>& args, const vector<Warrior>& warriors) {

  cout << "There are: " << warriors.size() << " warriors" << endl;

  for (size_t i = 0; i < warriors.size(); i++) {
    cout << "Warrior: " << warriors[i].name << ", strength: "
	 << warriors[i].strength << endl;
  }

}
