#include <stdlib.h>
#include <json.h>
#include "../include/matrixmath_serializer.h"

/**
 * {@inheritdoc}
 */
char *matrix_serialize(struct matrix *object) {
  struct json *container = json_array();
  long double *lvalue;
  struct json *jvalue;
  for (int j = 0; j < object->rows; j++) {
    struct json *row_items = json_array();
    for (int k = 0; k < object->columns; k++) {
      lvalue = matrix_getl(object, j, k);
      jvalue = json_number(*lvalue);
      json_push(row_items, jvalue);
    }
    json_push(container, row_items);
  }
  return json_encode(container);
}

/**
 * {@inheritdoc}
 */
struct matrix *matrix_unserialize(char *data) {
  struct json *container = json_decode(data);
  if (container == NULL) {
    return NULL;
  }
  return NULL;
}
