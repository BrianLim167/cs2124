#include <iostream>
#include <string>
#include <vector>

#ifndef REGISTRAR
#define REGISTRAR

namespace BrooklynPoly {
  class Registrar;
}

class BrooklynPoly::Registrar {
  friend std::ostream& operator<<(ostream& os, const Registrar& rhs);
public:
  Registrar();
  bool addCourse(const string&);
  bool addStudent(const string&);
  bool enrollStudentInCourse(const string& studentName,
			     const string& courseName);
  bool cancelCourse(const string& courseName);
  void purge();

private:
  size_t findStudent(const string&) const;
  size_t findCourse(const string&) const;

  vector<Course*> courses;
  vector<Student*> students;
};

#endif
