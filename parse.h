#include "sat.h"

enum Symbol {
    GrammarCNF, GrammarDisjunction, GrammarLiteral
};

/**
 * Check if a given character is a white-space character.
 *
 * @param c The character to check.
 * @return true if the character is a white-space character (' ', '\t', '\n'), false otherwise.
 */
bool isWhiteSpace(char c);

/**
 * Check if a given character is a valid character for a variable name.
 *
 * @param c The character to check.
 * @return true if the character is a valid variable character (uppercase letter, lowercase letter, or digit), false otherwise.
 */
bool isVariableChar(char c);

/**
 * Parse a variable name from a given CNF (Conjunctive Normal Form) string starting at a given index.
 *
 * @param cnf_string The CNF string to parse.
 * @param index A pointer to the index in the CNF string from which to start parsing.
 * @return Variable structure containing the parsed variable name. To avoid memory leaks, the returned pointer
 * must be deallocated with free() or realloc().
 */
Variable *parseVariable(char *cnf_string, int *index);

/**
 * Parse a literal from a given CNF string starting at a given index.
 *
 * @param cnf_string The CNF string to parse.
 * @param index A pointer to the index in the CNF string from which to start parsing.
 * @return Literal structure containing the parsed literal. To avoid memory leaks, the returned pointer
 * must be deallocated with free() or realloc().
 */
Literal *parseLiteral(char *cnf_string, int *index);

Disjunction* parseDisjunction(char *cnf_string, int *index);
CNFSatFormula parseCNF(char *cnf_string);