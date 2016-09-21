#include "TERM.H"
Term::Term(int exponent, double scalar)
/* 
 
Post: The Term is initialized with the given coefficient and exponent,
or with default parameter values of 0.
 
*/

{
   degree = exponent;
   coefficient = scalar;
}
