#pragma once
#include "../../C/UTILITY.H"
#include "TERM.H"
typedef Term Node_entry;
struct Node {
//  data members
   Node_entry entry;
   Node *next;

//  constructors
   Node();
   Node(Node_entry item, Node *add_on = NULL);
};
