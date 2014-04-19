#define NO_LOCKER 0

// this must be allocated in a shared space
struct spin_lock_state
{
  volatile unsigned int g1;
  volatile unsigned int g2;
};

void
spin_lock(struct spin_lock_state *state, int locker_id)
{
  for (;;) {
    if (state->g2 == locker_id) {
      return;
    }
    while (state->g2 != NO_LOCKER) {
      continue;
    }
    state->g1 = locker_id;
    if (state->g2 == NO_LOCKER) {
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
  state->g2 = NO_LOCKER;
}
