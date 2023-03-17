#ifndef SEM_PROTECTED_BUFFER_H
#define SEM_PROTECTED_BUFFER_H
#include "circular_buffer.h"
#include "protected_buffer.h"
#include <pthread.h>
#include <stdlib.h>

// Initialise the protected buffer structure above.
protected_buffer_t *sem_protected_buffer_init(int length);

// Extract an element from buffer. If the attempted operation is
// not possible immedidately, the method call blocks until it is.
void *sem_protected_buffer_get(protected_buffer_t *b);

// Insert an element into buffer. If the attempted operation is
// not possible immedidately, the method call blocks until it is.
void sem_protected_buffer_put(protected_buffer_t *b, void *d);

// Extract an element from buffer. If the attempted operation is not
// possible immedidately, return NULL. Otherwise, return the element.
void *sem_protected_buffer_remove(protected_buffer_t *b);

// Insert an element into buffer. If the attempted operation is
// not possible immedidately, return 0. Otherwise, return 1.
int sem_protected_buffer_add(protected_buffer_t *b, void *d);

// Extract an element from buffer. If the attempted operation is not
// possible immedidately, the method call blocks until it is, but
// waits no longer than the given timeout. Return the element if
// successful. Otherwise, return NULL.
void *sem_protected_buffer_poll(protected_buffer_t *b,
                                struct timespec *abstime);

// Insert an element into buffer. If the attempted operation is not
// possible immedidately, the method call blocks until it is, but
// waits no longer than the given timeout. Return 0 if not
// successful. Otherwise, return 1.
int sem_protected_buffer_offer(protected_buffer_t *b, void *d,
                               struct timespec *abstime);
#endif
