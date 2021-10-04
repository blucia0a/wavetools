#ifndef _lpfsimp_h_
#define _lpfsimp_h_

#include "sample.h"
#include "module.h"

typedef struct lpfsimp_s{

  module *mod; /*pointer to container module*/
  module *in;
  module *cutoffmod_in;

  unsigned samplerate;
  float resonance;

  /*cutoff is used, base is reference to support modulation*/
  float cutoff;
  float base_cutoff;

  /*Filter alphas*/
  float a1;
  float a2;
  float a3;

  /*Filter betas*/
  float b1;
  float b2;
  
  /*derived cutoff parameter*/
  float c;

  /*previous ins and out*/ 
  float prevOut[2];
  float prevIn[2];

 

} lpfsimp;

sample lpfsimp_next(void *);  
void lpfsimp_init(lpfsimp **fs);/*create a filter structure*/
void lpfsimp_setin(lpfsimp *fs, module *in);
void lpfsimp_setcutoffmod(lpfsimp *fs, module *mod);
void lpfsimp_setres(lpfsimp *fs, float res);
void lpfsimp_setcutoff(lpfsimp *fs, float cutoff);
void lpfsimp_updateparams(lpfsimp *fs);
void mod_mklpfsimp(module *m, lpfsimp *fs);/*setup module container*/

module *lpfsimp_new(float cutoff, float resonance);


#endif
