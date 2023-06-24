#include <stdlib.h>
#include <stdio.h>

#include <Polyterm/Polyterm.h>

#define SYM_LEN1 2

double degree1 [SYM_LEN1] = { 1.34, 2.12 };
Polyterm poly1 = {
  .co_eff = 2.0,
  .degree = degree1,
  .sym = "xy",
  .sym_len = SYM_LEN1
};

double degree2 [2] = { 2.12, 1.34 };
Polyterm poly2 = {
  .co_eff = 2.0,
  .degree = degree2,
  .sym = "yx",
  .sym_len = 2,
};

const int polyterms_len = 2;
Polyterm * polyterms [] = {
  &poly1,
  &poly2
};


void verify_polyterm_print ();
void verify_polyterm_add ();
void verify_polyterm_multiply ();


int main () {
  verify_polyterm_print ();
  verify_polyterm_add ();
  verify_polyterm_multiply ();

  return 0;
}

void verify_polyterm_print () {
  printf("polyterm_print -> ");
  polyterm_print (&poly1);
}


void verify_polyterm_add () {
  Polyterm * poly = polyterm_add (polyterms, polyterms_len);
  printf("polyterm_print -> ");
  polyterm_print (poly);
}

void verify_polyterm_multiply () {
  Polyterm * poly = polyterm_multiply (polyterms, polyterms_len);
  printf ("polyterm_multiply -> ");
  polyterm_print (poly);
}
