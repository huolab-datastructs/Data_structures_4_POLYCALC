#include   "../../C/UTILITY.H"
#include "NODE.H" 
#include "TERM.H"
Node::Node()
{
   next = NULL;
}
 
Node::Node(Node_entry item, Node *add_on)
{
   entry = item;
   next = add_on;
}
