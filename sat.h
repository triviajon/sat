#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VARIABLE_LEN 256

typedef struct {
    char name[MAX_VARIABLE_LEN];  // Variable identifier (e.g., "varA", "my_variable", ...)
} Variable;

// Literal in SAT formula
typedef struct {
    Variable var;
    bool negated;    // Indicates whether the literal is negated (true or false)
} Literal;

// Disjunction of the literals (a clause)
typedef struct {
    Literal* literals;   // Array of literals in the disjunction
    int num_literals;    // Number of literals in the disjunction
} Disjunction;

// SAT formula
typedef struct {
    Disjunction* disjunctions;     // Array of disjunctions in the formula
    int num_disjunctions;     // Number of clauses in the formula
} CNFSatFormula;
