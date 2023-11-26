#include "Student.h"


// Constructors & destructor
Student::Student(){
}
Student::Student(int id, string studentName, string studentYear, string studentMajor, double studentGPA, int advisor){
    studentID = id;
    name = studentName;
    year = studentYear;
    major = studentMajor;
    gpa = studentGPA;
    advisor = advisorID;
}
Student::~Student(){
}

// Print
void Student::printStudent(){
    cout << "Name: " << name << endl;
    cout << "ID: " << studentID << endl;
    cout << "Year: " << year << endl;
    cout << "Major: " << major << endl;
    cout << "GPA: " << gpa << endl;
    cout << "Advisor: " << advisorID << endl;
}

// Getters and setter

int Student::getID(){
    return studentID;
}
string Student::getName(){
    return name;
}
string Student::getYear(){
    return year;
}
string Student::getMajor(){
    return major;
}
double Student::getGPA(){
    return gpa;
}
int Student::getAdvisor(){
    return advisorID;
}

void Student::setAdvisor(int newAdvisor){
    advisorID = newAdvisor;
}