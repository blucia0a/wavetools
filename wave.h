#ifndef _wave_h_
#define _wave_h_

#include "sample.h"
#include "module.h"
#include "wavetable.h"

typedef struct wave_s{

  module *mod; /*pointer to container module*/
  wavetable *wt; /*either a wavloader or an sbuf*/ 

  /*wavetable properties*/
  
  float F;
  size_t A;
  float STEP; //= w->T / w->F * SRATE;
  short WAIT; //= 1.0 / STEP (> 1 if STEP < 1
  size_t cur;

} wave;

sample wave_next(void *);  
void wave_init(wave **w);/*create a wave structure*/
void wave_freq(wave *w, float f);
void wave_setwavetable(wave **w, wavetable *wt);
void wave_mkwtab(wave *w, wavetable *wt);
void mod_mkwave(module *m, wave *w);/*set m->mod = new wave; set mod->next = wave_next*/
module *wave_new( wavetable *wtab, float freq );

#endif
