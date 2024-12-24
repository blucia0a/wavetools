GCC=gcc
CC = $(GCC)

CFLAGS += -I. -g -Wno-deprecated

LDFLAGS += -std=c11 -lm

all: sysh viz


%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

sysh: env.o amp.o noise.o reslpf.o out.o lpfsimp.o mixn.o mix.o wavetable.o wavloader.o module.o wave.o sysh.o fft.o fft_kernel.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

viz:
	$(GCC) viz.c -O3 -o viz -lSDL2

fft_kernel: fft_kernel.c
	$(GCC) -DFFT_KERNEL_TEST -O3 -I. -g -Wno-deprecated $^ -o $@ -lm

clean:
	-rm *.o *.pdf *.out
	-rm sysh.exe sysh
	-rm sysh fft_kernel
