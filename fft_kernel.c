#include <complex.h>
#include <math.h>

#ifdef FFT_KERNEL_TEST
#include <stdio.h>
#include <time.h>
#endif

#include "fft_kernel.h"

complex float gettwiddle(int k, int n){
  /*complex roots of unity are stored in twid[][]
    for use as twiddle factors.  
    The expression for these is cexp(-1.0 * TwoPi * I * k / N)
    These are populated from twiddlefactors_1024.h.
  */
  switch(n){
    case 1024: return twid[9][k];
    case 512: return twid[8][k];
    case 256: return twid[7][k];
    case 128: return twid[6][k];
    case 64: return twid[5][k];
    case 32: return twid[4][k];
    case 16: return twid[3][k];
    case 8: return twid[2][k];
    case 4: return twid[1][k];
    case 2: return twid[0][k];
    default:
      fprintf(stderr,"ERROR: invalid twiddlefactor index\n");
    
  };
}

/*Recursive Radix-2 Decimation in Time FFT*/
void fft(const complex float *x, complex float *X, int N, int s){

  if( N == 1 ){

    X[0] = x[0]; 
    return;

  }

  fft(x,   X,     N/2, 2*s);
  fft(x+s, X+N/2, N/2, 2*s);

  for(int k = 0; k < N/2; k++){

    complex float p = X[k];
    complex float q = gettwiddle(k,N) * X[k + N/2];
    X[k] = p + q;
    X[k + N/2] = p - q;

  }

}

void ifft(const complex float *X, complex float *x, int N){
  /*Using some extra space to avoid blowing away X*/
  complex float flipped[N];
  complex float flopped[N];

  for(int i = 0; i < N; i++){
    flipped[i] = cimag(X[i]) + creal(X[i]) * I;
  }
  fft(flipped,flopped,N,1);

  for(int i = 0; i < N; i++){
    x[i] = (cimag(flopped[i]) + creal(flopped[i]) * I) / N;
  }
}

#ifdef FFT_KERNEL_TEST
void fft_test(){

  complex float x[SIG_LEN];
  complex float fftX[NUM_BINS]; 
  complex float ifftx[NUM_BINS]; 

  float step = 17.0 * TwoPi / (float)SIG_LEN;
  float step2 = 39.0 * TwoPi / (float)SIG_LEN;
  float rad = 0.0;
  float rad2 = 0.0;
  for(int i = 0; i < SIG_LEN; i++){
    x[i] = 0.75 * sin(rad) + 0.25 * sin(rad2 + 0.75);
    rad += step;
    rad2 += step2;
  }
  
  struct timespec start;
  struct timespec end;
  clock_gettime(CLOCK_REALTIME,&start);
  fft(x,fftX,NUM_BINS,1);
  ifft(fftX,ifftx,NUM_BINS);
  clock_gettime(CLOCK_REALTIME,&end);
  printf("FFT Time: %lu\n",end.tv_nsec-start.tv_nsec);

  FILE *wave = fopen("wav.out","w");
  FILE *fft = fopen("fft.out","w");
  FILE *ifft = fopen("ifft.out","w");
  for(int i = 0; i < SIG_LEN; i++){
    fprintf(wave,"%d %f\n",i,cabs(x[i]));
  }
  
  for(int i = 0; i < NUM_BINS / 2; i++){
    fprintf(fft,"%d %f\n",i,cabs(fftX[i]));
  }
  
  for(int i = 0; i < SIG_LEN; i++){
    fprintf(ifft,"%d %f\n",i,cabs(ifftx[i]));
  }

}

int main(int argc, char *argv[]){
  fft_test();
}
#endif
