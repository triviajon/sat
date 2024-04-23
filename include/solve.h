#ifndef SOLVE_H
#define SOLVE_H

#include <stdbool.h>
#include "var_map.h"
#include "cnf_sat_formula.h"
#include "sat.h"

#define BASE_CASE_SIZE -1

/**
 * Checks if a CNFSatFormula is satisfiable.
 *
 * @param formula Pointer to the CNFSatFormula to check.
 * @return true if the CNFSatFormula is satisfiable, false otherwise.
 */
bool is_satisfiable(CNFSatFormula *formula);

/**
 * Finds a satisfying assignment for a CNFSatFormula.
 *
 * @param formula Pointer to the CNFSatFormula to find an assignment for.
 * @param var_map Pointer to the VarMap where the satisfying assignment will be stored. Must be empty. 
 * @return true if a satisfying assignment was found, false otherwise.
 */
bool solve_CNFSatFormula(CNFSatFormula *formula, VarMap *var_map);

#endif /* SOLVE_H */
