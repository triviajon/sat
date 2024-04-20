#include "sat.h"

/**
 * Custom map to store Variable-boolean pairs.
 */
typedef struct
{
    Variable *keys[MAX_VARIABLES]; // Array of Variable pointers
    bool values[MAX_VARIABLES];    // Array of boolean values
    int size;                      // Current size of the map
} VarMap;

/**
 * Initializes a new empty VarMap.
 *
 * @return Pointer to the newly created VarMap.
 */
VarMap* var_map_init();

/**
 * Inserts a Variable-boolean pair into the map.
 *
 * @param map Pointer to the VarMap.
 * @param key Pointer to the Variable.
 * @param value Boolean value to associate with the Variable.
 * @return true if insertion was successful, false otherwise.
 */
bool var_map_insert(VarMap* map, Variable* key, bool value);

/**
 * Retrieves the boolean value associated with a Variable.
 *
 * @param map Pointer to the VarMap.
 * @param key Pointer to the Variable to look up.
 * @param value Pointer to store the retrieved boolean value.
 * @return true if the Variable exists in the map, false otherwise.
 */
bool var_map_get(VarMap* map, Variable* key, bool* value);

/**
 * Frees the memory used by the VarMap.
 *
 * @param map Pointer to the VarMap to free.
 */
void var_map_free(VarMap* map);