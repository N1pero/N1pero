#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

class Student {
private:
    std::string surname;
    float* grades;
    int gradesCount;

public:
    Student();
    Student(const std::string& surname, const float* grades, int gradesCount);
    Student(const Student& other);
    ~Student();

    std::string getSurname() const;
    void setSurname(const std::string& surname);
    void setGrades(const float* grades, int gradesCount);
    void getGrades() const;
    double getAverageGrade() const;

    friend std::ostream& operator<<(std::ostream& out, const Student& student);
    friend std::istream& operator>>(std::istream& in, Student& student);
};

#endif // STUDENT_H