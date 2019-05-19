#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "module.h"
#include "wave.h"

sample wave_next(void *v){
  
  wave *w = (wave*)v;
  sample r = 0;
  if( w->STEP >= 1. ){

    w->WAIT = 0;
    w->cur = (w->cur + (size_t)w->STEP) % w->wt->len;
  }else{

    if( w->WAIT <= 0 ){
      w->cur = (w->cur + 1) % w->wt->len;
      w->WAIT = (short) (1. / w->STEP);
    }else{
      w->WAIT--;
    }  

  }

  r = w->wt->data[w->cur];
  assert(w->cur >= 0);
  assert(w->cur < w->wt->len); 
  return r;

}

void wave_freq(wave *w, float f){
  fprintf(stderr,"%f\n",f);
  w->F = f;
  /*        44100    / 440  * 44100   */
  w->STEP = (float)(w->wt->len) * (float)(w->F) / (float)(w->wt->samplerate);
  fprintf(stderr,"set step = %f len = %f, F=%f, rate=%f\n",w->STEP,(float)(w->wt->len), (float)(w->F), (float)(w->wt->samplerate));
  w->WAIT = (short) (1. / w->STEP);
}

void wave_init(wave **w){
  
  *w = (wave *)malloc(sizeof(wave)); 
  (*w)->cur = 0;
  (*w)->F = 1;

  /*cannot set STEP until wavetable is defined*/
}

void wave_mkwtab(wave *w, wavetable *wt){

  w->wt = wt; 
  w->STEP = (float)(w->wt->len) * (float)(w->F) / (float)(w->wt->samplerate);

}

void mod_mkwave(module *m, wave *w){

  m->mod = (void *)w;
  w->mod = m;
  m->next = wave_next;

}

module *wave_new( wavetable *wtab, float freq ){

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
