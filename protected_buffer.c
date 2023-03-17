#include "protected_buffer.h"
#include "cond_protected_buffer.h"
#include "sem_protected_buffer.h"

long sem_impl; // Use the semaphore implementation or not
int pb_debug = 0;

// Initialise the protected buffer structure above. sem_impl specifies
// whether the implementation is a semaphore based implementation.
protected_buffer_t *protected_buffer_init(long sem_impl, int length) {
  protected_buffer_t *b;
  if (sem_impl)
    b = sem_protected_buffer_init(length);
  else
    b = cond_protected_buffer_init(length);
  b->sem_impl = sem_impl;
  return b;
}

// Extract an element from buffer. If the attempted operation is
// not possible immedidately, the method call blocks until it is.
void *protected_buffer_get(protected_buffer_t *b) {
  if (b->sem_impl)
    return sem_protected_buffer_get(b);
  else
    return cond_protected_buffer_get(b);
}

// Insert an element into buffer. If the attempted operation is
// not possible immedidately, the method call blocks until it is.
void protected_buffer_put(protected_buffer_t *b, void *d) {
  if (b->sem_impl)
    sem_protected_buffer_put(b, d);
  else
    cond_protected_buffer_put(b, d);
}

// Extract an element from buffer. If the attempted operation is not
// possible immedidately, return NULL. Otherwise, return the element.
void *protected_buffer_remove(protected_buffer_t *b) {
  if (b->sem_impl)
    return sem_protected_buffer_remove(b);
  else
    return cond_protected_buffer_remove(b);
}

// Insert an element into buffer. If the attempted operation is
// not possible immedidately, return 0. Otherwise, return 1.
int protected_buffer_add(protected_buffer_t *b, void *d) {
  if (b->sem_impl)
    return sem_protected_buffer_add(b, d);
  else
    return cond_protected_buffer_add(b, d);
}

// Extract an element from buffer. If the attempted operation is not
// possible immedidately, the method call blocks until it is, but
// waits no longer than the given timeout. Return the element if
// successful. Otherwise, return NULL.
void *protected_buffer_poll(protected_buffer_t *b, struct timespec *abstime) {
  if (b->sem_impl)
    return sem_protected_buffer_poll(b, abstime);
  else
    return cond_protected_buffer_poll(b, abstime);
}

// Insert an element into buffer. If the attempted operation is not
// possible immedidately, the method call blocks until it is, but
// waits no longer than the given timeout. Return 0 if not
// successful. Otherwise, return 1.
int protected_buffer_offer(protected_buffer_t *b, void *d,
                           struct timespec *abstime) {
  if (b->sem_impl)
    return sem_protected_buffer_offer(b, d, abstime);
  else
    return cond_protected_buffer_offer(b, d, abstime);
}
