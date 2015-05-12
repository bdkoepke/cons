#include "cons.h"

#include <assert.h>
#include <stdlib.h>

typedef struct {
	const Cons *left;
	const Cons *right;
} Tuple;

struct _Cons {
	enum { ETuple, ELeaf } type;
	union {
		Tuple *tuple;
		void *leaf;
	};
};

Cons *cons_new_tuple(const Cons *left, const Cons *right) {
	Cons *c = malloc(sizeof(Cons));
	{
		c->type = ETuple;
		c->tuple = malloc(sizeof(Tuple));
	}
	Tuple *t = c->tuple;
	{
		t->left = left;
		t->right = right;
	}
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
	return cons_is_tuple(self) ? self->tuple->left : NULL;
}

const Cons *cons_get_right(const Cons *self) {
	return cons_is_tuple(self) ? self->tuple->right : NULL;
}

bool cons_is_leaf(const Cons *self) {
	return self->type == ELeaf;
}

bool cons_is_tuple(const Cons *self) {
	return self->type == ETuple;
}

void cons_foreach(const Cons *self, cons_apply a) {
  if (cons_is_leaf(self)) {
		a(self);
		return;
	}
	assert (cons_is_tuple(self));
	const Cons *left = cons_get_left(self);
	const Cons *right = cons_get_right(self);
	a(self);
	cons_foreach(left, a);
	cons_foreach(right, a);
}

void cons_free(Cons *self) {
	cons_foreach(self, (cons_apply)free);
}
