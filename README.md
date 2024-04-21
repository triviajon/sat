## SAT Solver

This project is a simple implementation of evaluation and solving for SAT formulas (boolean expressions) using C. Still under construction! Internally, formulas are represented in conjunctive normal form (CNF). The CNF formulas are used to represent Boolean expressions as a conjunction (AND) of disjunctions (ORs). The solver can evaluate if a given CNF formula is satisfiable or not under a given variable assignment. 

### Project Structure

The project consists of several source files organized into directories as follows:

- `src/`: Contains the source code files for the main solver and utility functions.
- `include/`: Contains header files defining the data structures and function prototypes.
- `tests/`: Contains the test code to validate the solver functionalities.

### Files

- **`var_map.c`** and **`var_map.h`**: Implements a custom map to store Variable-boolean pairs.
- **`sat.c`** and **`sat.h`**: Defines data structures and functions related to SAT formulas.
- **`parse.c`** and **`parse.h`**: Implements parsing functions to convert CNF strings into CNF SAT formulas.
- **`main.c`**: Contains the main function to test the CNF SAT solver.
- **`cnf_sat_formula.h`**: Defines data structures used to represent CNF SAT formulas.
- **`Makefile`**: Contains instructions to compile the project.

### Data Structures

- **`Variable`**: Represents a variable in a CNF formula.
- **`Literal`**: Represents a literal in a CNF formula, which is either a variable or its negation.
- **`Disjunction`**: Represents a disjunction (OR) of literals.
- **`CNFSatFormula`**: Represents a CNF formula as a conjunction (AND) of disjunctions.
- **`VarMap`**: A custom map to store Variable-boolean pairs.
- **`UniqueVarArray`**: Stores an array of unique variables.

### How to Build and Run

To build the project, navigate to the project directory and run the following command:

```bash
make clean && make
./main
```

To run the tests, execute:

```bash
make clean && make TEST=1
./tester
```

### Dependencies

The project uses standard C libraries and does not require any external dependencies.

### To-do List
- Comphrensive testing strategy
- Extending parsing to all valid boolean expressions and converting to CNF.
- Implement solving of CNF formulas.

---