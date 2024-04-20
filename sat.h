#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "var_map.h"

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
 * @return true if the formula is satisfied, false otherwise.
 */
bool eval(CNFSatFormula *formula, VarMap *var_map);

/**
 * Finds all unique variables in a CNFSatFormula.
 *
 * @param formula Pointer to the CNFSatFormula to analyze.
 * @return Pointer to a UniqueVarArray containing unique variables. To avoid memory leaks, the returned pointer
 * must be deallocated with free() or realloc().
 */
UniqueVarArray* find_unique_variables(CNFSatFormula *formula);

/**
 * Frees all dynamically allocated memory in a UniqueVarArray.
 *
 * @param formula Pointer to the UniqueVarArray to clean up.
 */
void cleanup_UniqueVarArray(UniqueVarArray *array);
