#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "module.h"
#include "amp.h"

sample amp_next(void *v){
  
  amp *a = (amp*)v;
  amp_modulate(a);

  sample r = a->in->next(a->in->mod);

  return r * a->level;

}


void amp_setin(amp *a, module *amod){
  a->in = amod;
}

void amp_init(amp **w){
  
  *w = (amp *)malloc(sizeof(amp)); 
  /*cannot set STEP until amptable is defined*/
}

void amp_modulate(amp *a){

  if(a->ampmod){

    sample ams = a->ampmod->next(a->ampmod->mod);
    float amod = SAMP2SCALE(ams);

    /*TODO: memoize the shifted base value*/
    a->level = a->base_level - 0.5 * a->base_level + amod * a->base_level;

  }

}

void amp_setampmod(amp *w, module *amod){

  w->ampmod = amod;

}

void mod_mkamp(module *m, amp *w){

  m->mod = (void *)w;
  w->mod = m;
  m->next = amp_next;

}

module *amp_new( float level ){

  module *m;
  amp *w;
  
  /*Create module*/
  mod_init(&m);

  /*Create amp*/
  amp_init(&w);
 
  w->level = level;
  w->base_level = level;

  /*Make module amp*/
  mod_mkamp(m,w);
 
  return m;

}
