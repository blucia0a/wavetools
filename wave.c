#include <stdlib.h>
#include <stdio.h>

#include "module.h"
#include "wave.h"

sample wave_next(void *w){

  return sbuf_get(((wave *)w)->s);

}

void wave_init(wave **w){
  
  *w = (wave *)malloc(sizeof(wave)); 

}

void wave_mkwtab(wave *w, sbuf *s){

  w->s = s; 

}

void mod_mkwave(module *m, wave *w){

  m->mod = (void *)w;
  w->mod = m;
  m->next = wave_next;

}
