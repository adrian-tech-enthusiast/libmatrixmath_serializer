#include <stdio.h>
#include <stdlib.h>
#include "../include/matrixmath_serializer.h"
#include "matrix_serializer_tests.h"

/**
 * Tests the serialization of a matrix.
 *
 * This function creates a matrix with a given capacity, fills it with values,
 * serializes the matrix to a string, prints the serialized string and the matrix,
 * and then cleans up the allocated memory.
 *
 * @return int
 *   Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int matrix_serialize_tests() {
  printf("------------ Matrix Serialize Tests. ------------\n");
  // Create an matrix of 2 x 2 elements.
  const int rows = 2;
  const int columns = 2;
  struct matrix *matrix_object = matrix_create(rows, columns);
  // Fill in the matrix.
  matrix_setl(matrix_object, 0, 0, 0.0000000000045);
  matrix_setl(matrix_object, 0, 1, 320.2519111111193);
  matrix_setl(matrix_object, 1, 0, 4.634254238956);
  matrix_setl(matrix_object, 1, 1, 83.5793259741265);
  // Serialize the matrix.
  char *matrix_string = matrix_serialize(matrix_object);
  if (matrix_string == NULL) {
    matrix_destroy(matrix_object);
  }
  // Print the matrix object and the serialized matrix string.
  printf("Serialized Matrix String: %s \n", matrix_string);
  matrix_print(matrix_object);
  // Clear the used memory.
  matrix_destroy(matrix_object);
  free(matrix_string);
  // Return success response.
  return EXIT_SUCCESS;
}

/**
 * Tests the deserialization of a matrix.
 *
 * This function defines a serialized matrix string, deserializes it to a matrix,
 * prints the original string and the resulting matrix, and then cleans up the allocated memory.
 *
 * @return int
 *   Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
static int matrix_unserialize_tests() {
  printf("------------ Matrix Un-Serialize Tests. ------------\n");
  // Define the matrix string representation.
  char *matrix_string = "[[\"0.0000000000045\",\"320.2519111111193\"],[\"4.634254238956\",\"83.5793259741265\"]]";
  // Unserialize the matrix string.
  struct matrix *matrix_object = matrix_unserialize(matrix_string);
  if (matrix_object == NULL) {
    return EXIT_FAILURE;
  }
  // Print the matrix string and the unserialized matrix.
  printf("Matrix String: %s.\n", matrix_string);
  printf("Unserialized ");
  matrix_print(matrix_object);
  // Clear the used memory.
  matrix_destroy(matrix_object);
  return EXIT_SUCCESS;
}

/**
 * {@inheritdoc}
 */
int matrix_serializer_tests() {
  if (matrix_serialize_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  if (matrix_unserialize_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
