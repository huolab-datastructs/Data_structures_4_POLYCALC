#pragma once
#include "../../C/UTILITY.H"
#include "NODE.H"
typedef Node_entry Queue_entry; 
class Queue {
public:
//  standard Queue methods
   Queue();
   bool empty() const;
   Error_code append(const Queue_entry &item);
   Error_code serve();
   Error_code retrieve(Queue_entry &item) const;
//  safety features for linked structures
   ~Queue();
   Queue(const Queue &original);
   void operator =(const Queue &original);
protected:
   Node *front, *rear;
};
