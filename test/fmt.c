#include "libation_test.h"

#include <float.h>
#include <limits.h>

#define MAX_LITERAL_LENGTH 509

void print_assertion_failure(const char *fmt, ...)
{
	/* TODO: snprintf the format string into 
			printf("%s:%s - assertion failed - expected: \"" FMT \
			       "\"; actual: \"" FMT "\"\n"); \ */
}

const char *format_literal(const char *literal)
{
#define RETURN_HEX_OR_DEC(PREFIX) do { \
	if (hex) \
		return PREFIX "x"; \
	return PREFIX "d"; \
} while (0)

	size_t length = strnlen(literal, MAX_LITERAL_LENGTH);
	char *ll_end = NULL, *ld_end = NULL;
	unsigned long long int hella_long = strtoull(literal, &ll_end, 10);
	long double hella_precise = strtold(literal, &ld_end);
	uint8_t hex = (length > 2
		&& '0' == literal[0]
		&& ('x' == literal[1] || 'X' == literal[1])
	);

	if (ll_end == literal) {
		/* integer parsing failed; assume string */
		return "%s";
	}

	if (ld_end > ll_end) {
		/* floating-point literal */
		if (ld_end != length - 1) {
			/* assume double literal (e.g., 0.7071) */
			return "%d";
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
				return "%d";
		}
	}
	/* integer literal */
	if (ld_end == length || length - (ld_end - literal) > 3) {
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

