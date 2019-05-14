#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "module.h"
#include "wave.h"

sample wave_next(void *v){
  
  wave *w = (wave*)v;

  sample r = w->wt->data[w->cur];
  w->cur = (w->cur + w->STEP) % w->wt->len;

  assert(w->cur >= 0);
  assert(w->cur < w->wt->len); 
  return r;

}

void wave_freq(wave *w, size_t f){
  w->F = f;
  /*        44100    / 440  * 44100   */
  w->STEP = w->wt->len * w->F / w->wt->samplerate;
}

void wave_init(wave **w){
  
  *w = (wave *)malloc(sizeof(wave)); 

}

void wave_mkwtab(wave *w, wavetable *wt){

  w->wt = wt; 

}

void mod_mkwave(module *m, wave *w){

  m->mod = (void *)w;
  w->mod = m;
  m->next = wave_next;

}
