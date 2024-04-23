#include "solve.h"

bool is_satisfiable(CNFSatFormula *formula) {
    VarMap *var_map = init_VarMap();
    bool satisfiable = solve_CNFSatFormula(formula, var_map);
    cleanup_VarMap(var_map);
    return satisfiable;
}

bool _solve_CNFSatFormula(CNFSatFormula *formula, UniqueVarArray *unique_vars, VarMap *int_var_map, int var_num) {
    int num_variables = unique_vars->count;

    if (var_num == num_variables) {
        // we have a full var_map
        bool result;
        bool success = eval_CNFSatFormula(formula, int_var_map, &result);
        if (success && result) {
            return true;
        }
        return false;
    } else if (false && (num_variables - var_num < BASE_CASE_SIZE)) {
        // disabled for now
    } else {
        insert_VarMap(int_var_map, unique_vars->vars[var_num], false);
        if (_solve_CNFSatFormula(formula, unique_vars, int_var_map, var_num + 1)) {
            return true;
        }

        insert_VarMap(int_var_map, unique_vars->vars[var_num], true);
        return _solve_CNFSatFormula(formula, unique_vars, int_var_map, var_num + 1);
    }
}

/**
 * Finds a satisfying assignment for a CNFSatFormula.
 *
 * @param formula Pointer to the CNFSatFormula to find an assignment for.
 * @param var_map Pointer to the VarMap where the satisfying assignment will be stored. 
 * @return true if a satisfying assignment was found, false otherwise.
 */
bool solve_CNFSatFormula(CNFSatFormula *formula, VarMap *var_map) {
    // This is a the root call of a solve, and thus should have an empty var_map
    assert(var_map->size == 0);

    UniqueVarArray *unique_vars = find_unique_variables(formula);

    bool solved = _solve_CNFSatFormula(formula, unique_vars, var_map, 0);

    cleanup_UniqueVarArray(unique_vars);
    return solved;
}