#include "libation_test.h"

BEGIN_TEST_FILE();

/* declare test functions */
static void stack_test(void);
/* declare test metadata for harness */
libation_test stack_tests[] = {
	{ stack_test, "basic stack test" },
	{ 0 } /* test array must be NULL-terminated */
};
/* declare suite metadata for harness */
test_suite stack_suite = DECLARE_TEST_SUITE(stack_tests, "stack tests");

typedef char stack_element[3];

static void stack_test(void)
{
#define STACK_ELEMENT_0 "DA"
#define STACK_ELEMENT_1 "DB"
#define STACK_ELEMENT_2 "OD"
#define STACK_ELEMENT_3 "LI"
#define STACK_ELEMENT_4 "FE"
	stackation s = {0};

	/* can't initialize stack unless a valid pointer is supplied */
	ASSERTATION(-1, stackation_init(5, 3, NULL));
	/* can initialize if we pass &s */
	ASSERTATION(0, stackation_init(5, 3, &s));
	/* can't pop off a stack that's initially empty */
	ASSERTATION(NULL, s.pop(&s));
	/* can push onto the stack five times */
	ASSERTATION(0, s.push(&s, STACK_ELEMENT_0));
	ASSERTATION(0, s.push(&s, STACK_ELEMENT_1));
	ASSERTATION(0, s.push(&s, STACK_ELEMENT_2));
	ASSERTATION(0, s.push(&s, STACK_ELEMENT_3));
	ASSERTATION(0, s.push(&s, STACK_ELEMENT_4));
	/* can't push onto the full stack */
	ASSERTATION(-1, s.push(&s, "??"));
	/* can pop off of the stack five times */
	ASSERTATION_FMT("%s", STACK_ELEMENT_4, s.pop(&s));
	ASSERTATION_FMT("%s", STACK_ELEMENT_3, s.pop(&s));
	ASSERTATION_FMT("%s", STACK_ELEMENT_2, s.pop(&s));
	ASSERTATION_FMT("%s", STACK_ELEMENT_1, s.pop(&s));
	ASSERTATION_FMT("%s", STACK_ELEMENT_0, s.pop(&s));
	/* can't pop off a stack that's finally empty */
	ASSERTATION(NULL, s.pop(&s));
	/* clean up heap usage */
	s.free(&s);
}

END_TEST_FILE();
