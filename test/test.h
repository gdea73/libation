#ifndef TEST_H
#define TEST_H

#define ASSERTATION(FMT, ACTUAL, EXPECTED) \
	do { \
		if ((ACTUAL) != (EXPECTED)) { \
			printf("%s:%s - assertion failed - expected: \"" FMT \
			       "\"; actual: \"" FMT "\"\n"); \
		} \
	} while (0)

#endif
