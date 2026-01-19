/*
Dylan Waters
1/15/25

Name : LinkedListsTwo - Student Class Definition
Description : Header file for Student class definition.
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

using namespace std;

/* Student class definition */
class student
{
public:
    // Default constructor
    student() {
        this->id = -1;
        this->gpa = -1.0;
        strcpy(this->firstname, "");
        strcpy(this->lastname, "");
    }
    
    // Convenience constructor
    student(int id, char* first, char* last, float gpa) {
        this->id = id;
        this->gpa = gpa;
        strcpy(this->firstname, first);
        strcpy(this->lastname, last);
    }

    // Destructor
   ~student() { }

    // Getters and Setters
    void setId(int id) { this->id = id; }
    int  getId() { return this->id; }

    void setFirstName(const char* first) { strcpy(this->firstname, first); }
    const char* getFirstName() { return this->firstname; }

    void setLastName(const char* last) { strcpy(this->lastname, last); }
    const char* getLastName() { return this->lastname; }

    void setGpa(float gpa) { this->gpa = gpa; }
    float getGpa() { return this->gpa; }
    
    void print() {
        cout << this->firstname << " " << this->lastname << ", " << id << ", " << fixed << setprecision(2) << this->gpa << endl;
    }
    
private:
    // Student attributes
    char firstname[20];
    char lastname[20];
    int id;
    float gpa;
};


#endif // STUDENT_H
