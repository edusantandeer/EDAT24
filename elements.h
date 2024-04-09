#ifndef _ELEMENTS_H
#define _ELEMENTS_H

#include "types.h"
#include <stdio.h>

/* function type to print an element */
typedef int (*print_elem_fn)(FILE *, const void *elem);

/* function type to compare two elements */
/*
 * This function type matches the requirement for the compare argument of the
 * standard library function qsort
 *
 * In C, the convention (for qsort but also for any other place where an
 * ordering among elements needs to be defined) is that, for a given way to
 * order elements, this function should return:
 *
 *  - a negative value if the first argument should be ordered *before* the
 * second,
 *  - a positive value if the first argument should be ordered *after* the
 * second,
 *  - 0 if both arguments are indistinguishable according to the order
 *
 * Thus for example, to sort integers in ascending order, the function may
 * simply return (int *)elem1 - (int*) elem2; similarly, to sort strings in
 * ascending order, you can return the result of strcmp applied to the
 * appropriatetly casted arguments.
 *
 * On the other hand, to use descending order, you'll need to define separate
 * functions, these functions may simply change the sign of the value returned
 * in the previous examples
 */

typedef int (*compare_elem_fn)(const void *elem1, const void *elem2);

/* ADD ADDITIONAL FUNCTION TYPES HERE AS NEEDED */
/* you might want to consider functions to initialize, copy, free elements... In
the first two cases, should they allocate memory or not? or should we have two
versions to allow for both options? */

/* HERE ARE TWO EXAMPLES */
/* function type to convert strings to elements of the appropriate type */
/* the functions should allocate memory for the element */
typedef void *(*elem_from_string_fn)(const char *str);

/* generic function type to process an element */
typedef void (*process_elem_fn)(const void *element);

/* PROTOTYPES FOR SPECIFIC FUNCTIONS OF THESE TYPES*/
int int_print(FILE *pf, const void *a);
int char_print(FILE *pf, const void *a);
#endif
