#include "Group.h"
#include "Exceptions.h"

using namespace std;

Group::Group() : groupNumber(0), students(nullptr), studentCount(0) {
	cout << "The default constructor for group was called (address: " << this << ")\n";
}

Group::Group(int groupNumber) : groupNumber(groupNumber), students(nullptr), studentCount(0) {
	if (groupNumber <= 0) {
		throw GroupException("Error: group number must be positive!");
	}
	cout << "The constructor with parameters for group #" << groupNumber << " was called (address: " << this << ")\n";
}

Group::Group(const Group& other) : groupNumber(other.groupNumber), studentCount(other.studentCount) {
	cout << "Called copy constructor for group #" << other.groupNumber << " (address: " << this << ")\n";
	if (other.studentCount > 0) {
		students = new Student * [other.studentCount];
		for (int i = 0; i < other.studentCount; ++i) {
			students[i] = new Student(*other.students[i]);
		}
	}
	else {
		students = nullptr;
	}
}

Group::~Group() {
	for (int i = 0; i < studentCount; ++i) {
		delete students[i];
	}
	delete[] students;
	cout << "Destructor called for group #" << groupNumber << " (address: " << this << ")\n";
}

int Group::getGroupNumber() const {
	return groupNumber;
}

void Group::setGroupNumber(int number) {
	if (number <= 0) {
		throw GroupException("Error: group number must be positive!");
	}
	groupNumber = number;
}

void Group::addStudent(Student* student) {
	if (!student) {
		throw GroupException("Error: student pointer cannot be null!");
	}

	Student** newStudents = new Student * [studentCount + 1];
	for (int i = 0; i < studentCount; ++i) {
		newStudents[i] = students[i];
	}
	newStudents[studentCount] = student;
	delete[] students;
	students = newStudents;

	++studentCount;
	cout << "Student successfully added to group #" << groupNumber << ".\n";
}

void Group::addStudentAtPosition(Student* student, int position) {
	if (!student) {
		throw GroupException("Error: student pointer cannot be null!");
	}

	if (position < 0 || position > studentCount) {
		throw GroupException("Error: invalid position to add student!");
	}

	Student** newStudents = new Student * [studentCount + 1];
	for (int i = 0, j = 0; i < studentCount + 1; ++i) {
		if (i == position) {
			newStudents[i] = student;
		}
		else {
			newStudents[i] = students[j++];
		}
	}

	delete[] students;
	students = newStudents;
	++studentCount;

	cout << "Student added at position " << position + 1 << " in group #" << groupNumber << ".\n";
}

void Group::removeStudent(int index) {
	if (index < 0 || index >= studentCount) {
		throw GroupException("Error: invalid student index!");
	}

	delete students[index];
	for (int i = index; i < studentCount - 1; ++i) {
		students[i] = students[i + 1];
	}

	--studentCount;
	cout << "Student successfully removed from group #" << groupNumber << ".\n";
}

void Group::showStudents() const {
	if (studentCount == 0) {
		cout << "group #" << groupNumber << " �����.\n";
		return;
	}

	cout << "Group #" << groupNumber << ":\n";
	for (int i = 0; i < studentCount; ++i) {
		cout << " Student #" << i + 1 << ": " << students[i]->getSurname()
			<< ", Average Grade: " << students[i]->getAverageGrade() << "\n";
	}
}

double Group::getAverageGrade() const {
	if (studentCount == 0) {
		throw GroupException("Error: Cannot calculate average grade for group with no students!");
	}

	double total = 0.0;
	for (int i = 0; i < studentCount; ++i) {
		total += students[i]->getAverageGrade();
	}

	return total / studentCount;
}

Student* Group::getStudent(int index) const {
	if (index < 0 || index >= studentCount) {
		throw GroupException("Error: invalid student index!");
	}

	return students[index];
}

int Group::getStudentCount() const {
	return studentCount;
}