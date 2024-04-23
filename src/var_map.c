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

void cleanup_VarMap(VarMap *map) {
  free(map->keys);
  free(map->values);
  free(map);
};

bool print_VarMap(VarMap *map, char *buffer, int bufferSize) {
    if (!map || !buffer || bufferSize <= 0) {
        return false;
    }

    int offset = 0;
    int remainingSize = bufferSize;

    int len = snprintf(buffer + offset, remainingSize, "{");
    if (len < 0 || len >= remainingSize) {
        return false; // Buffer too small
    }
    offset += len;
    remainingSize -= len;

    // Write each variable-name and its associated boolean value to the buffer
    for (int i = 0; i < map->size; ++i) {
        Variable *key = map->keys[i];
        bool value = map->values[i];

        len = snprintf(buffer + offset, remainingSize, "\"%s\": %s, ", key->name, value ? "true" : "false");
        if (len < 0 || len >= remainingSize) {
            return false; // Buffer too small
        }
        offset += len;
        remainingSize -= len;
    }

    // Replace the last ", " with a closing brace and null terminator
    if (map->size > 0) {
        buffer[offset - 2] = '}';
        buffer[offset - 1] = '\0';
    } else {
        buffer[offset] = '}';
        buffer[offset + 1] = '\0';
    }

    return true;
}