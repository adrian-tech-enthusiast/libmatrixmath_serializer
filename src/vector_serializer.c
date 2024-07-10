#include <stdlib.h>
#include <json.h>
#include <stdio.h>
#include <strutils.h>
#include "../include/matrixmath_serializer.h"

/**
 * {@inheritdoc}
 */
char *vector_serialize(struct vector *object) {
  // Check if NULL vector object passed for serialization.
  if (object == NULL) {
    return NULL;
  }
  // Create JSON array container.
  struct json *container = json_array();
  if (container == NULL) {
    return NULL;
  }
  long double *lvalue;
  struct json *jvalue;
  for (int i = 0; i < object->capacity; i++) {
    lvalue = vector_getl(object, i);
    if (lvalue == NULL) {
      json_destroy(container);
      return NULL;
    }
    jvalue = json_number_string(*lvalue);
    if (jvalue == NULL) {
      json_destroy(container);
      return NULL;
    }
    json_push(container, jvalue);
  }
  char *json_string = json_encode(container);
  // Clean up JSON container after encoding.
  json_destroy(container);
  // Returning the JSON string.
  return json_string;
}

/**
 * {@inheritdoc}
 */
struct vector *vector_unserialize(char *data) {
  // Check if NULL JSON data passed for unserialization.
  if (data == NULL) {
    return NULL;
  }
  // Decodes the given JSON array string.
  struct json *container = json_decode(data);
  if (container == NULL) {
    return NULL;
  }
  // Check if the data passed is a JSON array.
  if (container->type != JSON_array) {
    json_destroy(container);
    return NULL;
  }
  // Check if the JSON array is empty.
  struct json *current = container->value;
  if (current == NULL) {
    json_destroy(container);
    return NULL;
  }
  // Calculate the capacity of the vector.
  int capacity = 0;
  for (struct json *iterator = current; iterator != NULL; iterator = iterator->next) {
    // Only count non-null values in the array.
    if (iterator->value != NULL) {
      capacity++;
    }
  }
  // Verify if the array contains only numeric values (no null values).
  if (capacity == 0) {
    json_destroy(container);
    return NULL;
  }
  // Create the vector.
  struct vector *vector_object = vector_create(capacity);
  if (vector_object == NULL) {
    json_destroy(container);
    return NULL;
  }
  // Fill the vector.
  int index = 0;
  for (struct json *iterator = current; iterator != NULL; iterator = iterator->next) {
    // Only count non-null values in the array.
    if (iterator->value == NULL) {
      continue;
    }
    // Convert the number string into a long double value.
    long double numeric_value = stold((char *)iterator->value);
    // Add the long double value to the vector object.
    vector_setl(vector_object, index, numeric_value);
    // Increment the index.
    index++;
  }
  // Clean up JSON container after unserializing.
  json_destroy(container);
  // Return the vector object.
  return vector_object;
}
