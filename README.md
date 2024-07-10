## Lib Matrix Math Serializer: This Vector and Matrix Serialization Library provides a set of C functions to serialize and deserialize vector and matrix objects.

The Vector and Matrix Serializer Library is a C library designed to provide serialization and deserialization functionalities for vector and matrix objects. This library allows you to convert vector and matrix objects into string representations and reconstruct them from these strings. It is particularly useful for saving objects to files, transmitting them over networks, or any scenario where you need a human-readable representation of your data structures.

### Features

- **Vector Serialization**: Convert vector objects to and from string representations.
- **Matrix Serialization**: Convert matrix objects to and from string representations.
- **Ease of Use**: : Simple API for integrating serialization functionality into your projects.
- **Documentation**: Comprehensive documentation and examples are provided to help you get started quickly and easily.
- **Compatibility**: Depends on the [libmatrixmath_serializer](https://github.com/adrian-tech-enthusiast/libmatrixmath_serializer) library for mathematical operations on vectors and matrices.
- **Open Source**: The library is open source and actively maintained, allowing for community contributions and enhancements.

### Prerequisites

Before installing Lib Matrix Math Serializer, ensure you have the following libraries installed:

1. [**Lib Matrix Math (libmatrixmath)**](https://github.com/adrian-tech-enthusiast/libmatrixmath?tab=readme-ov-file#installation) [v1.1.0](https://github.com/adrian-tech-enthusiast/libstr/releases/tag/v1.1.0) or later - Offers a robust collection of functions designed for efficient manipulation of vectors and matrices.
2. [**Lib Strutils (libstr)**](https://github.com/adrian-tech-enthusiast/libstr?tab=readme-ov-file#installation) [v1.0.1](https://github.com/adrian-tech-enthusiast/libstr/releases/tag/v1.0.1) or later - Offers a robust collection of functions designed for efficient manipulation of character arrays.
3. [**Lib JSON (libjson)**](https://github.com/adrian-tech-enthusiast/libjson?tab=readme-ov-file#installation) [v1.0.0](https://github.com/adrian-tech-enthusiast/libjson/releases/tag/v1.0.0) or later - Provides efficient JSON parsing, useful for encoding and decoding JSON objects.

### Getting Started

To use the Vector and Matrix Serializer Library in your project, include the respective header files and link against the [libmatrixmath_serializer](https://github.com/adrian-tech-enthusiast/libmatrixmath_serializer) library. 

### Installation

To make sure you obtain the most updated stable version of [shared library](https://en.wikipedia.org/wiki/Library_(computing)#Shared_libraries)(a DLL in Windows or .so in Unix/Linux), you’ll download this software from its [official Github repository](https://github.com/adrian-tech-enthusiast/libmatrixmath_serializer).

First, confirm the latest version available in their [releases page](https://github.com/adrian-tech-enthusiast/libmatrixmath_serializer/releases). At the time of this writing, the most current stable version is `1.0.0`.

1. The following command will download the `1.0.0` release and save the shared library file at /usr/local/lib/libmatrixmath_serializer.so, which will make this library globally accessible to clients:

    ```bash
    sudo curl -L "https://github.com/adrian-tech-enthusiast/libmatrixmath_serializer/releases/download/v1.0.0/libmatrixmath_serializer.so" -o /usr/local/lib/libmatrixmath_serializer.so
    ```

2. Next, We need to tell the loader it is available for use, so let us update the cache, invoke the `ldconfig` utility, which configures the system's dynamic loader. This configuration ensures that the loader will find the newly published library:

    ```bash
    sudo ldconfig;
    ```

    That should create a link to our shared library and update the cache so it is available for immediate use. To verify you can run:

    ```bash
    ldconfig -p | grep matrixmath
    ```

3. Copy the library header file(`matrixmath_serializer.h`) to where it can be included in one of the C compiler's search path. Typical locations are `/usr/include` and `/usr/local/include`;

    ```bash
    sudo curl -L "https://raw.githubusercontent.com/adrian-tech-enthusiast/libmatrixmath_serializer/v1.0.0/include/matrixmath_serializer.h" -o /usr/local/include/matrixmath_serializer.h;
    ```

    This allows the library header file to be included in your C project as follows:

    ```c
    #include <stdio.h>  /* standard input/output functions */
    #include <matrixmath_serializer.h> /* C Matrix Math Serializer Library functions */
    ```
    Without this `#include`, the compiler would complain about missing declarations for functions provided by the C Matrix Math Library. 

4. Finally in order to compile your code with the library, add the link flag to the library during the compilation of your C project: 

    ```bash
    gcc -o tester tester.c -lmatrixmath_serializer
    ```

### Example Usage

Here's a basic example demonstrating how to use the Matrix Math Serializer library to perform serialization:

```c
#include <stdio.h>
#include <stdlib.h>
#include <matrixmath_serializer.h>

/**
 * Tests the serialization of a vector.
 *
 * This function creates a vector with a given capacity, fills it with values,
 * serializes the vector to a string, prints the serialized string and the vector,
 * and then cleans up the allocated memory.
 *
 * @return int
 *   Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int vector_serialize_tests() {
  printf("------------ Vector Serialize Tests. ------------\n");
  // Create an vector of #20 elements.
  int capacity = 2;
  struct vector *vector_object = vector_create(capacity);
  if (vector_object == NULL) {
    return EXIT_FAILURE;
  }
  // Fill in the vector.
  vector_setl(vector_object, 0, 0.0000000000045);
  vector_setl(vector_object, 1, 320.2519111111193);
  // Serialize the vector.
  char *vector_string = vector_serialize(vector_object);
  if (vector_string != NULL) {
    printf("Serialized Vector String: %s \n", vector_string);
    free(vector_string);
  }
  // Print the vector.
  vector_print(vector_object);
  // Clear the used memory.
  vector_destroy(vector_object);
  // Return success response.
  return EXIT_SUCCESS;
}

/**
 * Tests the deserialization of a vector.
 *
 * This function defines a serialized vector string, deserializes it to a vector,
 * prints the original string and the resulting vector, and then cleans up the allocated memory.
 *
 * @return int
 *   Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int vector_unserialize_tests() {
  printf("------------ Vector Un-Serialize Tests. ------------\n");
  // Define the vector string representation.
  char *vector_string = "[\"0.0000000000045\",\"320.2519111111193\"]";
  // Unserialize the vector string
  struct vector *vector_object = vector_unserialize(vector_string);
  if (vector_object == NULL) {
    return EXIT_FAILURE;
  }
  printf("Vector String: %s.\n", vector_string);
  // Print the vector.
  printf("Unserialized ");
  vector_print(vector_object);
  // Clear the used memory.
  vector_destroy(vector_object);
  return EXIT_SUCCESS;
}

/**
 * Main function to run vector serialization and deserialization tests.
 *
 * This function calls the vector serialization and deserialization test functions.
 * If any of the tests fail, it returns EXIT_FAILURE. Otherwise, it returns EXIT_SUCCESS.
 *
 * @return int
 *   Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int vector_serializer_tests() {
  if (vector_serialize_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  if (vector_unserialize_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

```

### Contributions

Contributions to the C Matrix Math Library are welcome! Whether it's reporting issues, suggesting new features, or submitting pull requests, we appreciate any and all contributions from the community.

If you'd like to contribute, please follow these steps:

1. Fork the repository
2. Create your feature branch (git checkout -b feature/my-feature)
3. Commit your changes (git commit -am 'Add my feature')
4. Push to the branch (git push origin feature/my-feature)
5. Create a new Pull Request

### License

This library is licensed under the `GNU General Public License v3.0` License. See the LICENSE file for details.

### Acknowledgments

- Inspired by the need for efficient linear algebra operations in C.
- Special thanks to contributors and open-source libraries that provided inspiration and guidance.
