typedef struct {
  double co_eff;
  double * degree;
  char * sym;
  int sym_len;
} Polyterm;


Polyterm * polyterm_new (
    double co_eff,
    double degree [],
    char sym [],
    int sym_len);

void polyterm_print (Polyterm * poly);

Polyterm * polyterm_add (
    Polyterm * polyterms [],
    int len);

Polyterm * polyterm_multiply (
    Polyterm * polyterms [],
    int len);
