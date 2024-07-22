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
struct json *matrix_serialize_to_json_object(const char *key, struct matrix *object) {
  // Serialize the matrix to JSON.
  struct json *jmatrix = matrix_serialize_to_json(object);
  if (jmatrix == NULL) {
    return NULL;
  }
  // Create a JSON object with the given key and serialized matrix.
  struct json *jobject = json_object(key, jmatrix);
  if (jobject == NULL) {
    json_destroy(jmatrix);
    return NULL;
  }
  // Return the JSON object.
  return jobject;
}

/**
 * {@inheritdoc}
 */
struct matrix *matrix_unserialize_from_json_object(struct json *jobject) {
  // Validates the input.
  if (jobject == NULL) {
    return NULL;
  }
  // Check if the data passed is a JSON array.
  if (jobject->type != JSON_array) {
    json_destroy(jobject);
    return NULL;
  }
  // Check if the JSON array is empty.
  struct json *current = jobject->value;
  if (current == NULL) {
    json_destroy(jobject);
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
    json_destroy(jobject);
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
    json_destroy(jobject);
    return NULL;
  }
  // Create the matrix.
  struct matrix *matrix_object = matrix_create(rows, columns);
  if (matrix_object == NULL) {
    json_destroy(jobject);
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
  // Return the matrix object.
  return matrix_object;
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
  struct json *jobject = json_decode(data);
  if (jobject == NULL) {
    return NULL;
  }
  // Unserialize the matrix object.
  struct matrix *matrix_object = matrix_unserialize_from_json_object(jobject);
  if (matrix_object == NULL) {
    json_destroy(jobject);
    return NULL;
  }
  // Clean up JSON container after unserializing.
  json_destroy(jobject);
  // Return the matrix object.
  return matrix_object;
}

/**
 * {@inheritdoc}
 */
struct matrix *matrix_get_and_unserialize_from_json_object(const char *key, struct json *json_object) {
  // Get the JSON array associated with the key.
  struct json *json_array = json_get_array(json_object, key);
  if (json_array == NULL) {
    return NULL;
  }
  // Return the unserialized matrix object.
  return matrix_unserialize_from_json_object(json_array);
}

/**
 * {@inheritdoc}
 */
int matrix_set_from_json_object(struct matrix *destination, const char *key, struct json *json_object) {
  // Retrieve and unserialize the matrix from the JSON object.
  struct matrix *source = matrix_get_and_unserialize_from_json_object(key, json_object);
  if (source == NULL) {
    return 1;
  }
  // Try to copy the source matrix into the destination matrix.
  if (matrix_copy(source, destination) == 1) {
    matrix_destroy(source);
    return 1;
  }
  // Free memory.
  matrix_destroy(source);
  // Operation successfully completed.
  return 0;
}
