#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "spin-lock.h"

void
spin_wait_sleeper_callback()
{
  sleep(1);
}

void
spin_lock(struct spin_lock_state *state, int locker_id, void (*spin_wait_callback)())
{


  for (;;) {
    if (state->g2 == locker_id) {
      return;
    }
    while (state->g2 != SPIN_LOCK_NO_LOCKER) {
      if (spin_wait_callback != NULL) {
	spin_wait_callback();
      }
      continue;
    }
    state->g1 = locker_id;
    if (state->g2 == SPIN_LOCK_NO_LOCKER) {
      state->g2 = state->g1;
      if (state->g1 == locker_id) {
	if (state->g2 == locker_id) {
	  return;
	}
      }
    }
  }
}

void
spin_unlock(struct spin_lock_state *state, int locker_id)
{
  state->g2 = SPIN_LOCK_NO_LOCKER;
}

struct spin_lock_state *
spin_allocate(key_t key)
{
  int shmid;

  /* connect to (and possibly create) the segment: */
  if ((shmid = shmget(key, sizeof (struct spin_lock_state), 0644 | IPC_CREAT)) == -1) {
    perror("shmget");
    exit(1);
  }

  /* attach to the segment to get a pointer to it: */
  struct spin_lock_state *data = shmat(shmid, (void *)0, 0);
  if (data == (struct spin_lock_state *)(-1)) {
    perror("shmat");
    exit(1);
  }

  return data;
}
