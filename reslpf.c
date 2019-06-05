#include <stdlib.h>
#include <math.h>

#include "module.h"
#include "reslpf.h"

sample reslpf_next(void *vlpf){

  reslpf *lpf = (reslpf *)vlpf;

  sample in = 
    lpf->in->next(lpf->in->mod);

  float delta = in - lpf->lastOutput;

  float out = lpf->lastOutput + delta * lpf->cutoff;

  lpf->lastOutput = (sample)out;

  return (sample)out;

}

void reslpf_updateparams(reslpf *fs){


}

void reslpf_init(reslpf **fs){

  (*fs) = (reslpf *) calloc(1, sizeof(reslpf));

  (*fs)->samplerate = 44100;

  (*fs)->resonance = 0.125;
  (*fs)->cutoff = 0.125; 
  (*fs)->momentum = 0.; 


}

void reslpf_setin(reslpf *fs, module *in){
  fs->in = in;
}

void reslpf_setres(reslpf *fs, float res){
  fs->resonance = res;
}

void reslpf_setcutoff(reslpf *fs, float cutoff){
  fs->cutoff = cutoff;
}

void mod_mkreslpf(module *m, reslpf *fs){

  m->mod = (void *)fs;
  fs->mod = m;
  m->next = reslpf_next;

}

module *reslpf_new(float cutoff, float resonance){
 
  module *mlpf1;
  reslpf *lpf1; 

  mod_init(&mlpf1);
  reslpf_init(&lpf1);
  mod_mkreslpf(mlpf1,lpf1);

  reslpf_setres(lpf1,resonance);
  reslpf_setcutoff(lpf1,cutoff);
  return mlpf1;

}
