#ifndef _mix_h_
#define _mix_h_

#include "sample.h"
#include "module.h"

typedef struct mix_s{

  module *mod; /*pointer to container module*/
  module *in1;
  module *in2;

  /*wavetable properties*/

} mix;

sample mix_next(void *);  
void mix_init(mix **mx);/*create a wave structure*/
void mix_setins(mix *mx, module *in1, module *in2);
void mod_mkmix(module *m, mix *mx);/*set m->mod = new wave; set mod->next = wave_next*/
module *mix_new();

#endif
