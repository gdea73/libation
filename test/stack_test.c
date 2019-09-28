#include "libation_test.h"

void stack_test(void)
{
	stackation s = {0};
	const char *fmt = FORMAT_LITERAL(0);
	printf(fmt);
	stackation_init(5, 5, &s);
}
