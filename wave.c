#include <stdlib.h>
#include <stdio.h>

#include "module.h"
#include "wave.h"

sample wave_next(void *v){
  
  wave *w = (wave*)v;
  return sbuf_getn(w->s,w->STEP);

}

void wave_freq(wave *w, size_t f){
  w->F = f;
  /*        44100    / 440  * 44100   */
  w->STEP = w->s->sz * w->F / SRATE;
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
