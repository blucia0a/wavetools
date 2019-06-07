#ifndef _env_h_
#define _env_h_

#include "sample.h"
#include "module.h"

typedef struct env_s{

  module *mod; /*pointer to container module*/

  /*Sample rate*/
  size_t srate;

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
void env_init(env **e);/*create a env structure*/
void env_envelope(env * e, float a, float d, float s, float r, size_t srate);/*create a env structure*/
void mod_mkenv(module *m, env *e);/*set m->mod = new env; set mod->next = env_next*/
module *env_new( float a, float d, float s, float r, size_t srate );

#endif
