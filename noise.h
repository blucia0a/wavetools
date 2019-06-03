#ifndef _noise_h_
#define _noise_h_

#include "sample.h"
#include "module.h"

typedef struct noise_s{

  module *mod; /*pointer to container module*/

} noise;

sample noise_next(void *);  
void noise_init(noise **n);/*create a wave structure*/
void mod_mknoise(module *m, noise *n);/*set m->mod = new wave; set mod->next = wave_next*/
module *noise_new( );

#endif
