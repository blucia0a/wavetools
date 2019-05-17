#ifndef _lpfsimp_h_
#define _lpfsimp_h_

#include "sample.h"
#include "module.h"

typedef struct lpfsimp_s{

  module *mod; /*pointer to container module*/
  module *in;

  float resonance;
  float cutoff;

} lpfsimp;

sample lpfsimp_next(void *);  
void lpfsimp_init(lpfsimp **fs);/*create a filter structure*/
void lpfsimp_setin(lpfsimp *fs, module *in);
void mod_mklpfsimp(module *m, lpfsimp *fs);/*setup module container*/



#endif
