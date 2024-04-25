#include "sat.h"

void free_variable(Variable *var) { free(var); }

void free_literal(Literal *lit) {
  free_variable(lit->var);
  free(lit);
}

void free_disjunction(Disjunction *disj) {
  for (int i = 0; i < disj->num_literals; i++) {
    free_literal(disj->literals[i]);
  }
  free(disj->literals);
  free(disj);
}

void cleanup_CNFSatFormula(CNFSatFormula *formula) {
  if (formula == NULL) {
    return;
  }

  for (int i = 0; i < formula->num_disjunctions; i++) {
    free_disjunction(formula->disjunctions[i]);
  }
  free(formula->disjunctions);
  free(formula);
}

/**
 * Helper function to check if a Variable is already in the UniqueVarArray.
 *
 * @param var Pointer to the Variable to check.
 * @param array Pointer to the UniqueVarArray.
 * @return true if the Variable is already in the array, false otherwise.
 */
bool is_variable_in_array(Variable *var, UniqueVarArray *array) {
  for (int i = 0; i < array->count; i++) {
    if (strcmp(var->name, array->vars[i]->name) == 0) {
      return true;
    }
  }
  return false;
}

UniqueVarArray *find_unique_variables(CNFSatFormula *formula) {
  UniqueVarArray *unique_vars =
      (UniqueVarArray *)malloc(sizeof(UniqueVarArray));
  if (unique_vars == NULL) {
    return NULL;
  }

  unique_vars->vars = (Variable **)malloc(MAX_VARIABLES * sizeof(Variable *));
  if (unique_vars->vars == NULL) {
    free(unique_vars);
    return NULL;
  }

  unique_vars->count = 0;

  for (int i = 0; i < formula->num_disjunctions; i++) {
    for (int j = 0; j < formula->disjunctions[i]->num_literals; j++) {
      Variable *var = formula->disjunctions[i]->literals[j]->var;

      if (!is_variable_in_array(var, unique_vars)) {
        unique_vars->vars[unique_vars->count] = var;
        unique_vars->count++;
      }
    }
  }

  // Reallocate memory to fit only the number of unique variables found
  unique_vars->vars = (Variable **)realloc(
      unique_vars->vars, unique_vars->count * sizeof(Variable *));
  if (unique_vars->vars == NULL && unique_vars->count > 0) {
    free(unique_vars);
    return NULL;
  }

  return unique_vars;
}

void cleanup_UniqueVarArray(UniqueVarArray *array) {
  if (array != NULL) {
    free(array->vars);
    free(array);
  }
}

bool eval_CNFSatFormula(CNFSatFormula *formula, VarMap *var_map, bool *result) {
  // Make sure all variables in formula exist in the var_map
  UniqueVarArray *uniqueVarArr = find_unique_variables(formula);
  for (int i = 0; i < uniqueVarArr->count; i++) {
    bool var_val;
    if (!get_VarMap(var_map, uniqueVarArr->vars[i], &var_val)) {
      printf("Could not find variable %s\n", uniqueVarArr->vars[i]->name);
      cleanup_UniqueVarArray(uniqueVarArr);
      return false;
    }
  }

  for (int i = 0; i < formula->num_disjunctions; i++) {
    Disjunction *disj = formula->disjunctions[i];
    bool disjunction_result = false;
    for (int j = 0; j < disj->num_literals; j++) {
      Literal *lit = disj->literals[j];
      Variable *var = lit->var;
      bool var_val;
      get_VarMap(var_map, var, &var_val);
      disjunction_result |= (var_val != lit->negated);
      if (disjunction_result) { break; }
    }

    if (!disjunction_result) {
      // Exit early if any of the disjunctions are false
      *result = false;
      cleanup_UniqueVarArray(uniqueVarArr);
      return true;
    }
  }

  *result = true;  
  cleanup_UniqueVarArray(uniqueVarArr);
  return true;
}
