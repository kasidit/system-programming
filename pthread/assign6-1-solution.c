#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *child_thr(void *rank);
pthread_t thread_handle[6];

int main(int argc, char* argv[]){
    long i;
    for(i=0; i<2;i++)
      pthread_create(&thread_handle[i], NULL, child_thr, (void *)(i+1));
    printf("Hello from the main thread\n");
    for(i=0; i<2;i++)
      pthread_join(thread_handle[i], NULL);
}

void *child_thr(void *rank){
    long i; long myrank = (long) rank;
    printf("Hello from thread %ld\n", myrank);
    if(myrank > 2) return(0);
    for(i=0; i<2;i++)
      pthread_create(&thread_handle[i], NULL, child_thr,
                                              (void *)(myrank*2+(i+1)));
    for(i=0; i<2;i++)
      pthread_join(thread_handle[i], NULL);
}

