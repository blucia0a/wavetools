#ifndef _fft_h_
#define _fft_h_

#include "sample.h"
#include "module.h"

#define FFT_SIZE 1024
typedef struct fft_s{

  module *mod; /*pointer to container module*/
  module *in;

  unsigned samplerate;

  /*previous ins and out*/ 
  float sampbuff[FFT_SIZE];

} fft;

sample fft_next(void *);  
void fft_init(fft **fs);/*create a filter structure*/
void fft_setin(fft *fs, module *in);
void fft_updateparams(fft *fs);
void mod_mkfft(module *m, fft *fs);/*setup module container*/

module *fft_new();


#endif
