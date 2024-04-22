#include "parse.h"

bool is_whitespace(const char c) { return c == SPACE || c == '\t' || c == '\n'; }

bool is_variable_char(const char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
         (c >= '0' && c <= '9');
};

int skip_whitespace(char *cnf_string, int *index) {
  int skipped = 0;
  while (is_whitespace(cnf_string[*index])) {
    skipped++; (*index)++;
  }
  return skipped;
}

Variable *parse_variable(char *cnf_string, int *index) {
  char var_name[MAX_VARIABLE_LEN];
  int length = 0;

  while (is_variable_char(cnf_string[*index])) {
    var_name[length] = cnf_string[*index];
    (*index)++;
    length++;
  }

  var_name[length] = '\0';

  Variable *var = (Variable *)malloc(sizeof(Variable));
  if (var == NULL) {
    return NULL;
  }
  strcpy((*var).name, var_name);
  return var;
}

Literal *parse_literal(char *cnf_string, int *index) {
  bool negated = false;
  if (cnf_string[*index] == NOT) {
    negated = true;
    (*index)++;
  }

  while (cnf_string[*index] == SPACE) {
    (*index)++;
  }

  Literal *lit = (Literal *)malloc(sizeof(Literal));
  Variable *var = parse_variable(cnf_string, index);
  if (var == NULL) {
    return NULL;
  }
  lit->var = var;
  lit->negated = negated;
  return lit;
}

Disjunction *parse_disjunction(char *cnf_string, int *index) {
  int num_literals = 0;
  Literal **literals = NULL;

  while (true) {
    Literal *lit = parse_literal(cnf_string, index);
    if (lit == NULL) {
      return NULL;
    }
    literals =
        (Literal **)realloc(literals, (num_literals + 1) * sizeof(Literal *));
    literals[num_literals] = lit;
    num_literals++;

    skip_whitespace(cnf_string, index);

    if (cnf_string[*index] != OR) {
      break;
    }

    (*index)++;
  }

  skip_whitespace(cnf_string, index);

  if (cnf_string[*index] != RIGHT_PAREN) {
    return NULL;
  }

  Disjunction *disj = (Disjunction *)malloc(sizeof(Disjunction));
  if (disj == NULL) {
    return NULL;
  }
  disj->literals = literals;
  disj->num_literals = num_literals;

  return disj;
}

CNFSatFormula *parse_CNF(char *cnf_string) {
  int index = 0;

  int num_disjunctions = 0;
  Disjunction **disjunctions = NULL;

  while (true) {
    if (cnf_string[index] == LEFT_PAREN) {
      index++;
    } else {
      printf("Failed parsing string at offset %d. Saw %c instead of %c\n",
             index, cnf_string[index], LEFT_PAREN);
      return NULL;
    }

    Disjunction *disj = parse_disjunction(cnf_string, &index);
    if (disj == NULL) {
      return NULL;
    }

    disjunctions = (Disjunction **)realloc(
        disjunctions, (num_disjunctions + 1) * sizeof(Disjunction *));
    disjunctions[num_disjunctions] = disj;
    num_disjunctions++;

    skip_whitespace(cnf_string, &index);

    if (cnf_string[index] == RIGHT_PAREN) {
      index++;
    } else {
      printf("Failed parsing string at offset %d. Saw %c instead of %c\n",
             index, cnf_string[index], RIGHT_PAREN);
      return NULL;
    }

    skip_whitespace(cnf_string, &index);

    if (cnf_string[index] == '+') {
      index++;
    } else {
      break;
    }

    skip_whitespace(cnf_string, &index);
  }

  CNFSatFormula *cnfsat = (CNFSatFormula *)malloc(sizeof(CNFSatFormula));
  if (cnfsat == NULL) {
    return NULL;
  }
  cnfsat->disjunctions = disjunctions;
  cnfsat->num_disjunctions = num_disjunctions;

  return cnfsat;
}

/*
CFG for a formula in CNF:
  skip whispace {
    CNF         ->  '(' Disjunction ')' ['+' CNF]*
    Disjunction ->  Literal ['|' Disjunction]*
  }
    Literal     ->  '~'? Variable
    Variable    ->  [A-Za-z0-9]+
*/