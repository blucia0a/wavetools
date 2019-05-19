#include <stdlib.h>
#include <math.h>

#include "module.h"
#include "lpfsimp.h"

sample lpfsimp_next(void *vlpf){

  lpfsimp *lpf = (lpfsimp *)vlpf;
  sample in = 
    lpf->in->next(lpf->in->mod);


  float out = 
  lpf->a1 * (float)in + 
  lpf->a2 * lpf->prevIn[0] + 
  lpf->a3 * lpf->prevIn[1] - 
  lpf->b1 * lpf->prevOut[0] - 
  lpf->b2 * lpf->prevOut[1];

  lpf->prevOut[1] = lpf->prevOut[0];
  lpf->prevOut[0] = out;

  lpf->prevIn[1] = lpf->prevIn[0];
  lpf->prevIn[0] = in;

  return (sample)out;

}

void lpfsimp_updateparams(lpfsimp *fs){

 fs->c = 1.0 / tan(M_PI * fs->cutoff / fs->samplerate);
 fs->a1 = 1.0 / ( 1.0 + fs->resonance * fs->c + fs->c * fs->c);
 fs->a2 = 2 * fs->a1;
 fs->a3 = fs->a1;
 fs->b1 = 2.0 * ( 1.0 - fs->c * fs->c) * fs->a1;
 fs->b2 = ( 1.0 - fs->resonance * fs->c + fs->c * fs->c) * fs->a1;

}

void lpfsimp_init(lpfsimp **fs){

  (*fs) = (lpfsimp *) calloc(1, sizeof(lpfsimp));

  (*fs)->samplerate = 44100;

  (*fs)->resonance = 1.;
  (*fs)->cutoff = 20000.; 

  lpfsimp_updateparams(*fs);

  (*fs)->prevIn[0] = 0.;
  (*fs)->prevIn[1] = 0.;
  (*fs)->prevOut[0] = 0.;
  (*fs)->prevOut[1] = 0.;
}

void lpfsimp_setin(lpfsimp *fs, module *in){
  fs->in = in;
}

void lpfsimp_setres(lpfsimp *fs, float res){
  fs->resonance = res;
  lpfsimp_updateparams(fs); 
}

void lpfsimp_setcutoff(lpfsimp *fs, float cutoff){
  fs->cutoff = cutoff;
  lpfsimp_updateparams(fs); 
}

void mod_mklpfsimp(module *m, lpfsimp *fs){

  m->mod = (void *)fs;
  fs->mod = m;
  m->next = lpfsimp_next;

}

module *lpfsimp_new(float cutoff, float resonance){
 
  module *mlpf1;
  lpfsimp *lpf1; 

  mod_init(&mlpf1);
  lpfsimp_init(&lpf1);
  mod_mklpfsimp(mlpf1,lpf1);

  lpfsimp_setres(lpf1,resonance);
  lpfsimp_setcutoff(lpf1,cutoff);
  return mlpf1;

}
