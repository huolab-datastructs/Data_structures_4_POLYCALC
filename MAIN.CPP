#include "TERM.H"
#include "NODE.H"
#include "QUEUE.H"
#include "EXTQUEUE.H"
#include "POLYNOMI.H"
#include "STACK.H"


void introduction()
/* PRE:  None.
   POST: An introduction to the program Polynomial Calculator is printed. */
{
   cout << "Polynomial Calculator Program." << endl
        << "This program simulates a polynomial calculator that works on a\n"
        << "stack and a list of operations. The model is of a reverse Polish\n"
        << "calculator where operands are entered before the operators. An\n"
        << "example to add two polynomials and print the answer is ?P?Q+= .\n"
        << "P and Q are the operands to be entered, + is add, and = is\n"
        << "print result. The result is put onto the calculator's stack.\n\n";
}

void instructions()
/* PRE:  None.
   POST: Prints out the instructions and the operations allowed on the
         calculator.                                                       */
{
  cout << "\nEnter a string of instructions in reverse Polish form.\n"
       << "The allowable instructions are:\n\n"
       << "?:Read       +:Add           =:Print      -:Subtract\n"
       << "*:Multiply   q:Quit          /:Divide        h:Help\n\n";
}

char get_command()
/* PRE:  None.
   POST: A legal command is read from the user and returned.  */
{
   char command, d;
   cout << "Select command and press <Enter>:";
   while (1) {
      do {
         cin.get(command);
      } while (command == '\n');
      do {
         cin.get(d);
      } while (d != '\n');
      command = tolower(command);
      if (command == '?' || command == '=' || command == '+' || 
          command == '-' || command == 'h' || command == '*' || 
          command == '/' || command == 'q' || command == 'p' || 
          command == 'h') {
         return (command);
      }
      cout << "Please enter a valid command:" << endl;
      instructions();
   }
}
 
bool do_command(char command, Stack &stored_polynomials)
/* 
Pre:  The first parameter specifies a valid
calculator command.
Post:
The command specified by the first parameter
has been applied to the Stack of Polynomial 
objects given by the second parameter.
A result of true is returned unless
command == 'q'.
Uses:
The classes Stack and Polynomial.
*/
{
   Polynomial p, q, r;
   switch (command) {
   case '?':
      p.read();
      if (stored_polynomials.push(p) == overflow)
         cout << "Warning: Stack full, lost polynomial" << endl;
      break;

   case '=':
      if (stored_polynomials.empty())
         cout << "Stack empty" << endl;
      else {
         stored_polynomials.top(p);
         p.print();
      }
      break;

   case '+':
      if (stored_polynomials.empty())
         cout << "Stack empty" << endl;
      else {
         stored_polynomials.top(p);
         stored_polynomials.pop();
         if (stored_polynomials.empty()) {
            cout << "Stack has just one polynomial" << endl;
            stored_polynomials.push(p);
         }

         else {
            stored_polynomials.top(q);
            stored_polynomials.pop();
            r.equals_sum(q, p);
            if (stored_polynomials.push(r) == overflow)
               cout << "Warning: Stack full, lost polynomial" << endl;
         }
      }
      break;
 
   //   Add options for further user commands.
 
   case '/':
      if (stored_polynomials.empty()) cout << "Stack empty" << endl;
      else {
         stored_polynomials.top(p);
         stored_polynomials.pop();
         if (stored_polynomials.empty()) {
            cout << "Stack has just one polynomial" << endl;
            stored_polynomials.push(p);
         }
         else {
            stored_polynomials.top(q);
            stored_polynomials.pop();
            if (r.equals_quotient(q, p) != success) {
               cerr << "Division by 0 fails; no action done." << endl;
               stored_polynomials.push(q);
               stored_polynomials.push(p);
            }
            else if (stored_polynomials.push(r) == overflow)
               cout << "Warning: Stack full, lost polynomial" << endl;
         }
      }
      break;

   case '-':
      if (stored_polynomials.empty()) cout << "Stack empty" << endl;
      else {
         stored_polynomials.top(p);
         stored_polynomials.pop();
         if (stored_polynomials.empty()) {
            cout << "Stack has just one polynomial" << endl;
            stored_polynomials.push(p);
         }
         else {
            stored_polynomials.top(q);
            stored_polynomials.pop();
            r.equals_difference(q, p);
            if (stored_polynomials.push(r) == overflow)
               cout << "Warning: Stack full, lost polynomial" << endl;
         }
      }
      break;

   case '*':
      if (stored_polynomials.empty()) cout << "Stack empty" << endl;
      else {
         stored_polynomials.top(p);
         stored_polynomials.pop();
         if (stored_polynomials.empty()) {
            cout << "Stack has just one polynomial" << endl;
            stored_polynomials.push(p);
         }
         else {
            stored_polynomials.top(q);
            stored_polynomials.pop();
            r.equals_product(q, p);
            if (stored_polynomials.push(r) == overflow)
               cout << "Warning: Stack full, lost polynomial" << endl;
         }
      }
      break;

   case 'h':
      instructions();
      break;
   case 'q':
      cout << "Calculation finished." << endl;
      return false;
   }
   return true;
}
 
int main()
/* 
The program has executed simple polynomial arithmetic
commands entered by the user.
Uses:
The classes Stack and Polynomial and the functions
introduction, instructions, do_command, and
get_command.
*/
{
   Stack stored_polynomials;
   introduction();
   instructions();
   while (do_command(get_command(), stored_polynomials));
}
