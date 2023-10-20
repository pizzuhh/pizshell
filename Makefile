CC = gcc
CFLAGS = -Wall

SRCD=./src
BUILDD=./build

SRC=$(wildcard $(SRCD)/*.c)
OUT=pizshell

all: $(OUT)

# build
$(OUT):
	mkdir -p $(BUILDD)
	$(CC) $(CFLAGS) $(SRC) -o $(BUILDD)/$@

debug:
	mkdir -p $(BUILDD)
	$(CC) $(CFLAGS) -g $(SRC) -o $(BUILDD)/$(OUT)

clean:
	rm -rf $(BUILDD)

.PHONY: all clean