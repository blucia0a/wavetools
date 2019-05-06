#ifndef _wave_h_
#define _wave_h_

#include "sample.h"
#include "sbuf.h"
#include "module.h"

typedef struct wave_s{

  module *mod; /*pointer to container module*/
  sbuf *s; /*stores the samples we report*/

  /*wavetable properties*/
  
  size_t F;
  size_t A;

} wave;

sample wave_next(void *);  
void wave_init(wave **w);/*create a wave structure*/
void wave_setwavetable(wave **w, sbuf *s);
void wave_mkwtab(wave *w, sbuf *s);
void mod_mkwave(module *m, wave *w);/*set m->mod = new wave; set mod->next = wave_next*/

#endif
