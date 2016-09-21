#include "../../C/UTILITY.H"
#include "POLYNOMI.H"
void Polynomial::mult_term(Polynomial p, Term t)
{
   clear();
   while (!p.empty()) {
      Term pterm;
      p.serve_and_retrieve(pterm);
      Term answer_term(pterm.degree + t.degree,
                       t.coefficient * pterm.coefficient);
      append(answer_term);
   }
}

int Polynomial::degree() const
/*

Post:
If the Polynomial is identically 0, a result of -1 is returned.
Otherwise the degree of the Polynomial is returned.

*/

{
   if (empty()) return -1;
   Term lead;
   retrieve(lead);
   return lead.degree;
}

void Polynomial::print() const
/*
Post: The Polynomial is printed to cout.
 */

{
   Node *print_node = front;
   bool first_term = true;

   while (print_node != NULL) {
      Term &print_term = print_node->entry;
      if (first_term) {  //  In this case, suppress printing an initial '+'.
         first_term = false;
         if (print_term.coefficient < 0) cout << "- ";
      }

      else if (print_term.coefficient < 0) cout << " - ";
      else cout << " + ";

      double r = (print_term.coefficient >= 0)
                 ? print_term.coefficient : -(print_term.coefficient);
      if (r != 1) cout << r;
      if (print_term.degree > 1) cout << " X^" << print_term.degree;
      if (print_term.degree == 1) cout << " X";
      if (r == 1 && print_term.degree == 0) cout << " 1";
      print_node = print_node->next;
   }
   if (first_term)
      cout << "0";  //  Print 0 for an empty Polynomial.
   cout << endl;
}

void Polynomial::read()
/*
Post: The Polynomial is read from cin.
 */

{
   clear();
   double coefficient;
   int last_exponent, exponent;
   bool first_term = true;

   cout << "Enter the coefficients and exponents for the polynomial, "
        << "one pair per line.  Exponents must be in descending order." << endl
        << "Enter a coefficient of 0 or an exponent of 0 to terminate." << endl;

   do {

      cout << "coefficient? " << flush;
      cin  >> coefficient;
      if (coefficient != 0.0) {

         cout << "exponent? " << flush;
         cin  >> exponent;
         if ((!first_term && exponent >= last_exponent) || exponent < 0) {
            exponent = 0;

            cout << "Bad exponent: Polynomial terminates without its last term."
                 << endl;
         }

         else {
            Term new_term(exponent, coefficient);
            append(new_term);
            first_term = false;
         }
         last_exponent = exponent;
      }
   } while (coefficient != 0.0 && exponent != 0);
}

void Polynomial::equals_sum(Polynomial p, Polynomial q)
/*
Post: The Polynomial object
is reset as the sum of the two parameters.
 */

{
   clear();
   while (!p.empty() || !q.empty()) {
      Term p_term, q_term;
      if (p.degree() > q.degree()) {
         p.serve_and_retrieve(p_term);
         append(p_term);
      }

      else if (q.degree() > p.degree()) {
         q.serve_and_retrieve(q_term);
         append(q_term);
      }

      else {
         p.serve_and_retrieve(p_term);
         q.serve_and_retrieve(q_term);
         if (p_term.coefficient + q_term.coefficient != 0) {
            Term answer_term(p_term.degree,
                             p_term.coefficient + q_term.coefficient);
            append(answer_term);
         }
      }
   }
}

void Polynomial::equals_difference(Polynomial p, Polynomial q)
{
   clear();
   Term p_term, q_term;
   while (!p.empty() || !q.empty()) {
      if (p.degree() > q.degree()) {
         p.serve_and_retrieve(p_term);
         append(p_term);
      }
      else if (q.degree() > p.degree()) {
         q.serve_and_retrieve(q_term);
         q_term.coefficient = -q_term.coefficient;
         append(q_term);
      }
      else {
         p.serve_and_retrieve(p_term);
         q.serve_and_retrieve(q_term);
         if (p_term.coefficient - q_term.coefficient != 0) {
            Term answer_term(p_term.degree, p_term.coefficient - q_term.coefficient);
            append(answer_term);
         }
      }
   }
}

void Polynomial::equals_product(Polynomial p, Polynomial q)
{
   clear();
   Term p_term, term;
   Polynomial partial_prod, old_sum, new_sum;
   while (p.serve_and_retrieve(p_term) == success) {
      partial_prod.mult_term(q, p_term);
      new_sum.equals_sum(old_sum, partial_prod);
      old_sum = new_sum;
   }
   while (new_sum.serve_and_retrieve(term) == success) append(term);
}

Error_code Polynomial::equals_quotient(Polynomial p, Polynomial q)
{
   clear();
   if (q.empty()) return (fail);    //  divide by 0
   if (p.degree() < q.degree()) return (success);
   Term p_term, q_term, term;
   Polynomial partial_prod, remainder, tail;
   p.serve_and_retrieve(p_term);
   q.retrieve(q_term);
   Term lead_term(p_term.degree - q_term.degree, p_term.coefficient / q_term.coefficient);
   append(lead_term);
   partial_prod.mult_term(q, lead_term);
   partial_prod.serve_and_retrieve(term);
   remainder.equals_difference(p, partial_prod);
   tail.equals_quotient(remainder, q);
   while (tail.serve_and_retrieve(term) == success) append(term);
   return (success);
}
