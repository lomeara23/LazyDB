#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include "LinkedList.h"

using namespace std;

class Faculty{
    private:
        int facultyID;
        string name;
        string level;
        string department;

    public:
        // Constructors
        Faculty();
        Faculty(int id, string facultyName, string facultyLevel, string facultyDepartment);
        ~Faculty();

        // Print
        void printFaculty();

        // Getters
        int getID();
        string getName();
        string getLevel();
        string getDepartment();
        

        // Setter
        void addAdvisee(int newAdvisee);
        void removeAdvisee(int delAdvisee);
        
        // Relational operators
        bool operator==(Faculty const &other){return this->facultyID == other.facultyID;}
        bool operator!=(Faculty const &other){return this->facultyID != other.facultyID;}

        bool operator>(Faculty const &other){return this->facultyID > other.facultyID;}
        bool operator<(Faculty const &other){return this->facultyID < other.facultyID;}

        bool operator>=(Faculty const &other){return this->facultyID >= other.facultyID;}
        bool operator<=(Faculty const &other){return this->facultyID <= other.facultyID;}

        // ToString operator
        string toString() const{return to_string(facultyID);}
        friend ostream& operator<<(ostream& stream, const Faculty& obj){return stream << obj.toString();}

        LinkedList<int> *advisees;
};

#endif