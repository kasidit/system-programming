#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct node {
  int id; 
  int data; 
};

#define TABLE_SIZE 5
struct node * table[TABLE_SIZE]; 
pthread_mutex_t mutexT; 

// initialize data
struct node * create_node(int id){
  struct node * ptr;
  ptr = (struct node *) malloc(sizeof(struct node)); 
  ptr->id = id;
  ptr->data = 1;
  return ptr; 
}

void init_data(void){
  int i; 
  for(i = 0; i < TABLE_SIZE; i++){
    table[i] = create_node(i); 
  } 
}

void print_nodes(void){
  int i; 
  struct node * ptr; 
  for(i = 0; i < TABLE_SIZE; i++){
    ptr = table[i]; 
    if(ptr != NULL){
      printf("node id = %d\n", ptr->id); 
      printf("     data = %d\n", ptr->data); 
    }
  } 
}

// add data 
void Add_data(struct node * ptr){ 
  (ptr->data)++; 
}

void Find_and_add_data(int id){
  struct node * ptr; 
  pthread_mutex_lock(&mutexT); 
  sleep(2);
  ptr = table[id]; 
  if(ptr != NULL){
      Add_data(ptr);
      printf("table id= %d data= %d added\n", ptr->id, ptr->data);
  }
  pthread_mutex_unlock(&mutexT); 
}

// delete data and free node 
void Release_data_safe(int id){
  struct node * ptr; 
  pthread_mutex_lock(&mutexT); 
  ptr = table[id]; 
  pthread_mutex_unlock(&mutexT);  

  if(ptr == NULL) return;

  pthread_mutex_lock(&mutexT); 
  if((ptr->data) == 1){
    (ptr->data)--; 
    table[id] = NULL;
    free(ptr);
    pthread_mutex_unlock(&mutexT);  
  }
  else{
    (ptr->data)--; 
    pthread_mutex_unlock(&mutexT);  
  }
}
// processing

void * t1(void * arg){
   Find_and_add_data(2); 
   //sleep(1);
   pthread_exit((void *)NULL); 
}

void * t2(void * arg){
   Release_data_safe(2); 
   //sleep(1);
   pthread_exit((void *)NULL); 
}

#define NUM_THREADS 3

int main(void){

   pthread_t ntid[NUM_THREADS];

   init_data(); 
   print_nodes();
   pthread_mutex_init(&mutexT, NULL); 
    
   pthread_create(&ntid[0], NULL, t1, (void *)NULL);  
   pthread_create(&ntid[1], NULL, t2, (void *)NULL);  

   pthread_join(ntid[0], NULL);
   pthread_join(ntid[1], NULL);
   printf("summary\n");
   print_nodes();
}
