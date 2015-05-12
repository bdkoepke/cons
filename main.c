#include "cons.h"
#include "unsafe.h"

#include <assert.h>
#include <stdio.h>

void cons_print_int(const Cons *self) {
	if (cons_is_leaf(self))
		printf("%d\n", *(int *)cons_get_value(self));
}

int main() {
	const int n[] = { 5, 4, 3, 7 };
	Cons *c = cons_new_tuple(
		cons_new_tuple(
			cons_new_leaf(void_cast(&n[0])),
			cons_new_leaf(void_cast(&n[1]))),
		cons_new_tuple(
			cons_new_leaf(void_cast(&n[2])),
			cons_new_leaf(void_cast(&n[3]))));

	cons_foreach(c, cons_print_int);
	cons_free(c);
}
