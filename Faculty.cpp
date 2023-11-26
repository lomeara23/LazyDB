#include "Faculty.h"


// Constructors & destructor
Faculty::Faculty(){
}
Faculty::Faculty(int id, string facultyName, string facultyLevel, string facultyDepartment){
    facultyID = id;
    name = facultyName;
    level = facultyLevel;
    department = facultyDepartment;
    advisees = new LinkedList<int>();
}
Faculty::~Faculty(){
}

// Print faculty
void Faculty::printFaculty(){
    cout << "Name: " << name << endl;
    cout << "ID: " << facultyID << endl;
    cout << "Level: " << level << endl;
    cout << "Department: " << department << endl;
}

// Getters and setter

int Faculty::getID(){
    return facultyID;
}
string Faculty::getName(){
    return name;
}
string Faculty::getLevel(){
    return level;
}
string Faculty::getDepartment(){
    return department;
}

void Faculty::addAdvisee(int newAdvisee){
    advisees->insertBack(newAdvisee);
}
void Faculty::removeAdvisee(int delAdvisee){
    int* temp = &delAdvisee;
    advisees->removeNode(temp);
}