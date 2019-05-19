#ifndef _mix_h_
#define _mix_h_

#include "sample.h"
#include "module.h"

typedef struct out_s{

  module *mod; /*pointer to container module*/
  module *in;  /*pointer to incoming module*/

  sample *obuf;
  size_t obufsz;
  size_t i;  

  void (*outf)(sample *,size_t); 

} out;

sample out_next(void *);  
void out_init(out **o);/*create a wave structure*/
void out_setin(out *o, module *in);
void out_setoutput(out *o, void (*outf)(sample *, size_t) );
void mod_mkout(module *m, out *o);/*set m->mod = new wave; set mod->next = wave_next*/
void out_stdout_outf(sample *, size_t);
#endif
