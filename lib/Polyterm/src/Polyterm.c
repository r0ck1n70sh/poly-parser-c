#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <Polyterm/Polyterm.h>
const int TOTAL_CHAR_LEN = 26;

static void polyterm_sym_clean (Polyterm *);
static int polyterm_sym_equal (Polyterm *, Polyterm *);
static int polyterms_is_similar (Polyterm * polyterms [], int);

Polyterm * polyterm_new (
    double co_eff,
    double degree [],
    char sym [],
    int sym_len) {

  Polyterm * polyterm_ptr = malloc (sizeof (Polyterm));

  polyterm_ptr->co_eff = co_eff;
  polyterm_ptr->degree = degree;
  polyterm_ptr->sym = sym;
  polyterm_ptr->sym_len = sym_len;

  return polyterm_ptr;
}

void polyterm_print (Polyterm * poly) {
  printf("%lf", poly->co_eff);

  int i;
  for (i = 0; i < poly->sym_len; i++) {
    printf("(%c^%lf)", poly->sym[i], poly->degree[i]);
  }

  printf("\n");
}

Polyterm * polyterm_add (
    Polyterm * polyterms [],
    int len) {

  if (!polyterms_is_similar (polyterms, len)) {
    printf("invalid polyterms for polyterm_add\n");
    return NULL;
  }

  printf("valid polyterms for polyterm_add\n");

  double final_co_eff = 0.0;

  int i;
  for (i = 0; i < len; i++) {
    final_co_eff += polyterms [i]->co_eff;
  }

  return polyterm_new (
      final_co_eff,
      polyterms [0]->degree,
      polyterms [0]->sym,
      polyterms [0]->sym_len);
}

Polyterm * polyterm_multiply (
    Polyterm * polyterms [],
    int len) {

  double final_co_eff = 1.0;
  
  double * final_degree_array = (double *) malloc(TOTAL_CHAR_LEN * sizeof(double));
  memset(final_degree_array, 0, TOTAL_CHAR_LEN);

  int i = 0, idx = 0, sym_len, ch;
  double * degree;
  char * sym;
  int final_sym_len = 0;

  for (i = 0; i < len; i++) {
    final_co_eff *= polyterms [i]->co_eff;

    sym_len = polyterms [i]->sym_len;
    sym = polyterms [i]->sym;
    degree = polyterms [i]->degree;

    for (idx = 0; idx < sym_len; idx++) {
      ch = sym [idx] - 'a';

      if (final_degree_array [ch] == 0) final_sym_len += 1;
      final_degree_array [ch] += degree [idx];
    }
  }

  char * final_sym = (char *) malloc (final_sym_len * sizeof(char));
  double * final_degree = (double *) malloc (final_sym_len * sizeof(double));

  for (i = 0, idx = 0; i < TOTAL_CHAR_LEN; i++) {
    if (final_degree_array [i] == 0) continue;

    ch = i + 'a';
    final_sym [idx] = ch;
    final_degree [idx] = final_degree_array [i];
    idx++;
  }

  Polyterm * final_polyterm = polyterm_new (
      final_co_eff,
      final_degree,
      final_sym,
      final_sym_len
  );

  return final_polyterm;
}

static int polyterms_is_similar (
    Polyterm * polyterms [],
    int len) {

  int i;
  Polyterm * pre;
  Polyterm * curr;

  for (i = 1; i < len; i++) {
    pre = polyterms [i - 1];
    curr = polyterms [i];

    if (!polyterm_sym_equal (pre, curr)) {
      return 0;
    }
  }

  return 1;
}


static int polyterm_sym_equal (
    Polyterm * poly1,
    Polyterm * poly2) {

  if (poly1->sym_len != poly2->sym_len) {
    return 0;
  }

  polyterm_sym_clean (poly1);
  polyterm_sym_clean (poly2);

  int i = 0, len = poly1->sym_len;
  for (i = 0; i < len; i++) {
    if (poly1->sym [i] != poly2->sym [i] ||
        poly1->degree [i] != poly2->degree [i]) {
      return 0;
    }
  }

  return 1;
}

static void polyterm_sym_clean (Polyterm * poly) {
  double * chars = (double *) malloc (TOTAL_CHAR_LEN * sizeof(double));
  memset (chars, 0, TOTAL_CHAR_LEN * sizeof(double)); 

  int i, curr;
  for (i = 0; i < poly->sym_len; i++) {
    curr = poly->sym[i];
    chars [curr - 'a'] += poly->degree[i];
  }

  int new_sym_len = 0;
  for (i = 0; i < TOTAL_CHAR_LEN; i++) {
    new_sym_len += (chars [i] != 0);
  }

  char * new_sym = (char *) malloc (new_sym_len * sizeof(char));
  double * new_degree = (double *) malloc (new_sym_len & sizeof(double));

  int idx = 0;
  for (i = 0; i < TOTAL_CHAR_LEN && idx < new_sym_len; i++) {
    if (chars [i] == 0) continue;
    new_sym [idx] = i + 'a';
    new_degree [idx] = chars [i]; 
    idx++;
  }

  poly->sym_len = new_sym_len;
  poly->sym = new_sym;
  poly->degree = new_degree;

  free(chars);
}
