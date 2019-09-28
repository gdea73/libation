#include "libation_internal.h"

typedef struct {
	/* index of the top of the stack; index 0 is the base of the stack */
	size_t top_index;
	/* maximum number of elements that can be pushed onto the stack */
	size_t max_elements;
	/* size of an individual stack element */
	size_t element_size;
	/* max_elements * element_size bytes allocated on the heap */
	void *data;
} stackation_internals;

static int stack_push(stackation *s, void *element) {
	return 0;
}

static void * stack_pop(stackation *s) {
	return 0;
}

static int stack_free(stackation *s) {
	if (!s) {
		errno = EINVAL;
		return -1;
	}
	if (s->internals) {
		stackation_internals *internals = &s->internals;
		if (internals->data) {
			free(internals->data);
			internals->data = NULL;
		}
		free(internals);
		internals = NULL;
	}
	return 0;
}

int stackation_init(size_t max_elements, size_t element_size, stackation *s) {
	/* sanity check */
	if (!s) {
		errno = EINVAL;
		goto error_cleanup;
	}
	/* allocate memory for internals, and assign pointer in consumer's struct */
	stackation_internals *internals = calloc(1, sizeof *internals);
	if (!internals) {
		errno = ENOMEM;
		goto error_cleanup;
	}
	s->internals = internals;
	/* populate internals for given sizing parameters */
	internals->max_elements = max_elements;
	internals->element_size = element_size;
	internals->data = malloc(max_elements * element_size);
	if (!internals->data) {
		errno = ENOMEM;
		goto error_cleanup;
	}
	/* assign function pointers */
	return 0;

error_cleanup:
	if (internals) {
		free(internals);
	}
	return -1;
}
