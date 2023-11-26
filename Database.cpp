#include "Database.h"


// Constructors & destructor
Database::Database(){
    studentRecords = new LazyBST<Student>();
    facultyRecords = new LazyBST<Faculty>();
}
Database::~Database(){
}

void Database::runDB(){
    mainMenu();
}

void Database::mainMenu(){
    bool running = true;
    while(running){
        printMenu();

        // read choice from terminal
        int choice;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            printStudents();
            break;

        case 2:
            printFaculty();
            break;

        case 3:
            findStudent();
            break;

        case 4:
            findFaculty();
            break;

        case 5:
            addStudent();
            break;

        case 6:
            deleteStudent();
            break;

        case 7:
            addFaculty();
            break;

        case 8:
            deleteFaculty();
            break;

        case 9:
            changeStudentAdvisor();
            break;

        case 10:
            removeAdvisee();
            break;

        case 11:
            running = false;
            break;
        
        default:
            cout << "Invalid selection!" << endl;
            break;
        }
    }
}

void Database::printMenu(){
    cout << "Please select an option: " << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the student id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Add a new student" << endl;
    cout << "6. Delete a student given the id" << endl;
    cout << "7. Add a new faculty member" << endl;
    cout << "8. Delete a faculty member given the id." << endl;
    cout << "9. Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "10. Remove an advisee from a faculty member given the ids" << endl;
    cout << "11. Exit" << endl;
}

void Database::printStudents(){
    cout << "Student records: " << endl;
    studentRecords->printTree();
}
void Database::printFaculty(){
    cout << "Faculty records: " << endl;
    facultyRecords->printTree();
}

// Search through the student database for a student
void Database::findStudent(){
    cout << "Input ID of student to search for: " << endl;
    
    Student *searchStudent;

    int searchID;
    cin >> searchID;
    // Creates a null student with the same ID to compare against
    if(studentRecords->contains(*new Student(searchID, "", "", "", NULL, NULL))){
        searchStudent = studentRecords->find(*new Student(searchID, "", "", "", NULL, NULL));
        searchStudent->printStudent();
    }
    else
        cout << "Student not found" << endl;
}

// Search through the faculty database for a faculty member
void Database::findFaculty(){
    cout << "Input ID of faculty to search for: " << endl;
    
    Faculty *searchFaculty;

    int searchID;
    cin >> searchID;

    if(facultyRecords->contains(*new Faculty(searchID, "", "", ""))){
        searchFaculty = facultyRecords->find(*new Faculty(searchID, "", "", ""));
        searchFaculty->printFaculty();
}
    else
        cout << "Faculty not found" << endl;
}
void Database::addStudent(){
    int newID;
    string newName;
    string newYear;
    string newMajor;
    double newGPA;
    int newAdvisorID;

    cout << "New student name: ";
    cin >> newName;

    while(true){
        cout << "New student ID: ";
        cin >> newID;
        // Check to make sure a student woth that ID is not already in the system
        if(studentRecords->contains(*new Student(newID, "", "", "", NULL, NULL)))
            cout << "ERROR: Student already in system. Please enter alternative ID. " << endl;
        else
            break;
    }

    cout << "New student year: ";
    cin >> newYear;

    cout << "New student major: ";
    cin >> newMajor;

    cout << "New student GPA: ";
    cin >> newGPA;

    while(true){
        cout << "New student advisor ID: ";
        cin >> newAdvisorID;
        // Check to make sure that advisor is in the system
        if(facultyRecords->contains(*new Faculty(newAdvisorID, "", "", ""))){
            facultyRecords->find(*new Faculty(newAdvisorID, "", "", ""))->addAdvisee(newID);
            break;
        }
        else
            cout << "ERROR: Advisor not in system. Please enter ID of advisor in system. " << endl;
    }
    studentRecords->insert(*new Student(newID, newName, newYear, newMajor, newGPA, newAdvisorID));
}
void Database::deleteStudent(){
    int delID;

    cout << "Enter ID of student to be deleted: ";
    cin >> delID;
    // Confirm student is in system
    if(studentRecords->contains(*new Student(delID, "", "", "", NULL, NULL))){
        studentRecords->deleteNode(*new Student(delID, "", "", "", NULL, NULL));
        cout << "Student " << delID << " deleted." << endl;
    }
    else
        cout << "ERROR: Student not found." << endl;
}
void Database::addFaculty(){
    int newID;
    string newName;
    string newLevel;
    string newDepartment;

    cout << "New faculty name: ";
    cin >> newName;

    while(true){
        cout << "New faculty ID: ";
        cin >> newID;
        // Check to make sure faculty ID is not already in use
        if(facultyRecords->contains(*new Faculty(newID, "", "", "")))
            cout << "ERROR: Student already in system. Please enter alternative ID. " << endl;
        else
            break;
    }

    cout << "New faculty level: ";
    cin >> newLevel;

    cout << "New faculty department: ";
    cin >> newDepartment;

    facultyRecords->insert(*new Faculty(newID, newName, newLevel, newDepartment));
}
void Database::deleteFaculty(){
    int delAdvisorID;

    while(true){
        cout << "Enter ID of advisor to delete: ";
        cin >> delAdvisorID;
        // Make sure faculty member is in system
        if(facultyRecords->contains(*new Faculty(delAdvisorID, "", "", ""))){
            break;
        } else {
            cout << "ERROR: Advisor not found. Please enter alternative ID. " << endl;
        }
    }

    // Empty advisee list
    while(!facultyRecords->find(*new Faculty(delAdvisorID, "", "", ""))->advisees->isEmpty()){
        int tempID = facultyRecords->find(*new Faculty(delAdvisorID, "", "", ""))->advisees->removeBack();
        studentRecords->find(*new Student(tempID, "", "", "", NULL, NULL))->setAdvisor(NULL);
    }
    facultyRecords->deleteNode(*new Faculty(delAdvisorID, "", "", ""));
}

void Database::changeStudentAdvisor(){
    int changeID;
    int newID;

    while(true){
        cout << "Enter ID of student to change advisor of: ";
        cin >> changeID;
        // Check if student is in system
        if(studentRecords->contains(*new Student(changeID, "", "", "", NULL, NULL)))
            break;
        else
            cout << "ERROR: Student already in system. Please enter alternative ID. " << endl;
    }

    while(true){
        cout << "Enter ID of new advisor: ";
        cin >> newID;
        // Check if faculty member is in system
        if(facultyRecords->contains(*new Faculty(changeID, "", "", "")))
            break;
        else
            cout << "ERROR: Advisor already in system. Please enter alternative ID. " << endl;
    }

    studentRecords->find(*new Student(changeID, "", "", "", NULL, NULL))->setAdvisor(newID);
}
void Database::removeAdvisee(){
    int delAdviseeID;
    int advisorID;

    while(true){
        cout << "Enter ID of advisor to remove advisee from: ";
        cin >> advisorID;
        // Check if advisor is in system
        if(facultyRecords->contains(*new Faculty(advisorID, "", "", ""))){
            break;
        } else {
            cout << "ERROR: Advisor not found. Please enter alternative ID. " << endl;
        }
    }

    while(true){
        cout << "Enter ID of advisee to remove: ";
        cin >> delAdviseeID;
        if(facultyRecords->find(*new Faculty(advisorID, "", "", ""))->advisees->find(&delAdviseeID) != -1){
            break;
        } else {
            cout << "ERROR: Advisor not found. Please enter alternative ID. " << endl;
        }
    }

    facultyRecords->find(*new Faculty(advisorID, "", "", ""))->advisees->removeNode(&delAdviseeID);
}
