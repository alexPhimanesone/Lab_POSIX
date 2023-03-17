#ifndef UTILS_H
#define UTILS_H
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>

extern pthread_key_t task_info_key;

// Initialize the data structure used in this unti
void init_utils();

// Add msec milliseconds to a timespec (seconds, nanoseconds)
void add_millis_to_timespec(struct timespec *ts, long msec);

// Wait until specified absolute deadline
void delay_until(struct timespec *deadline);

// Compute time elapsed from the start time
long relative_clock();

// Delay the current task to have a more predictible execution
void resynchronize();

// Return the start time
struct timespec get_start_time();

// Store current time as the start time
void set_start_time();

char *get_task_name(int id);
void set_task_name(int id, char *name);
int get_current_task_id();
void set_current_task_id(int *id);
char *get_current_task_name();
void mtxprintf(int debug, char *format, ...);

// Read long in file f and store it in l. If there is an error,
// provide filename and line number (file:line).
int get_long(FILE *f, long *l, char *file, int line);

// Read string in file f and store it in s. If there is an error,
// provide filename and line number (file:line).
int get_string(FILE *f, char *s, char *file, int line);

#ifndef TIMEVAL_TO_TIMESPEC
#define TIMEVAL_TO_TIMESPEC(tv, ts)                                            \
  {                                                                            \
    (ts)->tv_sec = (tv)->tv_sec;                                               \
    (ts)->tv_nsec = (tv)->tv_usec * 1000;                                      \
  }
#endif
#ifndef TIMESPEC_TO_TIMEVAL
#define TIMESPEC_TO_TIMEVAL(tv, ts)                                            \
  {                                                                            \
    (tv)->tv_sec = (ts)->tv_sec;                                               \
    (tv)->tv_usec = (ts)->tv_nsec / 1000;                                      \
  }
#endif
#ifdef DARWIN
int sem_timedwait(sem_t *restrict sem, const struct timespec *abs_timeout);
int pthread_mutex_timedlock(pthread_mutex_t *mutex,
                            const struct timespec *abs_timeout);
#endif
#endif
