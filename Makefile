GCC=gcc
CC ?= $(GCC)

CFLAGS += -I. -g -Wno-deprecated

LDFLAGS += -std=c11 -lm

all: sysh

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

sysh: env.o amp.o noise.o reslpf.o out.o lpfsimp.o mixn.o mix.o wavetable.o wavloader.o module.o wave.o sysh.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm *.o 
	-rm sysh.exe sysh
	-rm sysh
