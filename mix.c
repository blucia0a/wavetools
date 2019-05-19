#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "module.h"
#include "mix.h"

sample mix_next(void *v){
  
  mix *m = (mix *)v;

  sample r1 = m->in1->next(m->in1->mod);
  sample r2 = m->in2->next(m->in2->mod);

  return (0.5 * r1) + (0.5 * r2);

}


void mix_init(mix **w){
  
  *w = (mix *)malloc(sizeof(mix)); 

}

void mix_setins(mix *mx, module *in1, module *in2){
  mx->in1 = in1;
  mx->in2 = in2;
}

void mod_mkmix(module *m, mix *mx){

  m->mod = (void *)mx;
  mx->mod = m;
  m->next = mix_next;

}

module *mix_new(){

  module *m;
  mix *x;
  mod_init(&m);
  mix_init(&x);
  mod_mkmix(m,x);
  return m;

}
