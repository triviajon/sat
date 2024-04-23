#include "test_solve_CNFSatFormula.h"

void test_solve_CNFSatFormula() {

    /**
     * Testing strategy for solve_CNFSatFormula:
     *  cover all subdomains of the following partitions minimally
     * 
     */


    {
        printf("  Test (solve_CNFSatFormula)\n");
        char *cnf_string1 = "(x|y|~z)+(x|~y|z)+(~x|y|z)";
        CNFSatFormula *cnf_sat1 = parse_CNF(cnf_string1);
        VarMap *var_map1 = init_VarMap();
        Variable var_x = { "x" };
        Variable var_y = { "y" };
        Variable var_z = { "z" };

        bool result;

        bool is_satisfiable = solve_CNFSatFormula(cnf_sat1, var_map1);
        assert(is_satisfiable);

        // Verify the satisfying assignment
        bool value_x, value_y, value_z;
        get_VarMap(var_map1, &var_x, &value_x);
        get_VarMap(var_map1, &var_y, &value_y);
        get_VarMap(var_map1, &var_z, &value_z);

        // The satisfying assignment should satisfy the CNF formula
        CNFSatFormula *formula_check = parse_CNF(cnf_string1);
        insert_VarMap(var_map1, &var_x, value_x);
        insert_VarMap(var_map1, &var_y, value_y);
        insert_VarMap(var_map1, &var_z, value_z);

        bool successful_eval = eval_CNFSatFormula(formula_check, var_map1, &result);
        assert(successful_eval);
        assert(result);

        printf("    Test passed\n");

        cleanup_CNFSatFormula(cnf_sat1);
        cleanup_VarMap(var_map1);
        cleanup_CNFSatFormula(formula_check);
    }


    printf("All test cases passed successfully!\n");
}