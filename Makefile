CC = cc

PNAME = cnum

SRC  = $(shell find src -name "*.c")
OBJ  = $(SRC:.c=.o)
BIN = build

INSTALL_PATH = /usr/local/bin

EXEC = $(BIN)/$(PNAME)

INCFLAGS  = -Isrc/

CCFLAGS += $(INCFLAGS)
CCFLAGS += -ggdb
CCFLAGS += -O0
CCFLAGS += -Wall

LDFLAGS  = $(INCFLAGS)
# LDFLAGS += -lstdc++
# LDFLAGS += -Llib/ntr
# LDFLAGS += -lengine

all: build

run: build
	$(BIN)/cnum $*

build: $(OBJ)
	$(CC) -o $(BIN)/cnum $(filter %.o,$^) $(LDFLAGS)

install: build
	cp $(BIN)/$(PNAME) $(INSTALL_PATH)

clean:
	rm $(BIN)/* $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $< $(CCFLAGS)

