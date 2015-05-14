#ifndef CLOSURE_H
#define CLOSURE_H

typedef struct _Closure Closure;
typedef void *(*closure_apply_f)(Closure *, void *args);
struct _Closure {
	closure_apply_f apply;
};

void *closure_apply(Closure *, void *args);

#endif
