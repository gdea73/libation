#ifndef LIBATION_INTERNAL_H
#define LIBATION_INTERNAL_H

#include <libation.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define EINVAL_IF_NULL(P, RV) do { \
		if (!(P)) { \
			errno = EINVAL; \
			return RV; \
		} \
	} while (0)

#endif
