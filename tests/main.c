#include <stdlib.h>
#include "vector_serializer_tests.h"
#include "matrix_serializer_tests.h"

/**
 * Main controller function.
 *
 * @param int argc
 *   The number of arguments passed by the user in the command line.
 * @param array argv
 *   Array of char, the arguments names.
 *
 * @return int
 *   The constant that represents the exit status.
 */
int main(int argc, char const *argv[]) {
  // Run vector serializer tests and check for failure.
  if (vector_serializer_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  // Run matrix serializer tests and check for failure.
  if (matrix_serializer_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  // Return success response.
  return EXIT_SUCCESS;
}
