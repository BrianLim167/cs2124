/*
  Recitation 06
  CS2124
 
  Focus: Dynamic arrays and copy control
*/

#include <string>
#include <iostream>
using namespace std;

class Position {
  friend ostream& operator<<(ostream& os, const Position& rhs) {
    os << '[' << rhs.title << ',' << rhs.salary << ']';
    return os;
  }
public:
  Position(const string& aTitle, double aSalary)
    : title(aTitle), salary(aSalary) {}
  const string& getTitle() const { return title; }
  double getSalary() const { return salary; }
  void changeSalaryTo(double d) { salary = d; }
private:
  string title;
  double salary;
}; // class Position

class Entry {
  friend ostream& operator<<(ostream& os, const Entry& rhs) {
    os << rhs.name << ' ' << rhs.room
       << ' ' << rhs.phone << ", " << *rhs.pos;
    return os;
  }
public:
  Entry(const string& name, unsigned room, unsigned phone, Position& position)
    : name(name), room(room), phone(phone), pos(&position) {
  }
  const string& getName() const { return name; }
  unsigned getPhone() const { return phone; }
private:
  string name;
  unsigned room;
  unsigned phone;
  Position* pos;
}; // class Entry

class Directory {
  friend ostream& operator<<(ostream& os, const Directory& rhs) {
    os << '{';
    for (size_t i = 0; i < rhs.size; i++) {
      os << *(rhs.entries[i]) << "; ";
    }
    os << '}';
    return os;
  }
public:
  size_t CAPACITY = 1;
  Directory() : size(0), capacity(CAPACITY), entries(new Entry*[CAPACITY]){}
  
  Directory(const Directory& dir) {
    cout << "copy" << endl;
    entries = new Entry*[dir.capacity];
    for (size_t i = 0; i < dir.size; i++) {
      entries[i] = new Entry(*(dir.entries[i]));
    }
    size = dir.size;
    capacity = dir.capacity;
  }

  ~Directory() {
    cout << "destruct" << endl;
    for (size_t i = 0; i < size; i++) {
      if (entries[i] != nullptr) {
	delete entries[i];
	entries[i] = nullptr;
      }
    }
    if (entries != nullptr) {
      delete[] entries;
      entries = nullptr;
    }
  }

  Directory& operator=(const Directory& other) {
    if (this == &other) return *this;
    
    cout << "assign" << endl;
    for (size_t i = 0; i < size; i++) {
      if (entries[i] != nullptr) {
	delete entries[i];
	entries[i] = nullptr;
      }
    }
    if (entries != nullptr) {
      delete[] entries;
      entries = nullptr;
    }
    
    entries = new Entry*[other.capacity];
    for (size_t i = 0; i < other.size; i++) {
      entries[i] = new Entry(*(other.entries[i]));
    }
    size = other.size;
    capacity = other.capacity;

    return *this;
  }

  unsigned operator[](const string& name) const {
    for (size_t i = 0; i < size; i++) {
      if (entries[i]->getName() == name) {
	return entries[i]->getPhone();
      }
    }
    cerr << "name " << name << " not found in directory" << endl;
    return 1234567890;
    //exit(1);
  }
  
  void add(const string& name, unsigned room, unsigned ph, Position& pos) {
    if (size == capacity)	{
      capacity *= 2;
      Entry** new_entries = new Entry*[capacity];
      for (size_t i = 0; i < size; i++) {
	new_entries[i] = entries[i];
      }
      entries = new_entries;
    } // if
    entries[size] = new Entry(name, room, ph, pos);
    ++size;
  } // add

private:	
  Entry** entries;
  size_t size;
  size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
	
  // Note that the Postion objects are NOT on the heap.
  Position boss("Boss", 3141.59);
  Position pointyHair("Pointy Hair", 271.83);
  Position techie("Techie", 14142.13);
  Position peon("Peonissimo", 34.79);
	
  // Create a Directory
  Directory d;
  d.add("Marilyn", 123, 4567, boss);
  cout << d << endl;
  
  Directory d2 = d;	// What function is being used??
  d2.add("Gallagher", 111, 2222, techie);
  d2.add("Carmack", 314, 1592, techie);
  cout << d << endl;
  
  cout << "Calling doNothing\n";
  doNothing(d2);
  cout << "Back from doNothing\n";

  Directory d3;
  d3 = d2;
  
  // Should display 1592
  cout << d2["Carmack"] << endl;
  	
  cout << d2["Carm"] << endl;
} // main
