#include "parse.h"


bool isWhiteSpace(const char c) {
    return c == SPACE || c == '\t' || c == '\n';
}

bool isVariableChar(const char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
};

Variable *parseVariable(char *cnf_string, int *index) {
    char var_name[MAX_VARIABLE_LEN]; 
    int length = 0;
    
    while (isVariableChar(cnf_string[*index])) {
        var_name[length] = cnf_string[*index];
        (*index)++;
        length++;
    }

    var_name[length] = '\0';

    Variable *var = (Variable*) malloc(sizeof(Variable));
    if (var == NULL) { return NULL; }
    strcpy((*var).name, var_name);
    return var;
}

Literal *parseLiteral(char *cnf_string, int *index) {
    bool negated = false;
    if (cnf_string[*index] == NOT) {
        negated = true;
        (*index)++;
    }

    while (cnf_string[*index] == SPACE) {
        (*index)++;
    }

    Literal *lit = (Literal*) malloc(sizeof(Literal)); 
    Variable *var = parseVariable(cnf_string, index);
    if (var == NULL) { return NULL; } 
    lit->var = var;
    lit->negated = negated;
    return lit;
}

Disjunction* parseDisjunction(char *cnf_string, int *index) {
    int num_literals = 0;
    Literal **literals = NULL;

    while (true) {
        Literal *lit = parseLiteral(cnf_string, index);
        if (lit == NULL) { return NULL; }
        literals = (Literal**) realloc(literals, (num_literals + 1) * sizeof(Literal*));
        literals[num_literals] = lit;
        num_literals++;
        
        while (isWhiteSpace(cnf_string[*index])) {
            (*index)++;
        }

        if (cnf_string[*index] != OR) {
            break;
        }

        (*index)++;
    }

    while (true) {
        if (isWhiteSpace(cnf_string[*index])) {
            (*index)++;
        } else if (cnf_string[*index] == RIGHT_PAREN) {
            // Do not increment index since RIGHT_PAREN is part of the CNF var in the grammar
            break;
        } else {
            return NULL;
        }
    }

    Disjunction *disj = (Disjunction*) malloc(sizeof(Disjunction));
    if (disj == NULL) { return NULL; }
    disj->literals = literals;
    disj->num_literals = num_literals;

    return disj;
}

CNFSatFormula *parseCNF(char *cnf_string) {
    int index = 0;

    int num_disjunctions = 0;
    Disjunction **disjunctions = NULL;

    while (true) {
        if (cnf_string[index] == LEFT_PAREN) {
            index++;
        } else {
            printf("Failed parsing string at offset %d. Saw %c instead of %c\n", index, cnf_string[index], LEFT_PAREN);
            return NULL;
        }

        Disjunction *disj = parseDisjunction(cnf_string, &index);
        if (disj == NULL) { return NULL; }

        disjunctions = (Disjunction**) realloc(disjunctions, (num_disjunctions + 1) * sizeof(Disjunction*));
        disjunctions[num_disjunctions] = disj;
        num_disjunctions++;
        
        while (isWhiteSpace(cnf_string[index])) {
            index++;
        }

        if (cnf_string[index] == RIGHT_PAREN) {
            index++;
        } else {
            printf("Failed parsing string at offset %d. Saw %c instead of %c\n", index, cnf_string[index], RIGHT_PAREN);
            return NULL;
        }

        if (cnf_string[index] == '+') {
            index++;
        } else {
            break;
        }
    }

    CNFSatFormula *cnfsat = (CNFSatFormula*) malloc(sizeof(CNFSatFormula));
    if (cnfsat == NULL) { return NULL; }
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