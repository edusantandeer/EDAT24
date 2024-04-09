#include "elements.h"
#include <stdio.h>
#include <stdlib.h>

/****************************************
 *
 *  DEFAULT PRINT FUNCTIONS
 *
 ***************************************
 */

int char_print(FILE *fp, const void *p) {
  char c;
  if (!fp || !p) {
    fprintf(stderr, "Wrong arguments to function %s\n", __func__);
    return -1;
  }
  c = *(char *)p;
  return fprintf(fp, "%c ", c);
}

int int_print(FILE *fp, const void *p) {
  if (!fp || !p) {
    fprintf(stderr, "Wrong arguments to function %s\n", __func__);
    return -1;
  }
  return fprintf(fp, "%d ", *((int *)p));
}

/*****************************************************************************
 *
 *  COMPARISON FUNCTIONS
 *
 *  Functions of type compare_elem_fn, i.e.
 *  int (*cmp) (const void* elem1, const void* elem2)
 *****************************************************************************
 */
