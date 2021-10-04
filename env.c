#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "module.h"
#include "env.h"

sample env_next(void *v){
  
  env *e = (env*)v;

  sample r = 1.0;

  return r;

}

void env_init(env **e){
  
  *e = (env *)malloc(sizeof(env)); 

}

void env_envelope(env *e, float a, float d, float s, float r, size_t srate){

  e->srate = srate;

  e->A = a; 
  e->As = a * srate; 

  e->D = d; 
  e->Ds = d * srate; 

  e->S = s; 
  e->Ss = s * srate; 

  e->R = r; 
  e->Rs = r * srate; 

}

void mod_mkenv(module *m, env *e){

  m->mod = (void *)e;
  e->mod = m;
  m->next = env_next;

}

module *env_new( float a, float d, float s, float r, size_t srate){

  module *m;
  env *e;
  
  /*Create module*/
  mod_init(&m);

  /*Create env*/
  env_init(&e);

  /*Make module env*/
  mod_mkenv(m,e);
 
  /*Create envelop parameters*/
  env_envelope(e, a, d, s, r, srate);
 
  return m;

}
