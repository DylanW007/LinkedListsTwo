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
#include <vector>
#include <cstring>
#include "student.h"

using namespace std;

void print(vector<student*>& students) { // Including the vector of pointers so print can access it.

  cout << "==================================" << endl;
  cout << "              PRINT" << endl;             // Nice formatting to make it easier on the user.
  cout << "==================================" << endl;
  cout << "\nStudents:\n\n";
  
  for (student* add : students) {
        cout << add->getFirstName() << " " << add->getLastName()
             << ", ID: " << add->getId()
             << ", GPA: " << fixed << setprecision(2) << add->getGpa() << endl;
  }          //https://www.geeksforgeeks.org/c/rounding-floating-point-number-two-decimal-places-c-c/
  
  cout << "\n";
}

void ADD(vector<student*>& students){ // Including the vector of pointers so add can access it.
  student* add = new student; // https://www.geeksforgeeks.org/cpp/cpp-vector-of-pointers/
  char all[1000] = "\0";     // Used for vector math. Includes adding and removing student pointers.
  
  cout << "==================================" << endl;
  cout << "              ADD" << endl;              // Nice formatting to make it easier on the user.
  cout << "==================================" << endl;
  
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
  
  students.push_back(add);
  cout << "Added " << add->getFirstName() << " " << add->getLastName() << "\n" << endl;
}

void REMOVE(vector<student*>& students){ // Including the vector of pointers so remove can access it.
  cout << "==================================" << endl;
  cout << "              REMOVE" << endl;           // Nice formatting to make it easier on the user.
  cout << "==================================" << endl;
  
  int removeid;
  cout << "Enter ID of student you want to remove: ";
  cin >> removeid;
  
  //"how to remove item from vector c++"
  //https://www.geeksforgeeks.org/cpp/vector-erase-in-cpp-stl/
  
  for (int i = 0; i < students.size(); i++){
      if (students[i]->getId() == removeid){
          cout << "Removed " << students[i]->getFirstName() << " " 
          << students[i]->getLastName() << endl;
          students.erase(students.begin() + i); // Removes student from vector. Used from geeksforgeeks link above.
          return;
      }
  }
}

int main(){
  vector<student*> students; // Declare vector of students in main.
  
  char action[81] = "\0";
  bool run = true;
  while (run == true) {
      cout << "==================================" << endl;
      cout << "             COMMAND" << endl;           // The main command console in which you will enter
      cout << "==================================" << endl; // ADD,REMOVE,PRINT, and QUIT to run.
      
      cout << "Supported commands: { ADD, REMOVE, PRINT, QUIT }\n\nEnter command: ";
      cin >> action;
      
      // Uses strcmp to compare the "action". If true it will be 0.
      if (strcmp(action, "ADD") == 0) {
          cout << "\n\n";
          ADD(students); // Runs add
      } else if (strcmp(action, "REMOVE") == 0 ) {
          REMOVE(students); // Runs remove
      } else if (strcmp(action, "PRINT") == 0) {
          print(students); // Runs print
      } else if (strcmp(action, "QUIT") == 0) {
          cout << "Quitting"; // Runs quit
          return 1;
      } else{
          cout << "Invalid Action." << endl; // Else if none apply, its invalid.
      }
  }
  
  return 0;
}