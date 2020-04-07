#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex_var; 
pthread_cond_t cv; 
int global_var = 0; 

void * foo(void * arg){

   sleep(3);
   pthread_mutex_lock(&mutex_var);  
   global_var ++;
   printf("foo() update global_var to %d\n", global_var); 
   pthread_cond_signal(&cv);
   pthread_mutex_unlock(&mutex_var);  

   pthread_exit((void *)NULL); 
}

int main(void){

   pthread_t mtid, ntid;
   void *tret; 
    
   pthread_mutex_init(&mutex_var, NULL); 
   pthread_cond_init(&cv, NULL); 

   pthread_create(&ntid, NULL, foo, NULL);  

   pthread_mutex_lock(&mutex_var);  
   while(global_var <= 0){
     pthread_cond_wait(&cv, &mutex_var); 
   }
   global_var--;
   pthread_mutex_unlock(&mutex_var);  
   printf("main() update global_var to %d\n", global_var); 

   pthread_join(ntid, tret); 

}
