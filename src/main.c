#include "parse.h"
#include <stdio.h>
#include <time.h>

int main() {
  srand(time(NULL));
  char *cnf_string = "(x|y|~z)+(x|~y|z)+(~x|y|z)";
  // char *cnf_string = "(~Z)";
  CNFSatFormula *cnf_sat = parse_CNF(cnf_string);
  UniqueVarArray *uniqueVars = find_unique_variables(cnf_sat);
  VarMap *var_map = init_VarMap();
  for (int i = 0; i < uniqueVars->count; i++) {
    Variable *var = uniqueVars->vars[i];
    insert_VarMap(var_map, var, rand() & 1);
  }

  if (cnf_sat != NULL) {
    printf("num of disjunctions: %d\n", cnf_sat->num_disjunctions);
    printf("unique vars:\n");
    for (int i = 0; i < uniqueVars->count; i++) {
      Variable *var = uniqueVars->vars[i];
      bool value;
      get_VarMap(var_map, var, &value);
      printf("    %s=%d", var->name, value);
    }
    printf("\n");
    bool result;
    bool successful_eval = eval_CNFSatFormula(cnf_sat, var_map, &result);
    if (successful_eval) {
      printf("Evaluation result: %d\n", result);
    } else {
      printf("Unable to evaluate CNF :(\n");
    }
  } else {
    printf("Bad parse :( \n");
  }

  cleanup_CNFSatFormula(cnf_sat);
  cleanup_UniqueVarArray(uniqueVars);
  cleanup_VarMap(var_map);

  return 0;
}