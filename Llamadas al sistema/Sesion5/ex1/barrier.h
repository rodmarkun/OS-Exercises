#include <pthread.h>
 
/**
 **  Interface of the barrier object
 **/
struct barrier {
  int             nrThreads;
  int             count;
  pthread_mutex_t mutex;
  pthread_cond_t  tQueue;
};
typedef struct barrier  barrier; 
typedef struct barrier *barrier_t; 


int barrier_init   (barrier_t barrier, int nrThreads);
int barrier_block  (barrier_t barrier);


