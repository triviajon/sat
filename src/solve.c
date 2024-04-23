#include "solve.h"

bool is_satisfiable(CNFSatFormula *formula) {
    VarMap *var_map = init_VarMap();
    bool satisfiable = solve_CNFSatFormula(formula, var_map);
    cleanup_VarMap(var_map);
    return satisfiable;
}

/**
 * Finds a satisfying assignment for a CNFSatFormula.
 *
 * @param formula Pointer to the CNFSatFormula to find an assignment for.
 * @param var_map Pointer to the VarMap where the satisfying assignment will be stored. 
 * @return true if a satisfying assignment was found, false otherwise.
 */
bool solve_CNFSatFormula(CNFSatFormula *formula, VarMap *var_map) {
    UniqueVarArray *unique_vars = find_unique_variables(formula);
    int num_variables = unique_vars->count;
    bool *assignment = malloc(num_variables * sizeof(bool));


    cleanup_UniqueVarArray(unique_vars);
    return false;
}

