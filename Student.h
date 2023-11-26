#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
    private:
        int studentID;
        string name;
        string year;
        string major;
        double gpa;
        int advisorID;


    public:
        // Constructors
        Student();
        Student(int id, string studentName, string studentYear, string studentMajor, double studentGPA, int advisor);
        ~Student();

        // Print
        void printStudent();

        // Getters
        int getID();
        string getName();
        string getYear();
        string getMajor();
        double getGPA();
        int getAdvisor();

        // Setter
        void setAdvisor(int newAdvisor);
        
        // Relational operators
        bool operator==(Student const &other){return this->studentID == other.studentID;}
        bool operator!=(Student const &other){return this->studentID != other.studentID;}

        bool operator>(Student const &other){return this->studentID > other.studentID;}
        bool operator<(Student const &other){return this->studentID < other.studentID;}

        bool operator>=(Student const &other){return this->studentID >= other.studentID;}
        bool operator<=(Student const &other){return this->studentID <= other.studentID;}

        // ToString operator
        string toString() const{return to_string(studentID);}
        friend ostream& operator<<(ostream& stream, const Student& obj){return stream << obj.toString();}
};

#endif