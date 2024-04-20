#include "parse.h"
#include <stdio.h>

int main() {
  char *cnf_string = "(x|y|~z)+(x|~y|z)+(~x|y|z)";
  // char *cnf_string = "(~Z)";
  CNFSatFormula *cnf_sat = parse_CNF(cnf_string);
  UniqueVarArray *uniqueVars = find_unique_variables(cnf_sat);

  if (cnf_sat != NULL) {
    printf("num of disjunctions: %d\n", cnf_sat->num_disjunctions);
    printf("unique vars:\n");
    for (int i = 0; i < uniqueVars->count; i++) {
      printf("    %s", uniqueVars->vars[i]->name);
    }
    printf("\n");
  } else {
    printf("Bad parse :( \n");
  }

  cleanup_CNFSatFormula(cnf_sat);
  cleanup_UniqueVarArray(uniqueVars);

  return 0;
}