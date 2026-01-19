#ifndef NODE_H
#define NODE_H
#include"student.h"
#include<iostream>
using namespace std;

class node
{
 private:
  student* stdt;
  node* next;
 public:
 //void setvalue(nstudent);//sets node value to student
 student* getstudent();//gets the corresponding student for the current node
 void setnext(node* nnext);//sets pointer to next in chain
 node* getnext();//gets sthe next node in the chain
  node(student* nstudent);//constructs node
  ~node();//destructor
};
#endif