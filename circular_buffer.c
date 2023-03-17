#include <stdlib.h>
#include "circular_buffer.h"

circular_buffer_t * circular_buffer_init(int max_size) {
  circular_buffer_t * b =
    (circular_buffer_t *)malloc(sizeof(circular_buffer_t));
  b->first = 0;
  b->last  = -1;
  b->size = 0;
  b->max_size = max_size;
  b->buffer = (void *)malloc(max_size*sizeof(void *));
  return b;
}

void * circular_buffer_get(circular_buffer_t * b){
  void * d;
  if (b->size == 0) return NULL;
  d = b->buffer[b->first];
  b->first = (b-> first + 1) % b->max_size;
  b->size--;
  return d;
}

int circular_buffer_put(circular_buffer_t * b, void * d){
  if (b->size == b->max_size) return 0;
  b->last = (b->last + 1) % b->max_size;
  b->buffer[b->last] = d;
  b->size++;
  return 1;
}

int circular_buffer_size(circular_buffer_t * b) {
  return b->size;
}
   
