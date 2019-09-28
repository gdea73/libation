#include "libation_test.h"

struct {
	void (*test_function)(void); const char *test_name;
} tests = LIBATION_TESTS;

int main(int argc, char **argv)
{
	/* ignore command-line arguments */
	(void) argc, (void) argv;
}
