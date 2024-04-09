/* Very simple test code to verify that you can compile with the libqueue
 * library
 * Compile with
 *      gcc -Wall -g -o test_queue test_queue.c elements.c -L. -lqueue
 */

#include "elements.h"
#include "queue.h"

int main() {
  Queue *q;
  int arr[] = {1, 2, 3, 4};
  int i;
  void *e;
  int arr_size = sizeof(arr) / sizeof(arr[0]);

  q = queue_new();
  for (i = 1; i < arr_size; i++) {
    queue_push(q, arr + i);
  }
  queue_print(stdout, q, int_print);
  while (!queue_isEmpty(q)) {
    e = queue_pop(q);
    int_print(stdout, e);
    puts("");
  }

  return 0;
}
