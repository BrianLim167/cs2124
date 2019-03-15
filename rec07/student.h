#include <iostream>
#include <string>
#include <vector>

#ifndef STUDENT
#define STUDENT

#include "course.h"

namespace BrooklynPoly {
  class Course;
  class Student;
}
 
class BrooklynPoly::Student {
  friend std::ostream& operator<<(ostream& os, const Student& rhs);
 public:
  // Student methods needed by Registrar
  Student(const string& name);
  const string& getName() const;
  bool addCourse(Course*);

  // Student method needed by Course
  void removedFromCourse(Course*);

 private:
  string name;
  vector<Course*> courses;
};

#endif
