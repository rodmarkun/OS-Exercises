#include <pthread.h>
#include <barrier.h>
#include <stdio.h>

/*
In this exercise we are going to build a fundamental synchronization object: the barrier.
The threads that use a given barrier form a pre-established set of N threads.
In the figure we have an example with N = 3.
All the threads are blocking in the barrier, looking for a moment of common resumption. This arrives when the last thread of the set invokes barrier.
barrier takes as parameter a pointer to a barrier object.
*/


int barrier_init (barrier_t barrier, int nrThreads) 
{ 
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexAt;
    (void) pthread_mutexattr_init(&mutexAt);
    pthread_cond_t  tQueue;

    barrier->nrThreads = nrThreads;
    barrier->count = 0;
    barrier->mutex = mutex;
    barrier->tQueue = tQueue;

  return 0;
}

int barrier_block(barrier_t barrier) 
{
    pthread_mutex_lock(&barrier->mutex);
    barrier->count++;
    if(barrier->count != barrier->nrThreads){
        pthread_cond_wait(&barrier->tQueue, &barrier->mutex);
    }
    else{
        pthread_cond_signal(&barrier->tQueue);
        barrier->count = 0;
    }

    pthread_mutex_unlock(&barrier->mutex);
  return 0;
}