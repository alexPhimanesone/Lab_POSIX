#include "circular_buffer.h"
#include "protected_buffer.h"
#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define EMPTY_SLOTS_NAME "/empty_slots"
#define FULL_SLOTS_NAME "/full_slots"

// Initialise the protected buffer structure above.
protected_buffer_t *sem_protected_buffer_init(int length) {
  protected_buffer_t *b;
  b = (protected_buffer_t *)malloc(sizeof(protected_buffer_t));
  b->buffer = circular_buffer_init(length);
  // Initialize the synchronization attributes
  // Use these filenames as named semaphores
  sem_unlink(EMPTY_SLOTS_NAME);
  sem_unlink(FULL_SLOTS_NAME);
  // Open the semaphores using the filenames above
  return b;
}

// Extract an element from buffer. If the attempted operation is
// not possible immedidately, the method call blocks until it is.
void *sem_protected_buffer_get(protected_buffer_t *b) {
  void *d;

  // Enforce synchronisation semantics using semaphores.

  // Enter mutual exclusion.

  d = circular_buffer_get(b->buffer);
  if (d == NULL)
    mtxprintf(pb_debug, "get (B) - data=NULL\n");
  else
    mtxprintf(pb_debug, "get (B) - data=%d\n", *(int *)d);

    // Leave mutual exclusion.

  // Enforce synchronisation semantics using semaphores.

  return d;
}

// Insert an element into buffer. If the attempted operation is
// not possible immedidately, the method call blocks until it is.
void sem_protected_buffer_put(protected_buffer_t *b, void *d) {

  // Enforce synchronisation semantics using semaphores.

  // Enter mutual exclusion.

  circular_buffer_put(b->buffer, d);
  if (d == NULL)
    mtxprintf(pb_debug, "put (B) - data=NULL\n");
  else
    mtxprintf(pb_debug, "put (B) - data=%d\n", *(int *)d);

    // Leave mutual exclusion.

  // Enforce synchronisation semantics using semaphores.
}

// Extract an element from buffer. If the attempted operation is not
// possible immedidately, return NULL. Otherwise, return the element.
void *sem_protected_buffer_remove(protected_buffer_t *b) {
  void *d = NULL;
  int rc = -1;

  // Enforce synchronisation semantics using semaphores.

  if (rc != 0) {
    if (d == NULL)
      mtxprintf(pb_debug, "remove (U) - data=NULL\n");
    else
      mtxprintf(pb_debug, "remove (U) - data=%d\n", *(int *)d);
    return d;
  }

  // Enter mutual exclusion.

  d = circular_buffer_get(b->buffer);
  if (d == NULL)
    mtxprintf(pb_debug, "remove (U) - data=NULL\n");
  else
    mtxprintf(pb_debug, "remove (U) - data=%d\n", *(int *)d);

    // Leave mutual exclusion.

  // Enforce synchronisation semantics using semaphores.

  return d;
}

// Insert an element into buffer. If the attempted operation is
// not possible immedidately, return 0. Otherwise, return 1.
int sem_protected_buffer_add(protected_buffer_t *b, void *d) {
  int rc = -1;

  // Enforce synchronisation semantics using semaphores.

  if (rc != 0) {
    d = NULL;
    if (d == NULL)
      mtxprintf(pb_debug, "add (U) - data=NULL\n");
    else
      mtxprintf(pb_debug, "add (U) - data=%d\n", *(int *)d);
    return 0;
  }

  // Enter mutual exclusion.

  circular_buffer_put(b->buffer, d);
  if (d == NULL)
    mtxprintf(pb_debug, "add (U) - data=NULL\n");
  else
    mtxprintf(pb_debug, "add (U) - data=%d\n", *(int *)d);

    // Leave mutual exclusion.

  // Enforce synchronisation semantics using semaphores.
  return 1;
}

// Extract an element from buffer. If the attempted operation is not
// possible immedidately, the method call blocks until it is, but
// waits no longer than the given timeout. Return the element if
// successful. Otherwise, return NULL.
void *sem_protected_buffer_poll(protected_buffer_t *b,
                                struct timespec *abstime) {
  void *d = NULL;
  int rc = -1;

  // Enforce synchronisation semantics using semaphores.

  if (rc != 0) {
    if (d == NULL)
      mtxprintf(pb_debug, "poll (T) - data=NULL\n");
    else
      mtxprintf(pb_debug, "poll (T) - data=%d\n", *(int *)d);
    return d;
  }

  // Enter mutual exclusion.

  d = circular_buffer_get(b->buffer);
  if (d == NULL)
    mtxprintf(pb_debug, "poll (T) - data=NULL\n");
  else
    mtxprintf(pb_debug, "poll (T) - data=%d\n", *(int *)d);

    // Leave mutual exclusion.

  // Enforce synchronisation semantics using semaphores.
  return d;
}

// Insert an element into buffer. If the attempted operation is not
// possible immedidately, the method call blocks until it is, but
// waits no longer than the given timeout. Return 0 if not
// successful. Otherwise, return 1.
int sem_protected_buffer_offer(protected_buffer_t *b, void *d,
                               struct timespec *abstime) {
  int rc = -1;

  // Enforce synchronisation semantics using semaphores.

  if (rc != 0) {
    d = NULL;
    if (d == NULL)
      mtxprintf(pb_debug, "offer (T) - data=NULL\n");
    else
      mtxprintf(pb_debug, "offer (T) - data=%d\n", *(int *)d);
    return 0;
  }

  // Enter mutual exclusion.

  circular_buffer_put(b->buffer, d);
  if (d == NULL)
    mtxprintf(pb_debug, "offer (T) - data=NULL\n");
  else
    mtxprintf(pb_debug, "offer (T) - data=%d\n", *(int *)d);

    // Leave mutual exclusion.

  // Enforce synchronisation semantics using semaphores.
  return 1;
}
