#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "spin-lock.h"

int
main(int argc, char *argv[])
{
  key_t key;

  if (argc != 3) {
    fprintf(stderr, "usage: spin-lock-test [keyfile] [lockerid]\n");
    exit(1);
  }

  /* make the key: */
  if ((key = ftok(argv[1], 'R')) == -1) {
    perror("ftok");
    exit(1);
  }

  printf("key: 0x%lx\n", (long)key);

  int locker_id = atoi(argv[2]);
  printf("locker_id: %d\n", locker_id);

  printf("allocating\n");
  struct spin_lock_state *state = spin_allocate(key);

  printf("locking\n");
  spin_lock(state, locker_id, SPIN_WAIT_DEFAULT_CALLBACK);
  printf("locked ... sleeping for 30 seconds\n");

  sleep(30);

  printf("unlocking\n");
  spin_unlock(state, locker_id);
  printf("unlocked\n");

  exit(0);
}
