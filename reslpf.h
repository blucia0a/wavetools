#ifndef _reslpf_h_
#define _reslpf_h_

#include "sample.h"
#include "module.h"

typedef struct reslpf_s{

  module *mod; /*pointer to container module*/
  module *in;

  unsigned samplerate;
  float resonance;
  float cutoff;
  float momentum;

  sample lastOutput;

} reslpf;

sample reslpf_next(void *);  
void reslpf_init(reslpf **fs);/*create a filter structure*/
void reslpf_setin(reslpf *fs, module *in);
void reslpf_setres(reslpf *fs, float res);
void reslpf_setcutoff(reslpf *fs, float cutoff);
void mod_mkreslpf(module *m, reslpf *fs);/*setup module container*/

module *reslpf_new(float cutoff, float resonance);


#endif
