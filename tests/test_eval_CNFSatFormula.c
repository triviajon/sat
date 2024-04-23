#include "test_eval_CNFSatFormula.h"

void test_eval_CNFSatFormula() {

  /**
   * Testing strategy for eval_CNFSatFormula:
   *  cover all subdomains of the following partitions minimally
   *
   *  bool eval_CNFSatFormula(CNFSatFormula *formula, VarMap *var_map, bool
   * *result)
   *
   *  partition on result (value): result is true, result is false
   *  partition on formula (AND): contains AND, does not contain AND
   *  partition on formula (OR): contains OR, does not contain OR
   *  partition on formula (NOT): contains NOT, does not contain NOT
   *  partition on formula (clauses): #clauses = 1, #clauses = 2, #clauses > 2
   *  partition on formula (satisifiability): formula is satisfiable, formula is
   * not satisfiable
   */

  {
    printf("  Test (covers result is true, +AND, -OR, -NOT, #clauses = 2, "
           "formula is satisfiable):\n");
    char *cnf_string1 = "(x)+(y)";
    CNFSatFormula *cnf_sat1 = parse_CNF(cnf_string1);
    UniqueVarArray *uniqueVars1 = find_unique_variables(cnf_sat1);
    VarMap *var_map1 = init_VarMap();
    Variable var_x = {"x"};
    Variable var_y = {"y"};

    insert_VarMap(var_map1, &var_x, 1);
    insert_VarMap(var_map1, &var_y, 1);

    bool result1;
    bool successful_eval1 = eval_CNFSatFormula(cnf_sat1, var_map1, &result1);
    assert(successful_eval1);
    assert(result1);
    printf("    Test passed\n");
    cleanup_CNFSatFormula(cnf_sat1);
    cleanup_UniqueVarArray(uniqueVars1);
    cleanup_VarMap(var_map1);
  }

  {
    printf("  Test (covers result is true, -AND, +OR, -NOT, #clauses = 1, "
           "formula is satisfiable):\n");
    char *cnf_string1 = "(x|y)";
    CNFSatFormula *cnf_sat1 = parse_CNF(cnf_string1);
    UniqueVarArray *uniqueVars1 = find_unique_variables(cnf_sat1);
    VarMap *var_map1 = init_VarMap();
    Variable var_x = {"x"};
    Variable var_y = {"y"};

    insert_VarMap(var_map1, &var_x, 0);
    insert_VarMap(var_map1, &var_y, 1);

    bool result1;
    bool successful_eval1 = eval_CNFSatFormula(cnf_sat1, var_map1, &result1);
    assert(successful_eval1);
    assert(result1);
    printf("    Test passed\n");
    cleanup_CNFSatFormula(cnf_sat1);
    cleanup_UniqueVarArray(uniqueVars1);
    cleanup_VarMap(var_map1);
  }

  {
    printf("  Test (covers result is false, -AND, -OR, +NOT, #clauses = 1, "
           "formula is satisfiable):\n");
    char *cnf_string1 = "(~longVariableName)";
    CNFSatFormula *cnf_sat1 = parse_CNF(cnf_string1);
    UniqueVarArray *uniqueVars1 = find_unique_variables(cnf_sat1);
    VarMap *var_map1 = init_VarMap();
    Variable var_longVariableName = {"longVariableName"};

    insert_VarMap(var_map1, &var_longVariableName, 1);

    bool result1;
    bool successful_eval1 = eval_CNFSatFormula(cnf_sat1, var_map1, &result1);
    assert(successful_eval1);
    assert(!result1);
    printf("    Test passed\n");
    cleanup_CNFSatFormula(cnf_sat1);
    cleanup_UniqueVarArray(uniqueVars1);
    cleanup_VarMap(var_map1);
  }

  {
    printf("  Test (covers result is false, +AND, +OR, +NOT, #clauses > 2, "
           "formula is not satisfiable):\n");
    char *cnf_string1 = "(x|y) + (~x|~y) + (x|~y) + (~x|y)";
    CNFSatFormula *cnf_sat1 = parse_CNF(cnf_string1);
    UniqueVarArray *uniqueVars1 = find_unique_variables(cnf_sat1);
    VarMap *var_map1 = init_VarMap();
    Variable var_x = {"x"};
    Variable var_y = {"y"};

    insert_VarMap(var_map1, &var_x, 0);
    insert_VarMap(var_map1, &var_y, 1);

    bool result1;
    bool successful_eval1 = eval_CNFSatFormula(cnf_sat1, var_map1, &result1);
    assert(successful_eval1);
    assert(!result1);
    printf("    Test passed\n");
    cleanup_CNFSatFormula(cnf_sat1);
    cleanup_UniqueVarArray(uniqueVars1);
    cleanup_VarMap(var_map1);
  }

  {
    printf("  Test (extra #1)\n");
    char *cnf_string1 = "(x|y|~z)+(x|~y|z)+(~x|y|z)";
    CNFSatFormula *cnf_sat1 = parse_CNF(cnf_string1);
    UniqueVarArray *uniqueVars1 = find_unique_variables(cnf_sat1);
    VarMap *var_map1 = init_VarMap();
    Variable var_x = {"x"};
    Variable var_y = {"y"};
    Variable var_z = {"z"};

    insert_VarMap(var_map1, &var_x, 0);
    insert_VarMap(var_map1, &var_y, 0);
    insert_VarMap(var_map1, &var_z, 0);

    bool result1;
    bool successful_eval1 = eval_CNFSatFormula(cnf_sat1, var_map1, &result1);
    assert(successful_eval1);
    assert(result1);
    printf("    Test passed\n");
    cleanup_CNFSatFormula(cnf_sat1);
    cleanup_UniqueVarArray(uniqueVars1);
    cleanup_VarMap(var_map1);
  }

  printf("All test cases passed successfully!\n");
}