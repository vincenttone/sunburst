#ifndif __V_SHM_H
#define __V_SHM_H 1

typedef struct {
  int shmid;
  key_t key;
  size_t size;
  size_t left_size;
} VShm;

int v_shm_init(key_t key, size_t size);
void v_shm_drop(VShm *vshm);
void *v_shm_malloc(size_t size);
void *v_shm_free(void *ptr);

#endif
