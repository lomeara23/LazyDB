#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "LbBst.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

class Database{
    private:
        LazyBST<Student> *studentRecords;
        LazyBST<Faculty> *facultyRecords;

        void mainMenu();

        void printMenu();

        void printStudents();
        void printFaculty();
        void findStudent();
        void findFaculty();
        void addStudent();
        void deleteStudent();
        void addFaculty();
        void deleteFaculty();
        void changeStudentAdvisor();
        void removeAdvisee();

    public:
        // Constructors
        Database();
        ~Database();

        void runDB();
};

#endif