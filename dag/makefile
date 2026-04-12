CC=gcc
CFLAGS=-Wall -lm
LDFLAGS=
EXEC=testtopo
TEST_EXEC=testtopo_unit

COMMON_SRC= topo.c ../graph/graph.c ../queue/queue.c ../stack/stack.c ../list/list.c
SRC= testtopo.c $(COMMON_SRC)
OBJ= $(SRC:.c=.o)

TEST_SRC= testtopo_unit.c $(COMMON_SRC)
TEST_OBJ= $(TEST_SRC:.c=.o)

all: $(EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(TEST_EXEC): $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.../queue/queue.o: ../queue/queue.h
../stack/stack.o: ../stack/stack.h
../list/list.o: ../list/list.h
../graph/graph.o: ../graph/graph.h
topo.o: topo.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ)
	rm -f $(TEST_OBJ)
	rm -f *~
	rm -f $(EXEC)
	rm -f $(TEST_EXEC)
	rm -f *.svg



