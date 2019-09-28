
CFLAGS = -g -I./include -Wall -Wextra -std=gnu11

libation_shared = lib/libation.so

source = $(wildcard ./*.c)
objects = $(patsubst ./%.c, ./%.o, $(source))

$(libation_shared): $(objects)
	$(CC) $(CFLAGS) -shared -o $(libation_shared) $(objects)

TEST_CFLAGS = $(CFLAGS) -I./test -L./lib -lation
test_binary = test/libation_test

test_source = $(wildcard test/*.c)
test_objects = $(patsubst test/%.c, test/%.o, $(test_source))

$(test_binary): $(test_objects)
	$(CC) $(TEST_CFLAGS) -o $(test_binary) $(test_objects)

test: $(test_binary)

clean:
	rm -f *.o $(libation_shared) $(test_binary)
