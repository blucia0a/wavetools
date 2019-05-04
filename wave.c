#include "module.h"
#include "wave.h"

void wave_next(void*){

}

void wave_init(wave **w){
  
  *w = (wave *)malloc(sizeof(wave)); 

}

void mod_mkwave(mod *m, wave *w){

  m->mod = (void *)w;
  w->mod = m;
  m->next = wave_next;

}
