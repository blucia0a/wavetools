#ifndef _wave_h_
#define _wave_h_

#include "sample.h"
#include "sbuf.h"
#include "module.h"

typedef struct wave_s{

  module *mod; /*pointer to container module*/
  sbuf *wavetable; /*stores the samples we report*/
  size_t rate; /*for sine: freq*/

} wave;

void wave_next(void *);  
void wave_init(wave *w);/*create a wave structure*/
void mod_mkwave(mod *m);/*set m->mod = new wave; set mod->next = wave_next*/

#endif
