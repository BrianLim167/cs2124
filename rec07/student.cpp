namespace BrooklynPoly {
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
}
