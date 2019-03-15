/*
Brian Lim
rec02.cpp
stores data of chemical formulas
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

struct chemical;
void open_stream(ifstream& ifs);
void get_file_data(vector<chemical>& buf, ifstream& ifs);
int find_chemical(vector<chemical> data, string line);
string get_name(string line);
int get_carbon(string line);
int get_hydrogen(string line);
bool is_less_than(chemical a, chemical b);
int get_min_index(vector<chemical> data, int low, int high);
void swap(vector<chemical>& data, int i, int j);
void sort_chemicals(vector<chemical>& data);
void print_chemical(chemical chem);
void print_chemicals(vector<chemical> data);

struct chemical {
  vector<string> names;
  int num_carbon;
  int num_hydrogen;
};

int main() {
  ifstream ifs;
  vector<chemical> data;

  //read the chemical file data into a vector
  open_stream(ifs);
  cout << endl;
  get_file_data(data, ifs);

  //process the contents of the vector
  sort_chemicals(data);
  print_chemicals(data);

  ifs.close();
}

//ask the user for the filename to create a file stream
void open_stream(ifstream& ifs) {
  do {
    ifs.clear();
    cout << "input data location: ";
    string filename;
    cin >> filename;
    ifs.open(filename.c_str());
    if (!ifs) {
      cout << "failed to open " << filename << endl;
    }
  } while (!ifs);
}

//find the index of an existing chemical in a list, or -1 if it doesn't exist
int find_chemical(vector<chemical> data, string line) {
  int carbon = get_carbon(line);
  int hydrogen = get_hydrogen(line);
  for (int i = 0; i < data.size(); i++) {
    if (data[i].num_carbon == carbon && data[i].num_hydrogen == hydrogen) {
      return i;
    }
  }
  return -1;
}

//determine the chemical name from a line of text
string get_name(string line) {
  return line.substr(0, line.find(" "));
}

//determine the number of carbons of a chemical from a line of text
int get_carbon(string line) {
  return atoi( line.substr(line.find_last_of("C") + 1,
			   line.find_last_of("H")).c_str() );
}

//determine the number of hydrogens of a chemical from a line of text
int get_hydrogen(string line) {
  return atoi( line.substr(line.find_last_of("H") + 1, line.length()).c_str() );
}

//build a list of chemicals from the file stream
void get_file_data(vector<chemical>& buf, ifstream& ifs) {
  string line;
  while (getline(ifs, line)) {
    int i = find_chemical(buf, line);
    /*if the chemical formula already exists in the vector, add to the names of
      the existing entry*/
    if (i >= 0) {
      string name = get_name(line);
      buf[i].names.push_back(name);
    } else { //otherwise, create a new entry
      chemical chem;
      chem.names.push_back(get_name(line));
      chem.num_carbon = get_carbon(line);
      chem.num_hydrogen = get_hydrogen(line);
      buf.push_back(chem);
    }
  }
}

//compare two chemicals to see which should be sorted first
bool is_less_than(chemical a, chemical b){
  return ( a.num_carbon < b.num_carbon ||
	   (a.num_carbon == b.num_carbon && a.num_hydrogen < b.num_hydrogen) ); 
}

//find the index of the least-valued chemical
int get_min_index(vector<chemical> data, int low, int high) {
  int min_index = low;
  for (int i = low; i <= high; i++) {
    if (is_less_than(data[i], data[min_index])) {
      min_index = i;
    }
  }
  return min_index;
}

//swap two entries in a vector
void swap(vector<chemical>& data, int i, int j) {
  chemical temp = data[i];
  data[i] = data[j];
  data[j] = temp;
}

//sort the chemicals in the vector
void sort_chemicals(vector<chemical>& data) {
  for (int i = 0; i < data.size(); i++) {
    int min_index = get_min_index(data, i, data.size() - 1);
    swap(data, i, min_index);
  }
}

//print a representation of a chemical
void print_chemical(chemical chem) {
  cout << "C" << chem.num_carbon << "H" << chem.num_hydrogen;
  for (int j = 0; j < chem.names.size(); j++) {
    cout << " " << chem.names[j];
  }
  cout << endl;
}

//print all the chemicals in the vector
void print_chemicals(vector<chemical> data) {
  for (int i = 0; i < data.size(); i++) {
    print_chemical(data[i]);
  }
}


