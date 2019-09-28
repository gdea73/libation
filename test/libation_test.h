#ifndef TEST_H
#define TEST_H

#include "libation_internal.h"

/* Literal-formatting utilities (fmt.c) */
#define TO_STRING(L) # L
#define STRINGIFY(L) TO_STRING(L)
#define FORMAT_LITERAL(L) format_literal(STRINGIFY(L))
const char *format_literal(const char *literal);

#define ASSERTATION_FMT(FMT, ACTUAL, EXPECTED) \
	do { \
		if ((ACTUAL) != (EXPECTED)) { \
			print_assertion_failure(); \
		} \
	} while (0)

#define ASSERTATION(ACTUAL, EXPECTED) \
	ASSERTATION_FMT(FORMAT_LITERAL(ACTUAL), ACTUAL, EXPECTED);

#define LIBATION_TESTS { \
		{ stack_test, "basic stack test" } \
	}

/* stack_test.c */
void stack_test(void);

#endif
