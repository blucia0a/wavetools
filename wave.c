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
  (*w)->cur = 0;
  (*w)->F = 1;

  /*cannot set STEP until wavetable is defined*/
}

void wave_mkwtab(wave *w, wavetable *wt){

  w->wt = wt; 
  w->STEP = w->wt->len * w->F / w->wt->samplerate;

}

void mod_mkwave(module *m, wave *w){

  m->mod = (void *)w;
  w->mod = m;
  m->next = wave_next;

}

module *wave_new( wavetable *wtab, unsigned freq ){

  module *m;
  wave *w;
  
  /*Create module*/
  mod_init(&m);

  /*Create wave*/
  wave_init(&w);

  /*Make module wave*/
  mod_mkwave(m,w);
  
  wave_mkwtab(w,wtab);
 
  wave_freq(w,freq);

  return m;

}
