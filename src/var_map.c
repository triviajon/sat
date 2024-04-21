#include "var_map.h"

VarMap *init_VarMap() {
  VarMap *map = (VarMap *)malloc(sizeof(VarMap));

  if (map == NULL) {
    return NULL;
  }

  map->keys = NULL;
  map->values = NULL;
  map->size = 0;

  return map;
};

/**
 * Inserts a Variable-boolean pair into the map.
 *
 * @param map Pointer to the VarMap.
 * @param key Pointer to the Variable.
 * @param value Boolean value to associate with the Variable.
 * @return true if insertion was successful, false otherwise.
 */
bool insert_VarMap(VarMap *map, Variable *key, bool value) {
  if (map == NULL || key == NULL) {
    return false;
  }

  // Check if var already exists and replace the value if it does.
  bool exists;
  int var_index = contains_VarMap(map, key, &exists);
  if (exists) {
    map->values[var_index] = value;
    return true;
  }

  // If not, need to realloc.
  Variable **newKeys =
      (Variable **)realloc(map->keys, (map->size + 1) * sizeof(Variable *));
  bool *newValues =
      (bool *)realloc(map->values, (map->size + 1) * sizeof(bool));

  if (newKeys == NULL || newValues == NULL) {
    // Handle memory allocation failure
    free(newKeys);
    free(newValues);
    return false;
  }

  map->keys = newKeys;
  map->values = newValues;

  map->keys[map->size] = key;
  map->values[map->size] = value;

  map->size++;

  return true;
};

/**
 * Retrieves the boolean value associated with a Variable.
 *
 * @param map Pointer to the VarMap.
 * @param key Pointer to the Variable to look up.
 * @param value Pointer to store the retrieved boolean value.
 * @return true if the Variable exists in the map, false otherwise.
 */
bool get_VarMap(VarMap *map, Variable *key, bool *value) {
  bool exists;
  int var_index = contains_VarMap(map, key, &exists);

  if (exists) {
    *value = map->values[var_index];
    return true;
  }

  return false;
};

int contains_VarMap(VarMap *map, Variable *key, bool *exists) {

  for (int i = 0; i < map->size; i++) {
    Variable *curr_var = map->keys[i];
    if (strcmp(curr_var->name, key->name) == 0) {
      *exists = true;
      return i;
    }
  }

  *exists = false;
  return -1;
}

/**
 * Frees the memory used by the VarMap.
 *
 * @param map Pointer to the VarMap to free.
 */
void cleanup_VarMap(VarMap *map) {
  free(map->keys);
  free(map->values);
  free(map);
};