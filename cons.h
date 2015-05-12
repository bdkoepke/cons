#ifndef CONS_H
#define CONS_H

#include <stdbool.h>

typedef struct _Cons Cons;

typedef void (*cons_apply)(const Cons *);

Cons *cons_new_tuple(const Cons *, const Cons *);
Cons *cons_new_leaf(void *);
void *cons_get_value(const Cons *);
const Cons *cons_get_left(const Cons *);
const Cons *cons_get_right(const Cons *);
bool cons_is_leaf(const Cons *);
bool cons_is_tuple(const Cons *);
void cons_pre_order(const Cons *, cons_apply a);
void cons_free(Cons *);

#endif
