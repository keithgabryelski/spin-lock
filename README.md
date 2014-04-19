#spin-lock

Some time in the early 1990s a friend (Mike Ditto) and I (Keith Gabryelski) worked on this code.  I've recently reconstituted the algorithm from memory.  Here it is for those to use as needed.

A user level spin lock that does not require exchange instruction.

.untested example code

```c
struct spin_lock_state *state = spin_allocate();
int pid = getpid();

spin_lock(state, pid)

// critical code here

spin_unlock(state, pid);

```
