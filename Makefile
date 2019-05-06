GCC=gcc

CFLAGS+= -I. -g -Wno-deprecated

LDFLAGS+= -std=c11

all: sysh

%.o: %.c
	$(GCC) $(CFLAGS) -c $^ -o $@

sysh: module.o wave.o sbuf.o sysh.o
	$(GCC) $(CFLAGS) $^ -o $@

clean:
	-rm *.o 
	-rm sysh.exe
