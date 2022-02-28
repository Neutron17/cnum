CC = clang

PNAME = c

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN = build

EXEC = $(BIN)/$(PNAME)
INCFLAGS  = -Isrc/

CCFLAGS += $(INCFLAGS)


LDFLAGS  = $(INCFLAGS)
# LDFLAGS += -lstdc++
# LDFLAGS += -Llib/ntr
# LDFLAGS += -lengine

all: build

run: build
	$(BIN)/c $*

build: $(OBJ)
	$(CC) -ggdb -o $(BIN)/c $(filter %.o,$^) $(LDFLAGS)

clean:
	rm $(BIN)/* $(OBJ)

%.o: %.c
	$(CC) -ggdb -o $@ -c $< $(CCFLAGS)
