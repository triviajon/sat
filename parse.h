#include "sat.h"

#define SPACE ' '
#define LEFT_PAREN '('
#define RIGHT_PAREN ')'
#define NOT '~'
#define OR '|'

enum Symbol { GrammarCNF, GrammarDisjunction, GrammarLiteral };

/**
 * Check if a given character is a white-space character.
 *
 * @param c The character to check.
 * @return true if the character is a white-space character (' ', '\t', '\n'),
 * false otherwise.
 */
bool is_whitespace(const char c);

/**
 * Check if a given character is a valid character for a variable name.
 *
 * @param c The character to check.
 * @return true if the character is a valid variable character (uppercase
 * letter, lowercase letter, or digit), false otherwise.
 */
bool is_variable_char(const char c);

/**
 * Parse a variable name from a given CNF (Conjunctive Normal Form) string
 * starting at a given index.
 *
 * @param cnf_string The CNF string to parse.
 * @param index A pointer to the index in the CNF string from which to start
 * parsing.
 * @return Variable structure containing the parsed variable name. To avoid
 * memory leaks, the returned pointer must be deallocated with free() or
 * realloc().
 */
Variable *parse_variable(char *cnf_string, int *index);

/**
 * Parse a literal from a given CNF string starting at a given index.
 *
 * @param cnf_string The CNF string to parse.
 * @param index A pointer to the index in the CNF string from which to start
 * parsing.
 * @return Literal structure containing the parsed literal. To avoid memory
 * leaks, the returned pointer must be deallocated with free() or realloc().
 */
Literal *parse_literal(char *cnf_string, int *index);

/**
 * Parses a disjunction from a CNF string.
 *
 * @param cnf_string The CNF string to parse.
 * @param index Pointer to the current index in the string.
 * @return A pointer to the parsed Disjunction. To avoid memory leaks, the
 * returned pointer must be deallocated with free() or realloc().
 */
Disjunction *parse_disjunction(char *cnf_string, int *index);

/**
 * Parses a CNF SAT formula from a CNF string.
 *
 * @param cnf_string The CNF string to parse.
 * @return A pointer to the parsed CNFSatFormula. To avoid memory leaks, the
 * returned pointer must be deallocated with free() or realloc().
 */
CNFSatFormula *parse_CNF(char *cnf_string);