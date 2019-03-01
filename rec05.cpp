/*
  Brian Lim
  rec05.cpp
  lab section simulation
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

class Section;
class LabWorker;

class Section {
public:
  Section(const string& name, const string& day, unsigned hour)
    : name(name), time_slot(day, hour) {}

  Section(const Section& section)
    : name(section.name), time_slot(section.time_slot) {
    for (size_t i = 0; i < section.students.size(); i++) {
      students.push_back(new Student(*section.students[i]));
    }
  }

  ~Section() {
    cout << "Section " << get_name() << " is being deleted" << endl;
    for (size_t i = 0; i < students.size(); i++) {
      cout << "Deleting " << students[i]->get_name() << endl;
      delete students[i];
    }
    students.clear();
  }

  string get_name() const {
    return name;
  }

  void addStudent(const string& name) {
    students.push_back(new Student(name));
  }

  void addGrade(const string& student_name, int grade, unsigned week) {
    Student* student = findStudent(student_name);
    student->addGrade(grade, week);
  }

  friend ostream& operator<<(ostream& os, const Section& section);
private:
  class TimeSlot {
  public:
    TimeSlot(const string& day, unsigned hour) : day(day), hour(hour) {}

    friend ostream& operator<<(ostream& os, const TimeSlot& time_slot) {
      os << "[Day: " << time_slot.day << ", Start time: ";
      if (time_slot.hour == 0 || time_slot.hour == 12) {
	os << 12;
      } else {
	os << time_slot.hour % 12;
      }
      if (time_slot.hour < 12) {
	os << "am";
      } else {
	os << "pm";
      }
      os << "]";
      return os;
    }
  private:
    string day;
    unsigned hour;
  };

  class Student {
  public:
    Student(const string& name) : name(name), grades(14, -1) {}

    string get_name() const {
      return name;
    }

    void addGrade(int grade, unsigned week) {
      grades[week - 1] = grade;
    }

    friend ostream& operator<<(ostream& os, const Student& student) {
      os << "Name: " << student.get_name() << ", Grades: ";
      for (size_t i = 0; i < student.grades.size(); i++) {
	os << student.grades[i] << " ";
      }
      return os;
    }
  private:
    string name;
    vector<int> grades;
  };
  
  string name;
  TimeSlot time_slot;
  vector<Student*> students;

  Student* findStudent(const string& name) const {
    for (size_t i = 0; i < students.size(); i++) {
      if (students[i]->get_name() == name) {
	return students[i];
      }
    }
    return nullptr;
  }
};
ostream& operator<<(ostream& os, const Section& section) {
  os << "Section: " << section.get_name()
     << ", Time slot: " << section.time_slot << ", Students:";
  if (section.students.size() == 0) {
    os << " None";
  }
  for (size_t i = 0; i < section.students.size(); i++) {
    os << endl << *section.students[i];
  }
  return os;
}

class LabWorker {
public:
  LabWorker(const string& name) : name(name), section(nullptr) {}

  string get_name() const {
    return name;
  }

  void addSection(Section& section) {
    this->section = &section;
  }

  void addGrade(const string& student_name, int grade, unsigned week) {
    section->addGrade(student_name, grade, week);
  }

  friend ostream& operator<<(ostream& os, const LabWorker& lab_worker);
private:
  string name;
  Section* section;
};
ostream& operator<<(ostream& os, const LabWorker& lab_worker) {
  os << lab_worker.get_name();
  if (lab_worker.section == nullptr) {
    os << " does not have a section";
  } else {
    os << " has "<< *lab_worker.section;
  }
  return os;
}

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

  cout << "Test 1: Defining a section\n";
  Section secA2("A2", "Tuesday", 16);
  cout << secA2 << endl;

  cout << "\nTest 2: Adding students to a section\n";
  secA2.addStudent("John");
  secA2.addStudent("George");
  secA2.addStudent("Paul");
  secA2.addStudent("Ringo");
  cout << secA2 << endl;

  cout << "\nTest 3: Defining a lab worker.\n";
  LabWorker moe( "Moe" );
  cout << moe << endl;

  cout << "\nTest 4: Adding a section to a lab worker.\n";
  moe.addSection( secA2 );
  cout << moe << endl;

  cout << "\nTest 5: Adding a second section and lab worker.\n";
  LabWorker jane( "Jane" );
  Section secB3( "B3", "Thursday", 11 );
  secB3.addStudent("Thorin");
  secB3.addStudent("Dwalin");
  secB3.addStudent("Balin");
  secB3.addStudent("Kili");
  secB3.addStudent("Fili");
  secB3.addStudent("Dori");
  secB3.addStudent("Nori");
  secB3.addStudent("Ori");
  secB3.addStudent("Oin");
  secB3.addStudent("Gloin");
  secB3.addStudent("Bifur");
  secB3.addStudent("Bofur");
  secB3.addStudent("Bombur");
  jane.addSection( secB3 );
  cout << jane << endl;

  cout << "\nTest 6: Adding some grades for week one\n";
  moe.addGrade("John", 17, 1);  
  moe.addGrade("Paul", 19, 1);  
  moe.addGrade("George", 16, 1);  
  moe.addGrade("Ringo", 7, 1);  
  cout << moe << endl;

  cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
  moe.addGrade("John", 15, 3);  
  moe.addGrade("Paul", 20, 3);  
  moe.addGrade("Ringo", 0, 3);  
  moe.addGrade("George", 16, 3);  
  cout << moe << endl;

  cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
       << "those students (or rather their records?)\n";

  cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
       << "then make sure the following call works:\n";
  doNothing(secA2);
  cout << "Back from doNothing\n\n";
  
} // main
