#ifndef _env_h_
#define _env_h_

#include "sample.h"
#include "module.h"
#include "envtable.h"

typedef struct env_s{

  module *mod; /*pointer to container module*/

  /*In seconds*/
  float A;
  float D;
  float S;
  float R;

  /*In samples*/
  size_t As;
  size_t Ds;
  size_t Ss;
  size_t Rs;

} env;

sample env_next(void *);  
void env_init(env **w);/*create a env structure*/
void env_modulate(env *w);/*create a env structure*/
void env_freq(env *w, float f);
void env_setfreqmod(env *w, module *fmod);
void env_setenvtable(env **w, envtable *wt);
void env_mkwtab(env *w, envtable *wt);
void mod_mkenv(module *m, env *w);/*set m->mod = new env; set mod->next = env_next*/
module *env_new( envtable *wtab, float freq );

#endif
