#include "parse.h"


bool isWhiteSpace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

bool isVariableChar(char c) {
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
    strcpy((*var).name, var_name);
    return var;
}

Literal *parseLiteral(char *cnf_string, int *index) {
    bool negated = false;
    if (cnf_string[*index] == '~') {
        negated = true;
        (*index)++;
    }

    while (cnf_string[*index] == ' ') {
        (*index)++;
    }

    Literal *lit = (Literal*) malloc(sizeof(Literal)); 
    lit->var = *parseVariable(cnf_string, index);
    lit->negated = negated;
    return lit;
}

Disjunction* parseDisjunction(char *cnf_string, int *index) {
    int num_literals = 0;
    Literal *literals = NULL;

    while (true) {
        Literal lit = *parseLiteral(cnf_string, index);
        literals = (Literal*) realloc(literals, (num_literals + 1) * sizeof(Literal));
        literals[num_literals] = lit;
        num_literals++;
        
        while (isWhiteSpace(cnf_string[*index])) {
            (*index)++;
        }

        if (cnf_string[*index] != '|') {
            break;
        }

        (*index)++;
    }

    Disjunction *disj = (Disjunction*) malloc(sizeof(Disjunction));
    disj->literals = literals;
    disj->num_literals = num_literals;

    return disj;
}

CNFSatFormula *parseCNF(char *cnf_string) {
    int index = 0;
    if (cnf_string[index] == '(') {
        index++;
    }

    Disjunction *disj = parseDisjunction(cnf_string, &index);

    int num_disjunctions = 0;
    Disjunction *disjunctions = NULL;

    while (true) {
        Disjunction disj = *parseDisjunction(cnf_string, index);
        disjunctions = (Disjunction*) realloc(disjunctions, (num_disjunctions + 1) * sizeof(Disjunction));
        disjunctions[num_disjunctions] = disj;
        num_disjunctions++;
        
        while (isWhiteSpace(cnf_string[index])) {
            index++;
        }

        if (cnf_string[index] != '+') {
            break;
        }

        index++;
    }

    CNFSatFormula *cnfsat = (CNFSatFormula*) malloc(sizeof(CNFSatFormula));
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