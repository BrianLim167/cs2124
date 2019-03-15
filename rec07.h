#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
  friend ostream& operator<<(ostream& os, const Course& rhs);
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

class Student {
  friend ostream& operator<<(ostream& os, const Student& rhs);
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

class Registrar {
  friend ostream& operator<<(ostream& os, const Registrar& rhs);
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
