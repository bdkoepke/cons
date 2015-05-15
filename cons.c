#include "cons.h"
#include "unsafe.h"

#include <assert.h>
#include <stdlib.h>

typedef struct {
  const Cons *left;
  const Cons *right;
} Tuple;

struct _Cons {
  enum { ETuple, ELeaf } type;
  union {
    Tuple tuple;
    void *leaf;
  };
};

Cons *cons_new_tuple(const Cons *left, const Cons *right) {
  Cons *c = malloc(sizeof(Cons));
  c->type = ETuple;
  c->tuple.left = left;
  c->tuple.right = right;
  return c;
}

Cons *cons_new_leaf(void *leaf) {
  Cons *c = malloc(sizeof(Cons));
  c->type = ELeaf;
  c->leaf = leaf;
  return c;
}

void *cons_get_value(const Cons *self) {
  return cons_is_leaf(self) ? self->leaf : NULL;
}

const Cons *cons_get_left(const Cons *self) {
  return cons_is_tuple(self) ? self->tuple.left : NULL;
}

const Cons *cons_get_right(const Cons *self) {
  return cons_is_tuple(self) ? self->tuple.right : NULL;
}

bool cons_is_leaf(const Cons *self) { return self->type == ELeaf; }

bool cons_is_tuple(const Cons *self) { return self->type == ETuple; }

void cons_post_order(const Cons *self, Closure *c) {
  switch (self->type) {
  case ELeaf:
    closure_apply(c, void_cast(self));
    break;
  case ETuple:
    cons_post_order(cons_get_left(self), c);
    cons_post_order(cons_get_right(self), c);
    closure_apply(c, void_cast(self));
    break;
  default:
    assert(false);
  }
}

static void *_cons_free(Closure *self, void *args) {
  free(args);
  return NULL;
}

void cons_free(Cons *self) {
  Closure free_closure = {.apply = _cons_free};
  cons_post_order(self, &free_closure);
}
