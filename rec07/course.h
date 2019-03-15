#include <iostream>
#include <string>
#include <vector>

#ifndef COURSE
#define COURSE

#include "student.h"

namespace BrooklynPoly {
  class Course;
}

class BrooklynPoly::Course {
  friend std::ostream& operator<<(ostream& os, const Course& rhs);
public:
  // Course methods needed by Registrar
  Course(const string& courseName);
  const string& getName() const;
  bool addStudent(Student*);
  void removeStudentsFromCourse(); 

private:
  string name;
  vector<Student*> students;
};

#endif
