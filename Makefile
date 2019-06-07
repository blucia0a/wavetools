GCC=gcc

CFLAGS+= -I. -g -Wno-deprecated

LDFLAGS+= -std=c11 -lm

all: sysh

%.o: %.c
	$(GCC) $(CFLAGS) -c $^ -o $@

sysh: amp.o noise.o reslpf.o out.o lpfsimp.o mixn.o mix.o wavetable.o wavloader.o module.o wave.o sbuf.o sysh.o
	$(GCC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	-rm *.o 
	-rm sysh.exe sysh
	-rm sysh
