/*
Dylan Waters
11/5/25

Name : LinkedListsTwo - 

Description : Adapted from StudentList project. "Create a struct.  It will have a first name (character array), a last name (character array), a number for the student id (int), and decimal for GPA (float).
Your program should have a vector of struct pointers passed by reference, or a vector pointer (which will point to a vector of struct pointers). (20 points)
Your program will allow you to read in students, print them out, and delete them.  Each of these functions should be in a different method."

In short, you will be able add,remove,print, students and quit the program.

https://codehs.com/sandbox/id/test-Ul6PQw

*/

#include <iostream>
#include <iomanip> // For rounding (setprecision).
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

// Function to create a new student and return a pointer to it.
student* createStudent(){
    student* add = new student;
  
    // https://www.geeksforgeeks.org/c/arrow-operator-in-c-c-with-examples/
    cout << "What is the student's first name?: ";
    char firstname[20];
    cin >> firstname;
    add->setFirstName(firstname);

    cout << "What is the student's last name?: ";
    char lastname[20];
    cin >> lastname;
    add->setLastName(lastname);

    cout << "What is the student's id?: ";
    int id;
    cin >> id;
    add->setId(id);

    cout << "What is the student's gpa?: ";
    float gpa;
    cin >> gpa;
    add->setGpa(gpa);
  
    return add;
}

// need to implement insertion with recursion
node* insertNodeSorted(node* curnode, node* newnode) { 

    //cout << "Inserting student with ID: " << newnode->getstudent()->getId() << endl;

    // if new node student ID is less than the current node then insert just before
    if (curnode == nullptr) {
        //cout << "Inserting at end of list." << endl;
        newnode->setnext(curnode);
        return newnode;
    } else if (newnode->getstudent()->getId() < curnode->getstudent()->getId()) {
        //cout << "Placing student with ID: " << newnode->getstudent()->getId() << " before student with ID: " << curnode->getstudent()->getId() << endl;
        newnode->setnext(curnode);
        return newnode;
    } else {
        //cout << "Moving past student with ID: " << curnode->getstudent()->getId() << endl;
        node* nextnode = curnode->getnext();
        curnode->setnext(insertNodeSorted(nextnode, newnode));
    }
    return curnode;
}

void printList(node* curnode) {
    if (curnode == nullptr) {
        return;
    }

    student* stdt = curnode->getstudent();
    stdt->print();
    
    printList(curnode->getnext());
}

void print(node* head) { // Including the vector of pointers so print can access it.

    cout << "\nStudents:\n\n";

    if (head == nullptr) {
        cout << "No students in the list.\n";
        return;
    }

    printList(head);

    cout << "\n";
}

void addStudent(node* &head, student* newStudent) {
    node* newNode = new node(newStudent);
    newNode->setnext(nullptr);

     head = insertNodeSorted(head, newNode);
}

void averageStudentGPA(node* curnode, float& totalGPA, int& count) {
    // reached end of list
    if (curnode == nullptr) {
        return;
    }

    student* stdt = curnode->getstudent();
    totalGPA += stdt->getGpa();
    count++;

    averageStudentGPA(curnode->getnext(), totalGPA, count);
}

void calculateAverage(node* head) {

    if (head == nullptr) {
        cout << "No students in the list." << endl;
        return;
    }

    float totalGPA = 0.0;
    int count = 0;

    averageStudentGPA(head, totalGPA, count);

    float averageGPA = totalGPA / count;
    cout << "Average GPA of students: " << fixed << setprecision(2) << averageGPA << endl;
}

node* removeStudent(node* head, int studentId) {
    if (head == nullptr) {
        cout << "Student with ID " << studentId << " not found." << endl;
        return nullptr;
    }

    if (head->getstudent()->getId() == studentId) {
        node* temp = head;
        student* stdt = head->getstudent();
        delete stdt; // Free the memory allocated for the student.

        head = head->getnext();
        delete temp;
        return head;
    }

    node* nextnode = head->getnext();
    head->setnext(removeStudent(nextnode, studentId));
    return head;
}

void deleteStudent(node*& head){ // Including the vector of pointers so remove can access it.

    int removeid;
    cout << "Enter ID of student you want to delete: ";
    cin >> removeid;

    if (head == nullptr) {
        cout << "No students in the list." << endl;
        return;
    }

    head = removeStudent(head, removeid);
}

int main(){

    node* head = nullptr; // Initializing head pointer for linked list of students.
  
    char action[81] = "\0";
    bool run = true;
    while (run == true) {
        cout << "==================================" << endl;
        cout << "             COMMAND" << endl;           // The main command console in which you will enter
        cout << "==================================" << endl; // ADD,DELETE,PRINT, and QUIT to run.
        
        cout << "Supported commands: { ADD, DELETE, PRINT, AVERAGE, QUIT }\n\nEnter command: ";
        cin >> action;
        
        // Uses strcmp to compare the "action". If true it will be 0.
        if (strcmp(action, "ADD") == 0) {

            student* add = createStudent();
            addStudent(head, add); // Runs add and head is passed by reference.
        } else if (strcmp(action, "DELETE") == 0 ) {
            deleteStudent(head);
        } else if (strcmp(action, "PRINT") == 0) {
            print(head); // Runs print
        } else if (strcmp(action, "AVERAGE") == 0) {
            calculateAverage(head); // Runs average            
        } else if (strcmp(action, "QUIT") == 0) {

            cout << "Quitting" << endl; // Runs quit
            return 1;
        } else{
            cout << "Invalid Action." << endl; // Else if none apply, its invalid.
        }
    }
  
  return 0;
}