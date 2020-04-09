#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct node {
  int id; 
  int data; 
  pthread_mutex_t mutex; 
};

#define TABLE_SIZE 5
struct node * table[TABLE_SIZE]; 

//pthread_mutex_t mutexT; 

// initialize data
struct node * create_node(int id){
  struct node * ptr;
  ptr = (struct node *) malloc(sizeof(struct node)); 
  ptr->id = id;
  ptr->data = 1;
  pthread_mutex_init(&(ptr->mutex), NULL); 
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
void Add_data(int id){
  struct node * ptr = table[id]; 
  pthread_mutex_lock(&(ptr->mutex));  
  (ptr->data)++; 
  pthread_mutex_unlock(&(ptr->mutex));  
}

void Find_and_add_data(int id){
  int i; 
  struct node * ptr; 
  for(i = 0; i < TABLE_SIZE; i++){
    ptr = table[i]; 
    if((ptr != NULL)&&(ptr->id == id)){
      Add_data(id);
      printf("table id= %d data= %d added\n", ptr->id, ptr->data);
      break;
    }
  }
}

// delete data and free node 
void Release_data(int id){
  struct node * ptr = table[id]; 
  pthread_mutex_lock(&(ptr->mutex));  
  (ptr->data)--; 
  if((ptr->data) == 0){
    pthread_mutex_unlock(&(ptr->mutex));  
    pthread_mutex_destroy(&(ptr->mutex));  
    free(ptr);
  }
  else{
    pthread_mutex_unlock(&(ptr->mutex));  
  }
}

// processing

void * t1(void * arg){
   Find_and_add_data(1); 
   sleep(2);
   pthread_exit((void *)NULL); 
}

void * t2(void * arg){
   Find_and_add_data(1); 
   sleep(2);
   pthread_exit((void *)NULL); 
}

void * t3(void * arg){
   Find_and_add_data(4); 
   sleep(2);
   pthread_exit((void *)NULL); 
}

#define NUM_THREADS 3

int main(void){

   pthread_t ntid[NUM_THREADS];

   init_data(); 

   print_nodes();
  //pthread_mutex_init(&mutexT, NULL); 
    
   pthread_create(&ntid[0], NULL, t1, (void *)NULL);  
   pthread_create(&ntid[1], NULL, t2, (void *)NULL);  
   pthread_create(&ntid[2], NULL, t3, (void *)NULL);  


   pthread_join(ntid[0], NULL);
   pthread_join(ntid[1], NULL);
   pthread_join(ntid[2], NULL);
   printf("summary\n");
   print_nodes();
}
