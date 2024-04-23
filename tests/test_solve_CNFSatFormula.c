#include "test_solve_CNFSatFormula.h"

void _test_solve_CNFSatFormula(char *cnf_string, bool expected) {
  CNFSatFormula *cnf_sat = parse_CNF(cnf_string);
  UniqueVarArray *unique_vars = find_unique_variables(cnf_sat);

  VarMap *var_map = init_VarMap();
  bool is_satisfied = solve_CNFSatFormula(cnf_sat, var_map);

  if (expected) {
    assert(is_satisfied);
    char buffer[256];
    bool success = print_VarMap(var_map, buffer, sizeof(buffer));
    if (success) {
      printf("    VarMap contents: %s\n", buffer);
    }

    bool result;
    bool successful_eval = eval_CNFSatFormula(cnf_sat, var_map, &result);
    assert(successful_eval);
    assert(result);
  } else {
    assert(!is_satisfied);
  }

  printf("    Test passed\n");
  cleanup_CNFSatFormula(cnf_sat);
  cleanup_UniqueVarArray(unique_vars);
  cleanup_VarMap(var_map);
}

void test_solve_CNFSatFormula() {

  /**
   * Testing strategy for solve_CNFSatFormula:
   *  cover all subdomains of the following partitions minimally
   *
   *  bool solve_CNFSatFormula(CNFSatFormula *formula, VarMap *var_map)
   *
   *  partition on formula (AND): contains AND, does not contain AND
   *  partition on formula (OR): contains OR, does not contain OR
   *  partition on formula (NOT): contains NOT, does not contain NOT
   *  partition on formula (clauses): #clauses = 1, #clauses = 2, #clauses > 2
   *  partition on formula (satisfiability): formula is satisfiable, formula is
   * not satisfiable
   */

  {
    printf("  Test (covers +AND, -OR, -NOT, #clauses = 2, "
           "formula is satisfiable):\n");
    char *cnf_string1 = "(x)+(y)";
    _test_solve_CNFSatFormula(cnf_string1, true);
  }

  {
    printf("  Test (covers -AND, +OR, -NOT, #clauses = 1, "
           "formula is satisfiable):\n");
    char *cnf_string1 = "(x|y)";
    _test_solve_CNFSatFormula(cnf_string1, true);
  }

  {
    printf("  Test (covers -AND, -OR, +NOT, #clauses = 1, "
           "formula is satisfiable):\n");
    char *cnf_string1 = "(~longVariableName)";
    _test_solve_CNFSatFormula(cnf_string1, true);
  }

  {
    printf("  Test (covers +AND, +OR, +NOT, #clauses > 2, "
           "formula is not satisfiable):\n");
    char *cnf_string1 = "(x|y) + (~x|~y) + (x|~y) + (~x|y)";
    _test_solve_CNFSatFormula(cnf_string1, false);
  }

  {
    printf("  Test (extra #1)\n");
    char *cnf_string1 = "(x|y|~z)+(x|~y|z)+(~x|y|z)";
    _test_solve_CNFSatFormula(cnf_string1, true);
  }

  printf("All test cases passed successfully!\n");
}