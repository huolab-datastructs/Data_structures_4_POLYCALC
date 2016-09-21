#include "../../C/UTILITY.H"
#include "EXTQUEUE.H"
Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
/*   
Post: The front of the Queue is removed and reported
in item. If the Queue 
is empty return an Error_code
of underflow and leave the Queue unchanged.
 */
{
   if (front == NULL) return underflow;
   Node *old_front = front;
   item = old_front->entry;
   front = old_front->next;
   if (front == NULL) rear = NULL;
   delete old_front;
   return success;
}
 
bool Extended_queue::full() const
{
   return false;
}
 
void Extended_queue::clear()
{
   while (!empty())
      serve();
}
 
int Extended_queue::size() const
/*   
Post:   Return the number of entries in the Extended_queue.
 */
{
   Node *window = front;
   int count = 0;
   while (window != NULL) {
      window = window->next;
      count++;
   }
   return count;
}
