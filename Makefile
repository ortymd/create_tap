CFLAGS = -g3 -Wall -I./include
LDLIBS = -l:func.o -l:tests.o
export LDFLAGS = -L./src -L./tests

.PHONY: func tests create_tap

all:  func tests create_tap

create_tap: create_tap.o func tests
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ create_tap.o $(LDLIBS)

func:
	$(MAKE) -C src/

tests:
	$(MAKE) -C tests/

clean:
	rm *.o src/*.o tests/*.o
