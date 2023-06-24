#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Polyterm/Polyterm.h>

#define OP_LEN 4
#define OP_MAX_CHAR_LEN 50

char OPERATIONS [OP_LEN][OP_MAX_CHAR_LEN] = {
  "print",
  "add",
  "multiply",
  "quit"
};

int str_equal (char *, char *);
void print_op ();
void add_op ();
void multiply_op ();

int main () {
  int quit = 0;
  int op_code;
  int idx;
  char * op;

  while (!quit) {
    op_code = OP_LEN - 1;
    printf ("Enter following code to perform given operation\n");

    for (idx = 0; idx < OP_LEN; idx++) {
      printf("\t- %d. %s\n", idx, OPERATIONS[idx]); 
    }

    scanf("%d", &op_code);
    if (op_code < 0 || OP_LEN <= op_code) {
      printf("invalid operation code\n");
      continue;
    }

    op = OPERATIONS[op_code];

    if (str_equal (op, "print")) {
      printf("\t\tprint\n");
      print_op ();
      continue;
    }

    if (str_equal (op, "quit")) {
      quit = 1;
      printf("\t\tquiting\n");
      continue;
    }
  }

  return 0;
}

int str_equal (char * s1, char * s2) {
  return !strcmp (s1, s2);
}


void print_op () {
  int sym_len, idx;
  double * degree, co_eff;
  char * sym, sym_str[27], ch;

  printf("enter co-efficient: ");
  scanf("%lf", &co_eff);

  printf("enter symbols: ");
  scanf("%s", sym_str);

  ch = sym_str[0];
  for (idx = 0; idx < 27; idx++) {
    ch = sym_str[idx];
    if (ch == '\0') break;

    if (ch < 'a' || ch > 'z') {
      printf("invalid sym: %s\n", sym_str);
      return;
    }
  }

  sym_len = idx;

  if (sym_len < 1) {
    printf("invalid sym_len: %s\n", sym_str);
    return;
  }

  sym = (char *) malloc (sym_len * sizeof(char));
  memcpy(sym, sym_str, sym_len);

  degree = (double *) malloc (sym_len * sizeof(double));
  for (idx = 0; idx < sym_len; idx++) {
    printf("enter degree for symbol '%c': ", sym [idx]);  
    scanf("%lf", &degree [idx]);
  }

  Polyterm * polyterm = polyterm_new (
      co_eff,
      degree,
      sym,
      sym_len
  );

  polyterm_print(polyterm);
}
