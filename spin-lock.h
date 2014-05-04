#ifndef _SPIN_LOCK
#define _SPIN_LOCK 1

#include <sys/shm.h>

#define SPIN_LOCK_NO_LOCKER 0

#define SPIN_WAIT_NO_CALLBACK (void *)0
#define SPIN_WAIT_DEFAULT_CALLBACK spin_wait_sleeper_callback

// this must be allocated in a shared space
struct spin_lock_state
{
  volatile unsigned int g1;
  volatile unsigned int g2;
};

extern void spin_unlock(struct spin_lock_state *state, int locker_id);
extern void spin_lock(struct spin_lock_state *state, int locker_id, void (*spin_wait_callback)());
extern struct spin_lock_state *spin_allocate(key_t key);
extern void spin_wait_sleeper_callback();

#endif
