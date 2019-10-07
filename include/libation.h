#ifndef LIBATION_H
#define LIBATION_H

#include <stdint.h>
#include <stddef.h>

/******************************************************************************
 * stackation: a statically-sized stack backed by a contiguous chunk of memory
 ******************************************************************************/

typedef struct stackation {
	void *internals;
	/* resizes the stack's internal storage */
	int (*expand)(struct stackation *s, size_t new_max_elements);
	/* pushes a new element on top of this stack */
	int (*push)(struct stackation *s, void *element);
	/* pops the top element off the top of this stack */
	void * (*pop)(struct stackation *s);
	/* releases all memory used by this stack */
	void (*free)(struct stackation *s);
} stackation;

/* initializes a stack */
int stackation_init(size_t max_elements, size_t element_size, stackation *s);

/******************************************************************************
 * allocation: a heap allocator for fixed-sized chunks of memory
 ******************************************************************************/

#endif
