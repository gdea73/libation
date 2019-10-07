#ifndef LIBATION_H
#define LIBATION_H

#include <stdint.h>
#include <stddef.h>

typedef struct stackation {
	void *internals;
	/* pushes a new element on top of this stack */
	int (*push)(struct stackation *s, void *element);
	/* pops the top element off the top of this stack */
	void * (*pop)(struct stackation *s);
	/* releases all memory used by this stack */
	void (*free)(struct stackation *s);
} stackation;

/* initializes a stack */
int stackation_init(size_t max_elements, size_t element_size, stackation *s);

#endif
