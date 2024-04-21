#include "test_eval_CNFSatFormula.h"

void test_eval_CNFSatFormula() {

    // Test Case 1: CNF formula is satisfied
    printf("Test Case 1: CNF formula is satisfied\n");
    char *cnf_string1 = "(x|y|~z)+(x|~y|z)+(~x|y|z)";
    CNFSatFormula *cnf_sat1 = parse_CNF(cnf_string1);
    UniqueVarArray *uniqueVars1 = find_unique_variables(cnf_sat1);
    VarMap *var_map1 = init_VarMap();
    Variable var_x = { "x" };
    Variable var_y = { "y" };
    Variable var_z = { "z" };

    insert_VarMap(var_map1, &var_x, 0);
    insert_VarMap(var_map1, &var_y, 0);
    insert_VarMap(var_map1, &var_z, 0);

    bool result1;
    bool successful_eval1 = eval_CNFSatFormula(cnf_sat1, var_map1, &result1);
    assert(successful_eval1);
    assert(result1);
    printf("Test Case 1 passed\n");
    cleanup_CNFSatFormula(cnf_sat1);
    cleanup_UniqueVarArray(uniqueVars1);
    cleanup_VarMap(var_map1);

    printf("All test cases passed successfully!\n");
}