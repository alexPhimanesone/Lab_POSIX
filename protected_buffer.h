#ifndef PROTECTED_BUFFER_H
#define PROTECTED_BUFFER_H
#include "circular_buffer.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define BLOCKING 0
#define NONBLOCKING 1
#define TIMEDOUT 2
extern long sem_impl; // Use the semaphore implementation or not
extern int pb_debug;

// Protected buffer structure used for both implemantations.
typedef struct {
  long sem_impl;
  circular_buffer_t *buffer;
} protected_buffer_t;

// Initialise the protected buffer structure above. sem_impl specifies
// whether the implementation is a semaphore based implementation.
protected_buffer_t *protected_buffer_init(long sem_impl, int length);

// Extract an element from buffer. If the attempted operation is
// not possible immedidately, the method call blocks until it is.
void *protected_buffer_get(protected_buffer_t *b);

// Insert an element into buffer. If the attempted operation is
// not possible immedidately, the method call blocks until it is.
void protected_buffer_put(protected_buffer_t *b, void *d);

// Extract an element from buffer. If the attempted operation is not
// possible immedidately, return NULL. Otherwise, return the element.
void *protected_buffer_remove(protected_buffer_t *b);

// Insert an element into buffer. If the attempted operation is
// not possible immedidately, return 0. Otherwise, return 1.
int protected_buffer_add(protected_buffer_t *b, void *d);

// Extract an element from buffer. If the attempted operation is not
// possible immedidately, the method call blocks until it is, but
// waits no longer than the given timeout. Return the element if
// successful. Otherwise, return NULL.
void *protected_buffer_poll(protected_buffer_t *b, struct timespec *abstime);

// Insert an element into buffer. If the attempted operation is not
// possible immedidately, the method call blocks until it is, but
// waits no longer than the given timeout. Return 0 if not
// successful. Otherwise, return 1.
int protected_buffer_offer(protected_buffer_t *b, void *d,
                           struct timespec *abstime);
#endif
