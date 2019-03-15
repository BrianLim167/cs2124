/*
  rec07 
  Starter Code for required functionality
  Yes, you may add other methods.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "course.h"
#include "student.h"
#include "registrar.h"

namespace BrooklynPoly {
  ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.getName() << ":";
    if (rhs.students.size() == 0) {
      os << " No Students";
    } else {
      for (size_t i = 0; i < rhs.students.size(); i++) {
	os << " " << rhs.students[i]->getName();
      }
    }
    return os;
  }

  Course::Course(const string& courseName) : name(courseName) {}
  
  const string& Course::getName() const {
    return name;
  }
  
  bool Course::addStudent(Student* student) {
    for (size_t i = 0; i < students.size(); i++) {
      if (students[i] == student) {
	return false;
      }
    }
    students.push_back(student);
    return true;
  }
  
  void Course::removeStudentsFromCourse() {
    for (size_t i = 0; i < students.size(); i++) {
      students[i]->removedFromCourse(this);
    }
    students.clear();
  }

ostream& operator<<(ostream& os, const Student& rhs) {
  os << rhs.getName() << ":";
  if (rhs.courses.size() == 0) {
    os << "No Courses";
  } else {
    for (size_t i = 0; i < rhs.courses.size(); i++) {
      os << " " << rhs.courses[i]->getName();
    }
  }
  return os;
}

// Student methods needed by Registrar
Student::Student(const string& name) : name(name) {}
  
const string& Student::getName() const {
  return name;
}
  
  bool Student::addCourse(Course* course) {
  for (size_t i = 0; i < courses.size(); i++) {
    if (courses[i] == course) {
      return false;
    }
  }
  courses.push_back(course);
  return true;
}

// Student method needed by Course
void Student::removedFromCourse(Course* course) {
  for (size_t i = 0; i < courses.size(); i++) {
    if (course == courses[i]) {
      for (size_t j = 0; j < courses.size()-1; j++) {
        Course* temp = courses[j];
	courses[j] = courses[j+1];
	courses[j+1] = temp;
      }
      courses.pop_back();
      return;
    }
  }
}

ostream& operator<<(ostream& os, const Registrar& rhs) {
  os << "Registrar's Report" << endl;
  os << "Courses:" << endl;
  for (size_t i = 0; i < rhs.courses.size(); i++) {
    os << *(rhs.courses[i]) << endl;
  }
  os << "Students:" << endl;
  for (size_t i = 0; i < rhs.students.size(); i++) {
    os << *(rhs.students[i]) << endl;
  }
  return os;
}

Registrar::Registrar() {}

bool Registrar::addCourse(const string& courseName) {
  courses.push_back(new Course(courseName));
  return true;
}

bool Registrar::addStudent(const string& studentName) {
  students.push_back(new Student(studentName));
  return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName,
				      const string& courseName) {
  size_t studentInd = findStudent(studentName);
  size_t courseInd = findCourse(courseName);
  if (studentInd == students.size() || courseInd == courses.size()) {
    return false;
  }
  Student* student = students[studentInd];
  Course* course = courses[courseInd];
  if (!student->addCourse(course)) {
    return false;
  }
  if (!course->addStudent(student)) {
    return false;
  }
  return true;
}

bool Registrar::cancelCourse(const string& courseName) {
  size_t courseInd = findCourse(courseName);
  Course* course = courses[courseInd];
  course->removeStudentsFromCourse();
  for (size_t i = courseInd; i < courses.size()-1; i++) {
    Course* temp = courses[i];
    courses[i] = courses[i+1];
    courses[i+1] = temp;
  }
  courses.pop_back();
  return true;
}

void Registrar::purge() {
  for (size_t i = 0; i < courses.size(); i++) {
    delete courses[i];
  }
  for (size_t i = 0; i < students.size(); i++) {
    delete students[i];
  }
  courses.clear();
  students.clear();
}

size_t Registrar::findStudent(const string& studentName) const {
  for (size_t i = 0; i < students.size(); i++) {
    if (students[i]->getName() == studentName) {
      return i;
    }
  }
  return students.size();
}
  
size_t Registrar::findCourse(const string& courseName) const {
  for (size_t i = 0; i < courses.size(); i++) {
    if (courses[i]->getName() == courseName) {
      return i;
    }
  }
  return courses.size();
}
}

int main() {

  BrooklynPoly::Registrar registrar;

  cout << "No courses or students added yet\n";
  cout << registrar << endl;
     
  cout << "AddCourse CS101.001\n";
  registrar.addCourse("CS101.001");
  cout << registrar << endl;

  cout << "AddStudent FritzTheCat\n";
  registrar.addStudent("FritzTheCat");
  cout << registrar << endl;

  cout << "AddCourse CS102.001\n";
  registrar.addCourse("CS102.001");
  cout << registrar << endl;

  cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
  registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
  cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
  registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
  cout << registrar << endl;

  cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
  cout << "Should fail, i.e. do nothing, "
       << "since Bullwinkle is not a student.\n";
  registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
  cout << registrar << endl;

  cout << "CancelCourse CS102.001\n";
  registrar.cancelCourse("CS102.001");
  cout << registrar << endl;
   
  /*
  // [OPTIONAL - do later if time]
  cout << "ChangeStudentName FritzTheCat MightyMouse\n";
  registrar.changeStudentName("FritzTheCat", "MightyMouse");
  cout << registrar << endl;  

  cout << "DropStudentFromCourse MightyMouse CS101.001\n";
  registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
  cout << registrar << endl;  

  cout << "RemoveStudent FritzTheCat\n";
  registrar.removeStudent("FritzTheCat");
  cout << registrar << endl;  
  */

  cout << "Purge for start of next semester\n";
  registrar.purge();
  cout << registrar << endl;
}
  
