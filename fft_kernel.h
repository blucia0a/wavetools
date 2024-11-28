#define SIG_LEN  1024 
#define NUM_BINS 1024 

#include "twiddlefactors_1024.h"

static const float TwoPi = 6.283185307179586476925286766559f;
complex float gettwiddle(int k, int n);
void fft(const complex float *x, complex float *X, int N, int s);
void ifft(const complex float *X, complex float *x, int N);
