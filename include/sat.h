#include "var_map.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Frees all dynamically allocated memory in a CNFSatFormula.
 *
 * @param formula Pointer to the CNFSatFormula to clean up.
 */
void cleanup_CNFSatFormula(CNFSatFormula *formula);

/**
 * Evaluates a CNFSatFormula given a variable mapping.
 *
 * @param formula Pointer to the CNFSatFormula to evaluate.
 * @param var_map Pointer to the VarMap containing variable boolean values.
 * @param result Point to where result we will be contained. true if the formula
 * is satisfied, false otherwise.
 * @return true if the CNFSatFormula was successfully evaluated, false
 * otherwise.
 */
bool eval_CNFSatFormula(CNFSatFormula *formula, VarMap *var_map, bool *result);

/**
 * Finds all unique variables in a CNFSatFormula.
 *
 * @param formula Pointer to the CNFSatFormula to analyze.
 * @return Pointer to a UniqueVarArray containing unique variables. To avoid
 * memory leaks, the returned pointer must be deallocated with free() or
 * realloc().
 */
UniqueVarArray *find_unique_variables(CNFSatFormula *formula);

/**
 * Frees all dynamically allocated memory in a UniqueVarArray.
 *
 * @param formula Pointer to the UniqueVarArray to clean up.
 */
void cleanup_UniqueVarArray(UniqueVarArray *array);
