#include <stddef.h>
#include <json.h>
#include <strutils.h>
#include "../include/matrixmath_serializer.h"

/**
 * {@inheritdoc}
 */
char *matrix_serialize(struct matrix *object) {
  // Generates a JSON representation of the given Matrix object.
  struct json *jobject = matrix_serialize_to_json(object);
  if (jobject == NULL) {
    return NULL;
  }
  // Encode the JSON Matrix representation into a string.
  char *json_string = json_encode(jobject);
  // Clean up JSON Matrix object after encoding.
  json_destroy(jobject);
  // Returning the JSON string.
  return json_string;
}

/**
 * {@inheritdoc}
 */
struct json *matrix_serialize_to_json(struct matrix *object) {
  // Check if NULL matrix object passed for serialization.
  if (object == NULL) {
    return NULL;
  }
  // Create JSON array jobject.
  struct json *jobject = json_array();
  if (jobject == NULL) {
    return NULL;
  }
  // Fill the jobject with matrix values.
  long double *lvalue;
  struct json *jvalue;
  for (int j = 0; j < object->rows; j++) {
    struct json *row_items = json_array();
    if (row_items == NULL) {
      json_destroy(jobject);
      return NULL;
    }
    for (int k = 0; k < object->columns; k++) {
      lvalue = matrix_getl(object, j, k);
      jvalue = json_number_string(*lvalue);
      if (jvalue == NULL) {
        json_destroy(row_items);
        json_destroy(jobject);
        return NULL;
      }
      json_push(row_items, jvalue);
    }
    json_push(jobject, row_items);
  }
  // Returning the JSON object.
  return jobject;
}

/**
 * {@inheritdoc}
 */
struct matrix *matrix_unserialize(char *data) {
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
  // Calculate the size of the matrix.
  int rows = 0;
  int columns = 0;
  struct json *current_row = NULL;
  for (struct json *rows_iterator = current; rows_iterator != NULL; rows_iterator = rows_iterator->next) {
    // Only count non-null values in the array.
    if (rows_iterator->value != NULL) {
      rows++;
      current_row = rows_iterator->value;
    }
  }
  if (current_row == NULL) {
    json_destroy(container);
    return NULL;
  }
  for (struct json *columns_iterator = current_row; columns_iterator != NULL; columns_iterator = columns_iterator->next) {
    // Only count non-null values in the array.
    if (columns_iterator->value != NULL) {
      columns++;
    }
  }
  // Verify if the matrix contains only numeric values (no null values).
  if (rows == 0 || columns == 0) {
    json_destroy(container);
    return NULL;
  }
  // Create the matrix.
  struct matrix *matrix_object = matrix_create(rows, columns);
  if (matrix_object == NULL) {
    json_destroy(container);
    return NULL;
  }
  // Fill the matrix.
  int j = 0;
  int k = 0;
  for (struct json *rows_iterator = current; rows_iterator != NULL; rows_iterator = rows_iterator->next) {
    // Only count non-null values in the array.
    if (rows_iterator->value == NULL) {
      continue;
    }
    current_row = rows_iterator->value;
    k = 0;
    for (struct json *columns_iterator = current_row; columns_iterator != NULL; columns_iterator = columns_iterator->next) {
      // Only count non-null values in the array.
      if (columns_iterator->value == NULL) {
        continue;
      }
      // Convert the number string into a long double value.
      long double numeric_value = stold((char *)columns_iterator->value);
      // Add the long double value to the matrix object.
      matrix_setl(matrix_object, j, k, numeric_value);
      // Increment the column index.
      k++;
    }
    // Increment the row index.
    j++;
  }
  // Clean up JSON container after unserializing.
  json_destroy(container);
  // Return the matrix object.
  return matrix_object;
}
