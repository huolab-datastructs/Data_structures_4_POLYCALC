#include   "../../C/UTILITY.H"
#include "QUEUE.H"
bool Queue::empty() const
/*   
Post: Return true if the Queue is empty,
otherwise return false.
 */
{
   return front == NULL;
}
 
Queue::Queue()
/*   
Post: The Queue is initialized to be empty.
 */
{
   front = rear = NULL;
}
 
Error_code Queue::append(const Queue_entry &item)
/*   
Post: Add item to the rear of the Queue and
return a code of success 
or return a code
of overflow if dynamic memory is exhausted.
 */
{
   Node *new_rear = new Node(item);
   if (new_rear == NULL) return overflow;
   if (rear == NULL) front = rear = new_rear;
   else {
      rear->next = new_rear;
      rear = new_rear;
   }
   return success;
}
 
Error_code Queue::retrieve(Queue_entry &item) const
/*   
Post: The front of the Queue is reported
in item. If the Queue 
is empty return an Error_code
of underflow and leave the Queue unchanged.
 */
{
   if (front == NULL) return underflow;
   item = front->entry;
   return success;
}
 
Error_code Queue::serve()
/*   
Post: The front of the Queue is removed.  If the Queue 
is empty, return an Error_code of underflow.
 */
{
   if (front == NULL) return underflow;
   Node *old_front = front;
   front = old_front->next;
   if (front == NULL) rear = NULL;
   delete old_front;
   return success;
}
 
Queue::~Queue()
{
   while (!empty())
      serve();
}
 
Queue::Queue(const Queue &copy)
{
   Node *copy_node = copy.front;
   front = rear = NULL;
   while (copy_node != NULL) {
      append(copy_node->entry);
      copy_node = copy_node->next;
   }
}
 
void Queue::operator =(const Queue &copy)
{
   while (!empty())
      serve();
   Node *copy_node = copy.front;
   while (copy_node != NULL) {
      append(copy_node->entry);
      copy_node = copy_node->next;
   }
}
