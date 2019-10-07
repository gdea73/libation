#include "libation_test.h"

#include <float.h>
#include <limits.h>

const char *format_literal(const char *literal)
{
#define RETURN_HEX_OR_DEC(PREFIX) do { \
	if (hex) \
		return PREFIX "x"; \
	return PREFIX "d"; \
} while (0)

	size_t length = strnlen(literal, MAX_LITERAL_LENGTH);
	char *ll_end = NULL, *ld_end = NULL;
	(void) strtoull(literal, &ll_end, 10);
	(void) strtold(literal, &ld_end);
	uint8_t hex = (length > 2
		&& '0' == literal[0]
		&& ('x' == literal[1] || 'X' == literal[1])
	);

	if (!ll_end) {
		/* integer parsing failed; assume string */
		return "%s";
	}

	if (ld_end > ll_end) {
		/* floating-point literal */
		if (ld_end != literal + length - 1) {
			/* assume double literal (e.g., 0.7071) */
			return "%g";
		}
		/* look for a single-character sizing suffix */
		switch (literal[length - 1]) {
			case 'f':
			case 'F':
				/* single-precision floating-point (e.g., 0.909f) */
				/* converted to double implicitly */
				return "%f";
			case 'l':
			case 'L':
				/* quadruple-precision floating-point (e.g., 2e-8192L) */
				return "%Lg";
			default:
				return "%g";
		}
	}
	/* integer literal */
	if (ld_end == literal + length || length - (ld_end - literal) > 3) {
		/* standard int literal, or garbage at the end */
		if (hex) {
			return "%x";
		}

		return "%d";
	}
	switch (literal[length - 1]) {
		case 'u':
		case 'U':
			switch (literal[length - 2]) {
				case 'l':
				case 'L':
					switch (literal[length - 3]) {
						case 'l':
						case 'L':
							return "%llu";
						default:
							return "%lu";
					}
				default:
					return "%u";
			}
		case 'l':
		case 'L':
			switch (literal[length - 2]) {
				case 'l':
				case 'L':
					switch (literal[length - 3]) {
						case 'u':
						case 'U':
							return "%llu";
						default:
							return "%lld";
					}
				case 'u':
				case 'U':
					return "%lu";
				default:
					return "%ld";
			}
		default:
			if (hex) {
				return "%x";
			}

			return "%d";
	}
}

int string_compare(void *actual, void *expected, size_t size)
{
	/* avoidance of compiler's (admittedly reasonable) warnings:
	 * because EVALUATE_ASSERTATION is expanded for both string assertions and
	 * non-string assertions, everything is casted to a (long int) and then a
	 * (void *) before being passed to str(n)cmp. Even after the double-cast,
	 * the compiler warns about null values being passed to srncmp, despite the
	 * fact that such a case should never be encountered at runtime. Hence the
	 * below NULL checks. */
	if (NULL == actual || NULL == expected)
	{
		return (NULL == actual) == (NULL == expected);
	}

	return (!strncmp(actual, expected, size));
}

void print_assertion_failure(const char *file_name, unsigned int line,
		const char *fmt, ...)
{
	char format_string[ASSERTION_MESSAGE_SIZE] = {0};
	va_list va;

	snprintf(format_string, sizeof format_string,
			"(%s:%d) assertion failed - expected: '%s'; "
			"actual: '%s'\n", file_name, line, fmt, fmt);

	/* avoid -Wvarargs by reassigning last named argument */
	fmt = format_string;
	va_start(va, fmt);
	vprintf(format_string, va);
	va_end(va);
}

