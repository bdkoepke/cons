#include "closure.h"

void *closure_apply(Closure *self, void *args) {
	return self->apply(self, args);
}
