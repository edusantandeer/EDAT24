#include <stdio.h>
#include "sorted_queue.h"

#define MAX_QUEUE 20

typedef struct Queue{

   void *data[MAX_QUEUE];
   int front;
   int rear;

}SortedQueue;

SortedQueue *squeue_new(){
    return queue_new();
}

void squeue_free(SortedQueue *q){
    free(q);
}

bool squeue_isEmpty(const SortedQueue *q){
    return queue_isEmpty(q);
}

Status squeue_push(SortedQueue *q, void *ele, p_queue_ele_cmp pcmp){
    
    if(q==NULL)
        return ERROR;
   
}

void squeue_pop(SortedQueue *q){
    queue_pop(q);
}

void squeue_getFront(const SortedQueue *q){
    
    return queue_getFront(q);
}

void squeue_getBack(const SortedQueue *q){

    return queue_getBack(q);
}