#include "libation_test.h"

static const test_suite *suites[] = TEST_SUITES;

static void print_suite_assertion_summary(const test_suite *suite)
{
	size_t assertions_passed = 0, assertions_failed = 0;
	assertion *assertion = suite->assertions;
	
	while (assertion->asserted) {
		if (assertion->passed) {
			assertions_passed++;
		} else {
			assertions_failed++;
		}
		assertion++;
	}

	printf("'%s' suite results: %zu assertions passed; %zu assertions failed\n",
			suite->suite_name, assertions_passed, assertions_failed);
}

static void execute_test_suite(const test_suite *suite)
{
	printf("Executing test suite: '%s'\n", suite->suite_name);
	libation_test *current_test = suite->tests;

	while (NULL != current_test->test_function) {
		printf("Executing test: '%s'\n", current_test->test_name);
		current_test->test_function();
		current_test++;
	}

	print_suite_assertion_summary(suite);
}

int main(int argc, char **argv)
{
	/* ignore command-line arguments */
	(void) argc, (void) argv;

	for (size_t suite_idx = 0; NULL != suites[suite_idx]; suite_idx++) {
		const test_suite *current_suite = suites[suite_idx];
		execute_test_suite(current_suite);
	}
}
