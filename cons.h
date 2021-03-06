#ifndef CONS_H
#define CONS_H

#include "closure.h"

#include <stdbool.h>

typedef struct _Cons Cons;

Cons *cons_new_tuple(const Cons *, const Cons *);
Cons *cons_new_leaf(void *);
void *cons_get_value(const Cons *);
const Cons *cons_get_left(const Cons *);
const Cons *cons_get_right(const Cons *);
bool cons_is_leaf(const Cons *);
bool cons_is_tuple(const Cons *);
/**
 * Applies the specified closure to each element
 * in the cons tree.
 */
void cons_post_order(const Cons *, Closure *c);
void cons_free(Cons *);

#endif
