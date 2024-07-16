#ifndef VECTOR_SERIALIZER_H
#define VECTOR_SERIALIZER_H

#include <matrixmath.h>
#include <json.h>

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
 * Generates a JSON representation of the given Vector object.
 *
 * This function serializes a Vector object into a JSON format.
 *
 * @param struct vector *object
 *   The Vector object to serialize.
 *
 * @return struct json*
 *   Returns a JSON object containing a serialized representation of the Vector object,
 *   or NULL if the serialization fails.
 */
struct json *vector_serialize_to_json(struct vector *object);

/**
 * Serializes a vector to a JSON object.
 *
 * This function takes a pointer to a vector and a key for the JSON object,
 * serializes the vector, and creates a JSON object with the given key
 * and the serialized vector.
 *
 * @param const char *key
 *   Name of the JSON key for the serialized vector.
 * @param struct vector *object
 *   Pointer to the vector containing the data to serialize.
 *
 * @return struct json*
 *   Returns a pointer to the created JSON object on success, or NULL on failure.
 */
struct json *vector_serialize_to_json_object(const char *key, struct vector *object);

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
 * Generates a JSON representation of the given Matrix object.
 *
 * This function serializes a Matrix object into a JSON format.
 *
 * @param struct matrix *object
 *   The Matrix object to serialize.
 *
 * @return struct json*
 *   Returns a JSON object containing a serialized representation of the Matrix object,
 *   or NULL if the serialization fails.
 */
struct json *matrix_serialize_to_json(struct matrix *object);

/**
 * Serializes a matrix to a JSON object.
 *
 * This function takes a pointer to a matrix and a key for the JSON object,
 * serializes the matrix, and creates a JSON object with the given key
 * and the serialized matrix.
 *
 * @param const char *key
 *   Name of the JSON key for the serialized matrix.
 * @param struct matrix *object
 *   Pointer to the matrix containing the data to serialize.
 *
 * @return struct json*
 *   Returns a pointer to the created JSON object on success, or NULL on failure.
 */
struct json *matrix_serialize_to_json_object(const char *key, struct matrix *object);

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
