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

static void * get_index(stackation_internals *internals, size_t index)
{
	char *element = internals->data;
	element += internals->element_size * index;
	return element;
}

static int stack_push(stackation *s, void *element)
{
	void *element_in_stack = NULL;
	stackation_internals *internals = NULL;

	EINVAL_IF_NULL(s, -1);
	internals = s->internals;

	/* check for a full stack */
	if (internals->top_index > internals->max_elements - 1) {
		errno = ENOMEM;
		return -1;
	}
	
	element_in_stack = get_index(internals, internals->top_index++);
	memcpy(element_in_stack, element, internals->element_size);

	return 0;
}

static void * stack_pop(stackation *s)
{
	stackation_internals *internals = NULL;

	EINVAL_IF_NULL(s, NULL);
	internals = s->internals;

	/* check for an empty stack */
	if (0 == internals->top_index) {
		errno = EINVAL;
		return NULL;
	}

	return get_index(internals, --internals->top_index);
}

static void stack_free(stackation *s)
{
	if (!s) {
		return;
	}
	if (s->internals) {
		stackation_internals *internals = s->internals;
		if (internals->data) {
			free(internals->data);
			internals->data = NULL;
		}
		free(internals);
		internals = NULL;
	}
}

int stackation_init(size_t max_elements, size_t element_size, stackation *s)
{
	EINVAL_IF_NULL(s, -1);
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
	s->push = stack_push;
	s->pop = stack_pop;
	s->free = stack_free;
	return 0;

error_cleanup:
	if (internals) {
		free(internals);
	}
	return -1;
}
