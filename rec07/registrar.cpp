namespace BrooklynPoly {
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
