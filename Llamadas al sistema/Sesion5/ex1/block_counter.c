#include <pthread.h>
#include <barrier.h>
#include <stdio.h>
 
#define NR_ITERA   32   
#define NR_THREADS  4


/**
 **  Program that uses the barrier package
 **/

void *Cycler(void *barrera) 
{  
  barrier_t  bar = (barrier_t)barrera;  
  int        i; 
 
  for(i = 0; i < NR_ITERA; i++ ) {
    barrier_block(bar);    
    printf("iteration %d\n", i);   
  } 
  return NULL;
}




int main(int argc, char *argv[])
{
  pthread_t  th1, th2, th3, th4;
  barrier    my_barrier;

  barrier_init (&my_barrier, NR_THREADS); 

  pthread_create(&th1, NULL, Cycler, (void *) &my_barrier);
  pthread_create(&th2, NULL, Cycler, (void *) &my_barrier);
  pthread_create(&th3, NULL, Cycler, (void *) &my_barrier);
  pthread_create(&th4, NULL, Cycler, (void *) &my_barrier);
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);
  pthread_join(th4, NULL);
  printf("\n");   
  return 0;
}
