#include "sat.h"

void freeVariable(Variable *var) {
    free(var);
}

void freeLiteral(Literal *lit) {
    freeVariable(lit->var);
    free(lit);
}

void freeDisjunction(Disjunction *disj) {
    for (int i = 0; i < disj->num_literals; i++) {
        freeLiteral(disj->literals[i]);
    }
    free(disj->literals);
    free(disj);
}

/**
 * Frees all dynamically allocated memory in a CNFSatFormula.
 *
 * @param formula Pointer to the CNFSatFormula to clean up.
 */
void cleanup(CNFSatFormula *formula) {
    if (formula == NULL) {
        return;
    }

    for (int i = 0; i < formula->num_disjunctions; i++) {
        freeDisjunction(formula->disjunctions[i]);
    }
    free(formula->disjunctions);
    free(formula);
}

/**
 * Evaluates a CNFSatFormula given a variable mapping.
 *
 * @param formula Pointer to the CNFSatFormula to evaluate.
 * @param var_map Mapping of variable names to boolean values.
 * @return true if the formula is satisfied, false otherwise.
 */
bool eval(CNFSatFormula *formula, bool *var_map);