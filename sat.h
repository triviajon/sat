#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Maxmimum length of a variable in a CNFSatFormula
#define MAX_VARIABLE_LEN 256
// Maximum number of variables in a CNFSatFormula
#define MAX_VARIABLES 65536

typedef struct
{
    char name[MAX_VARIABLE_LEN]; // Variable identifier (e.g., "varA", "my_variable", ...)
} Variable;

// Literal in SAT formula
typedef struct
{
    Variable *var; // Pointer to a variable
    bool negated; // Indicates whether the literal is negated (true or false)
} Literal;

// Disjunction of the literals (a clause)
typedef struct
{
    Literal **literals; // Array of literal pointers in the disjunction
    int num_literals;  // Number of literals in the disjunction
} Disjunction;

// SAT formula
typedef struct
{
    Disjunction **disjunctions; // Array of disjunction pointers in the formula
    int num_disjunctions;      // Number of clauses in the formula
} CNFSatFormula;

/**
 * Frees all dynamically allocated memory in a CNFSatFormula.
 *
 * @param formula Pointer to the CNFSatFormula to clean up.
 */
void cleanup(CNFSatFormula *formula);

/**
 * Evaluates a CNFSatFormula given a variable mapping.
 *
 * @param formula Pointer to the CNFSatFormula to evaluate.
 * @param var_map Mapping of variable names to boolean values.
 * @return true if the formula is satisfied, false otherwise.
 */
bool eval(CNFSatFormula *formula, bool *var_map);
