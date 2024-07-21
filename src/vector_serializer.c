#include <stddef.h>
#include <json.h>
#include <strutils.h>
#include "../include/matrixmath_serializer.h"

/**
 * {@inheritdoc}
 */
char *vector_serialize(struct vector *object) {
  // Generates a JSON representation of the given Vector object.
  struct json *jobject = vector_serialize_to_json(object);
  if (jobject == NULL) {
    return NULL;
  }
  // Encode the JSON object.
  char *jstring = json_encode(jobject);
  // Clean up JSON array object after encoding.
  json_destroy(jobject);
  // Returning the JSON string.
  return jstring;
}

/**
 * {@inheritdoc}
 */
struct json *vector_serialize_to_json(struct vector *object) {
  // Check if NULL vector object passed for serialization.
  if (object == NULL) {
    return NULL;
  }
  // Create JSON array object.
  struct json *jobject = json_array();
  if (jobject == NULL) {
    return NULL;
  }
  long double *lvalue;
  struct json *jvalue;
  for (int i = 0; i < object->capacity; i++) {
    lvalue = vector_getl(object, i);
    if (lvalue == NULL) {
      json_destroy(jobject);
      return NULL;
    }
    jvalue = json_number_string(*lvalue);
    if (jvalue == NULL) {
      json_destroy(jobject);
      return NULL;
    }
    json_push(jobject, jvalue);
  }
  // Returning the JSON object.
  return jobject;
}

/**
 * {@inheritdoc}
 */
struct json *vector_serialize_to_json_object(const char *key, struct vector *object) {
  // Serialize the vector to JSON.
  struct json *jvector = vector_serialize_to_json(object);
  if (jvector == NULL) {
    return NULL;
  }
  // Create a JSON object with the given key and serialized vector.
  struct json *jobject = json_object(key, jvector);
  if (jobject == NULL) {
    json_destroy(jvector);
    return NULL;
  }
  // Return the JSON object.
  return jobject;
}

/**
 * {@inheritdoc}
 */
struct vector *vector_unserialize_from_json_object(struct json *jobject) {
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
    json_destroy(jobject);
    return NULL;
  }
  // Create the vector.
  struct vector *vector_object = vector_create(capacity);
  if (vector_object == NULL) {
    json_destroy(jobject);
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
  // Return the vector object.
  return vector_object;
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
  struct json *jobject = json_decode(data);
  if (jobject == NULL) {
    return NULL;
  }
  // Unserialize the JSON object.
  struct vector *vector_object = vector_unserialize_from_json_object(jobject);
  if (vector_object == NULL) {
    json_destroy(jobject);
    return NULL;
  }
  // Clean up JSON object after unserializing.
  json_destroy(jobject);
  // Return the vector object.
  return vector_object;
}
