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
 * Creates a Vector object from the given serialized data string.
 *
 * @param char* data
 *   The serialized string.
 *
 * @return struct vector*
 *   The unserialize Vector object object is returned, otherwise NULL.
 */
struct vector *vector_unserialize(char *data);

/**
 * Unserializes a JSON object into a vector object.
 *
 * @param struct json *jobject
 *   Pointer to the JSON object representing the vector.
 *
 * @return struct vector*
 *   Returns a pointer to the newly created vector object, or NULL if the conversion failed.
 */
struct vector *vector_unserialize_from_json_object(struct json *jobject);

/**
 * Finds and unserializes a vector from a JSON object.
 *
 * This function retrieves a vector from the JSON object based on the provided key.
 *
 * @param const char *key
 *   Key of the vector to find in the JSON object.
 * @param struct json *json_object
 *   Pointer to the JSON object containing the vectors.
 *
 * @return struct vector*
 *   Pointer to the unserialized vector, or NULL if the operation failed.
 */
struct vector *vector_get_and_unserialize_from_json_object(const char *key, struct json *json_object);

/**
 * Retrieves and unserializes a vector from a JSON object, then sets it to the destination vector.
 *
 * This function retrieves a vector from the JSON object, unserializes it, and copies its contents
 * to the destination vector.
 *
 * @param struct vector *destination
 *   Pointer to the destination vector where the unserialized data will be stored.
 * @param const char *key
 *   Key of the vector to find in the JSON object.
 * @param struct json *json_object
 *   Pointer to the JSON object containing the vectors.
 *
 * @return int
 *   Returns 0 if successful, otherwise 1 if an error occurred.
 */
int vector_set_from_json_object(struct vector *destination, const char *key, struct json *json_object);

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

/**
 * Unserializes a JSON object into a matrix object.
 *
 * @param struct json *jobject
 *   Pointer to the JSON object representing the matrix.
 *
 * @return struct matrix*
 *   Returns a pointer to the newly created matrix object, or NULL if the conversion failed.
 */
struct matrix *matrix_unserialize_from_json_object(struct json *jobject);

/**
 * Finds and unserializes a matrix from a JSON object.
 *
 * This function retrieves a matrix from the JSON object based on the provided key.
 *
 * @param const char *key
 *   Key of the matrix to find in the JSON object.
 * @param struct json *json_object
 *   Pointer to the JSON object containing the matrices.
 *
 * @return struct matrix*
 *   Pointer to the unserialized matrix, or NULL if the operation failed.
 */
struct matrix *matrix_get_and_unserialize_from_json_object(const char *key, struct json *json_object);

/**
 * Retrieves and unserializes a matrix from a JSON object, then sets it to the destination matrix.
 *
 * This function retrieves a matrix from the JSON object, unserializes it, and copies its contents
 * to the destination matrix.
 *
 * @param struct matrix *destination
 *   Pointer to the destination matrix where the unserialized data will be stored.
 * @param const char *key
 *   Key of the matrix to find in the JSON object.
 * @param struct json *json_object
 *   Pointer to the JSON object containing the matrices.
 *
 * @return int
 *   Returns 0 if successful, otherwise 1 if an error occurred.
 */
int matrix_set_from_json_object(struct matrix *destination, const char *key, struct json *json_object);

#endif // MATRIX_SERIALIZER_H
