#ifndef VECTOR_SERIALIZER_H
#define VECTOR_SERIALIZER_H

#include <matrixmath.h>

/**
 * Generates a string representation of the given Vector object.
 *
 * @param struct vector *object
 *   The Vector object to serialize.
 *
 * @return char*
 *   Returns a string containing a representation of the Vector object.
 */
char *vector_serialize(struct vector *object);

/**
 * Creates a Vector object object from the given serialized data string.
 *
 * @param char* data
 *   The serialized string.
 *
 * @return struct vector*
 *   The unserialize Vector object object is returned, otherwise NULL.
 */
struct vector *vector_unserialize(char *data);

#endif // VECTOR_SERIALIZER_H

#ifndef MATRIX_SERIALIZER_H
#define MATRIX_SERIALIZER_H

/**
 * Generates a string representation of the given Matrix object.
 *
 * @param struct matrix *object
 *   The Matrix object to serialize.
 *
 * @return char*
 *   Returns a string containing a representation of the Matrix object.
 */
char *matrix_serialize(struct matrix *object);

/**
 * Creates a Matrix object object from the given serialized data string.
 *
 * @param char* data
 *   The serialized string.
 *
 * @return struct matrix*
 *   The unserialize Matrix object object is returned, otherwise NULL.
 */
struct matrix *matrix_unserialize(char *data);

#endif // MATRIX_SERIALIZER_H
