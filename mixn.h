#ifndef _mixn_h_
#define _mixn_h_

#include "sample.h"
#include "module.h"

#define MIXN_DEFAULT_NUM_INS 4
typedef struct mixn_s{

  module *mod; /*pointer to container module*/
  module **ins;
  size_t nextin;
  size_t numins;

  /*wavetable properties*/

} mixn;

sample mix_next(void *);  
void mixn_init(mixn **mx);/*create a wave structure*/
void mixn_addin(mixn *mx, module *in);
void mod_mkmixn(module *m, mixn *mx);/*set m->mod = new wave; set mod->next = wave_next*/
module *mixn_new();
#endif
