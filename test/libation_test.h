#ifndef TEST_H
#define TEST_H

#include "libation_internal.h"
#include "assertation.h"
#include <stdarg.h>

/* Utilitarian macros */
#define STATIC_ARRAY_SIZE(A) (sizeof(A) / sizeof(A[0]))
#define TO_STRING(L) # L
#define STRINGIFY(L) TO_STRING(L)

/* identifier used to store assertions for each test suite translation unit  */
#define SUITE_ASSERTIONS_ARRAY assertions

typedef struct {
	uint8_t passed;
	uint8_t asserted;
	unsigned int line_number;
} assertion;

typedef struct {
	void (*test_function)(void);
	const char *test_name;
} libation_test;

typedef struct {
	libation_test *tests;
	assertion *assertions;
	const char *suite_name;
} test_suite;

/******************************************************************************
 * To define a new test suite, use the macros defined below this line to
 * construct your C file, add an extern declaration of the resultant suite,
 * and add its address to the TEST_SUITES macro.
 ******************************************************************************/

#define DECLARE_TEST_SUITE(TESTS, SUITE_NAME) { \
		.tests = TESTS, \
		.assertions = SUITE_ASSERTIONS_ARRAY, \
		.suite_name = SUITE_NAME \
	}

#define BEGIN_TEST_FILE() \
	extern assertion SUITE_ASSERTIONS_ARRAY[]

#define END_TEST_FILE() \
	assertion SUITE_ASSERTIONS_ARRAY[__COUNTER__ + 1] = {0}

#define ASSERTATION(EXPECTED, ACTUAL) \
	EVALUATE_ASSERTATION(FORMAT_LITERAL(ACTUAL), __FILE__, __LINE__, \
			EXPECTED, ACTUAL)

#define ASSERTATION_FMT(FMT, EXPECTED, ACTUAL) \
	EVALUATE_ASSERTATION(FMT, __FILE__, __LINE__, EXPECTED, ACTUAL)

/* A suite must have an extern declaration here, and its address appended to
 * the TEST_SUITES macro, in order for it to be executed by the harness.
 * In the suite's C file, the test_suite must be defined with the
 * DEFINE_TEST_SUITE() macro. */
extern test_suite stack_suite;
#define TEST_SUITES { \
	&stack_suite, \
	NULL \
}

#endif
