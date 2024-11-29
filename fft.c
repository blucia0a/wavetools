#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "module.h"
#include "fft.h"
#include "fft_kernel.h"

sample fft_next(void *vlpf){

  fft *lpf = (fft *)vlpf;

  sample in = 
    lpf->in->next(lpf->in->mod);

  /*TODO: 
  1) count number of samples up to FFT_SIZE
  2) store these in fft->sampbuff[]
  3) when exceeds FFT_SIZE, compute fft
  4) do something via a side chain with fft data
  5) return in as next sample
  */

  return (sample)in;

}

void fft_updateparams(fft *fs){


}

void fft_init(fft **fs){

  (*fs) = (fft *) calloc(1, sizeof(fft));

  (*fs)->samplerate = 44100;

  memset((*fs)->sampbuff,0,FFT_SIZE);

  fft_updateparams(*fs);

}

void fft_setin(fft *fs, module *in){
  fs->in = in;
}

void mod_mkfft(module *m, fft *fs){

  m->mod = (void *)fs;
  fs->mod = m;
  m->next = fft_next;

}

module *fft_new(){
 
  module *mfft1;
  fft *fft1; 

  mod_init(&mfft1);
  fft_init(&fft1);
  mod_mkfft(mfft1,fft1);

  return mfft1;

}
