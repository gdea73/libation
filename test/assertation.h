#ifndef ASSERTATION_H
#define ASSERTATION_H

/* "Beauty is in the eye of the preprocessor."
 * An exercise in macro gymnastics so as to provide a simple unit-test assertion
 * API. Consumers need not manually specify the types or format strings of their
 * assertions if a literal is used as the expected value. */

#define MAX_LITERAL_LENGTH 509
#define ASSERTION_MESSAGE_SIZE 512

#define FORMAT_LITERAL(L) format_literal(STRINGIFY(L))
const char *format_literal(const char *literal);
int string_compare(void *actual, void *expected, size_t size);
void print_assertion_failure(const char *file_name, unsigned int line,
		const char *fmt, ...);

#define EVALUATE_ASSERTATION(FMT, FILE_NAME, LINE_NO, EXPECTED, ACTUAL) \
	do { \
		uint8_t passed = 0; \
		if ('s' == FMT[1]) { \
			passed = string_compare( \
				(void *) ((long int) ACTUAL), \
				(void *) ((long int) EXPECTED), sizeof EXPECTED \
			); \
		} else { \
			passed = ((ACTUAL) == (EXPECTED)); \
		} \
		assertion *a = &SUITE_ASSERTIONS_ARRAY[__COUNTER__]; \
		a->passed = passed; \
		a->asserted = 1; \
		if (!passed) { \
			print_assertion_failure(FILE_NAME, LINE_NO, FMT, \
					EXPECTED, ACTUAL); \
		} \
	} while (0)

#endif
