# spin-lock

Some time in the early 1990s a friend (Mike Ditto) and I (Keith Gabryelski) worked on this code.  I've recently reconstituted the algorithm from memory.  Here it is for those to use as needed.

A user level spin lock that does not require exchange instruction.

## example code

```c
struct spin_lock_state *state = spin_allocate((key_t)42, NULL);
int pid = getpid();

spin_lock(state, pid)

// critical code here

spin_unlock(state, pid);

```

## second example (provided)

```c
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
```

compile the above code and then run in two different windows:

### first window

```
./spin-lock-test spin-lock-test.c 1
```

### second window
```
./spin-lock-test spin-lock-test.c 2
```
