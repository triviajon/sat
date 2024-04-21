#include <stdlib.h>
#include <string.h>
#include "cnf_sat_formula.h"

/**
 * Structure to store an array of unique variables.
 */
typedef struct {
  Variable **vars; // Array of Variable pointers
  int count;       // Number of unique variables
} UniqueVarArray;

/**
 * Custom map to store Variable-boolean pairs.
 */
typedef struct {
  Variable **keys; // Array of Variable pointers
  bool *values;    // Array of boolean values
  int size;        // Current size of the map
} VarMap;

/**
 * Initializes a new empty VarMap.
 *
 * @return Pointer to the newly created VarMap.
 */
VarMap *init_VarMap();

/**
 * Inserts a Variable-boolean pair into the map.
 *
 * @param map Pointer to the VarMap.
 * @param key Pointer to the Variable.
 * @param value Boolean value to associate with the Variable.
 * @return true if insertion was successful, false otherwise.
 */
bool insert_VarMap(VarMap *map, Variable *key, bool value);

/**
 * Checks if a Variable exists in a VarMap based on the variable's name.
 *
 * @param map Pointer to a VarMap structure.
 * @param key Pointer to a Variable structure containing the key (variable) to search for.
 * @param exists Pointer to a bool variable that will be updated to indicate whether the variable exists in the map.
 * @return Returns the index of the found Variable in the VarMap if it exists, or -1 if the Variable does not exist.
 */
int contains_VarMap(VarMap *map, Variable *key, bool *exists);

/**
 * Retrieves the boolean value associated with a Variable.
 *
 * @param map Pointer to the VarMap.
 * @param key Pointer to the Variable to look up.
 * @param value Pointer to store the retrieved boolean value.
 * @return true if the Variable exists in the map, false otherwise.
 */
bool get_VarMap(VarMap *map, Variable *key, bool *value);

/**
 * Frees the memory used by the VarMap.
 *
 * @param map Pointer to the VarMap to free.
 */
void cleanup_VarMap(VarMap *map);