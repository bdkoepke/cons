#include "cons.h"
#include "unsafe.h"

#include <assert.h>
#include <stdio.h>

typedef struct {
  Closure super;
  const char *format;
} PrintClosure;

static void *cons_print(Closure *self, void *args) {
  PrintClosure *p = (PrintClosure *)self;
  const Cons *c = (const Cons *)args;
  if (cons_is_leaf(c))
    printf(p->format, *(int *)cons_get_value(c));
  return NULL;
}

int main() {
  const int n[] = {5, 4, 3, 7};
  // construct the new tree
  // Cons (Cons (5, 4), (Cons (3, 7)))
  Cons *c = cons_new_tuple(cons_new_tuple(cons_new_leaf(void_cast(&n[0])),
                                          cons_new_leaf(void_cast(&n[1]))),
                           cons_new_tuple(cons_new_leaf(void_cast(&n[2])),
                                          cons_new_leaf(void_cast(&n[3]))));

  // print each element in the tree using post-order traversal
  PrintClosure cons_print_closure = {{.apply = cons_print}, .format = "%d\n"};
  cons_post_order(c, (Closure *)&cons_print_closure);
  cons_free(c);
}
