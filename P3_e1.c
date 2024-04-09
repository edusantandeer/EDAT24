#include "types.h"
#include "sorted_queue.h"
#include "maze.h"
#include "string.h"

int string_cmp(const void *s1, const void *s2) {
    return strcmp((char *)s1, (char *)s2);
}

int integer_cmp(int i1, int i2){
    int result=0;
    if(i1<i2){
        result = -5;
    }
    
    if(i1 == i2){
        result = 0;
    }

    if(i1>i2){
        result = 5;
    }

    return result;
}



int main(){
    SortedQueue *int_queue = squeue_new();
    if(int_queue == NULL){
        fprintf(stdout, "\nError al crear cola de enteros\n");
        return -1;
    }

    SortedQueue *point_queue = squeue_new();
    if(point_queue == NULL){
        fprintf(stdout, "\nError al crear cola de puntos\n");
        squeue_free(int_queue);
        return -1;
    }   

    SortedQueue *strings_queue = squeue_new();

    if(strings_queue == NULL){
        fprintf(stdout, "\nError al crear cola de strings\n");
        squeue_free(point_queue);
        squeue_free(int_queue);
        return -1;
    }
    int i;
    int enteros[4] = {8, 2, 1, 10, 0};
    Point *points[4];

    points[0] = point_new(0, 0, WALL);
    points[1] = point_new(7, 6, IN);
    points[2] = point_new(1, 2, SPACE);
    points[3] = point_new(4, 3, OUT);
    points[4] = point_new(0, 0, IN);

    char *strings[3] = {"hola", "platano", "pera", "manzana"};

    for(i=0; i<5; i++){
        if(squeue_push(int_queue, enteros[i], integer_cmp) == ERROR){
            fprintf(stdout, "\nError al insertar en la cola de enteros\n");
            return -1;
        }
    }

    fprintf(stdout, "\ncola de enteros:\n");
    
    squeue_print(stdout, int_queue, int_print);

    fprintf(stdout, "\n");

    for(i=0; i<5; i++){
        if(squeue_push(point_queue, &points[i], point_cmp) == ERROR){
            fprintf(stdout, "\nError al insertar en la cola de puntos\n");
            return -1;
        }
    }

    fprintf(stdout, "\ncola de puntos:\n");
    
    squeue_print(stdout, int_queue, point_print);

    fprintf(stdout, "\n");

    for(i=0; i<4; i++){
        if(squeue_push(strings_queue, &strings[i], string_cmp) == ERROR){
            fprintf(stdout, "\nError al insertar en la cola de strings\n");
            return -1;
        }
    }

    fprintf(stdout, "\ncola de strings:\n");
    
    squeue_print(stdout, int_queue, char_print);

    fprintf(stdout, "\n");


}