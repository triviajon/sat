#include <stdio.h>
#include "parse.h"


int main() {
    // char *cnf_string = "(x|y|~z)+(x|~y|z)+(~x|y|z)";
    char *cnf_string = "(~Z)";
    CNFSatFormula *cnf_sat = parseCNF(cnf_string);

    if (cnf_sat != NULL) {
        printf("num of disjunctions: %d\n", cnf_sat->num_disjunctions);
    } else {
        printf("Bad parse :( \n");
    }

    cleanup(cnf_sat);

    return 0;
}