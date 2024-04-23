#ifndef VAR_MAP_H
#define VAR_MAP_H

#include "cnf_sat_formula.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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
 * @return Pointer to the newly created VarMap. Must be freed later with
 * cleanup_VarMap to prevent memory leaks. If memory could not be allocated for
 * the new VarMap, returns NULL.
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
 * @param key Pointer to a Variable structure containing the key (variable) to
 * search for.
 * @param exists Pointer to a bool variable that will be updated to indicate
 * whether the variable exists in the map.
 * @return Returns the index of the found Variable in the VarMap if it exists,
 * or -1 if the Variable does not exist.
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

/**
 * Populates the provided buffer with the contents of the VarMap.
 *
 * @param map Pointer to the VarMap.
 * @param buffer Pointer to the buffer where the output will be stored.
 * @param bufferSize Size of the provided buffer.
 * @return true if the buffer was successfully populated, false otherwise.
 */
bool print_VarMap(VarMap *map, char *buffer, int bufferSize);

#endif /* VAR_MAP_H */