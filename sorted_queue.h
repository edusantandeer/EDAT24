#ifndef SORTED_QUEUE_H
#define	SORTED_QUEUE_H

#include "elements.h"
#include "queue.h"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>

typedef Queue SortedQueue;

// typedef int (*print_elem_fn)(FILE *, const void *);
// typedef int (*compare_elem_fn)(const void *, const void *);

SortedQueue *squeue_new();
void squeue_free(SortedQueue *q);
bool squeue_isEmpty(const SortedQueue *q);
Status squeue_push(SortedQueue *q, void *elem, compare_elem_fn cmp);
void *squeue_pop(SortedQueue *q);
void *squeue_getFront(const SortedQueue *q);
void *squeue_getBack(const SortedQueue *q);
size_t squeue_size(const SortedQueue *q);
int squeue_print(FILE *fp, const SortedQueue *q, print_elem_fn print_elem);

#endif	/* SORTED_QUEUE_H */
