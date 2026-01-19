/*
Dylan Waters
11/5/25

Name : LinkedListsTwo - 

Description : Adapted from StudentList project.

Change your project Student List to use linked lists and a student class (convert your student struct into a class). 
You will need to use recursion for a number of these requirements! Also, no vectors are allowed in this project.
Use the provided Node class (Node.cpp and Node.h) from your partner that has a pointer to the next node and a Student pointer. (20 points)
You should compile your partner's Node.cpp into a Node.o file on your system. (Use the -c flag when compiling to make a .o file.)
You will then create your project using your files and the Node.o file. For example, I might compile my new project using: g++ -o LL Main.cpp Node.o
Your project should have all the same functions that you had for Student List.

StudentList Description:
"Create a struct.  It will have a first name (character array), a last name (character array), a number for the student id (int), and decimal for GPA (float).
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

///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
// Function to insert a new node into the linked list in sorted order based on student ID.
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

///////////////////////////////////////////////////////////////////////////////
// Function to print the linked list of students.
void printList(node* curnode) {
    if (curnode == nullptr) {
        return;
    }

    student* stdt = curnode->getstudent();
    stdt->print();
    
    // recursive call
    printList(curnode->getnext());
}

///////////////////////////////////////////////////////////////////////////////
// Function to print all students in the linked list.
void print(node* head) { // Including the vector of pointers so print can access it.

    cout << "\nStudents:\n\n";

    if (head == nullptr) {
        cout << "No students in the list.\n";
        return;
    }

    printList(head);

    cout << "\n";
}

///////////////////////////////////////////////////////////////////////////////
// Function to add a new student to the linked list.
void addStudent(node* &head, student* newStudent) {
    node* newNode = new node(newStudent);
    newNode->setnext(nullptr);

    // recursive insert into sorted position
    head = insertNodeSorted(head, newNode);
}

///////////////////////////////////////////////////////////////////////////////
// Function to calculate average GPA of students in the linked list.
void averageStudentGPA(node* curnode, float& totalGPA, int& count) {

    // reached end of list
    if (curnode == nullptr) {
        return;
    }

    student* stdt = curnode->getstudent();
    totalGPA += stdt->getGpa();
    count++;

    // recursive call
    averageStudentGPA(curnode->getnext(), totalGPA, count);
}

///////////////////////////////////////////////////////////////////////////////
// Function to calculate and print average GPA of students.
void calculateAverage(node* head) {

    // Check if list is empty
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

///////////////////////////////////////////////////////////////////////////////
// Function to remove a student by ID from the linked list.
node* removeStudent(node* head, int studentId) {
    if (head == nullptr) {
        cout << "Student with ID " << studentId << " not found." << endl;
        return nullptr;
    }

    // Found the student to remove
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

///////////////////////////////////////////////////////////////////////////////
// Function to delete a student by ID from the linked list.
void deleteStudent(node*& head){ // Including the vector of pointers so remove can access it.

    int removeid;
    cout << "Enter ID of student you want to delete: ";
    cin >> removeid;

    // Check if list is empty
    if (head == nullptr) {
        cout << "No students in the list." << endl;
        return;
    }

    head = removeStudent(head, removeid);
}

///////////////////////////////////////////////////////////////////////////////
// Main function to run the student linked list program.
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