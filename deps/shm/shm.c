#include <sys/shm.h>
#include <string.h>

int v_shm_init(key_t key, size_t size)
{
  int shmid;
  v_shm *shm;
  if ((shmid = shmget(key, size, 0600)) < 0) {
    return -1;
  }
  if ((shm = shmat(shmid, 0, 0)) == (void *)-1) {
    return -1;
  }
  memset(shm, 0, size);
  shm->key = key;
  shm->size = size;
  shm->shmid = shmid;
  shm->left_size = size - sizeof(v_shm);
  return 0;
}

void v_shm_drop(v_shm *vshm)
{
  int shmid = vshm->shmid;
  shmctl(shmid, IPC_RMID, 0);
}
