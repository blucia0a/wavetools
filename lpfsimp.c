#include <stdlib.h>

#include "module.h"
#include "lpfsimp.h"

sample lpfsimp_next(void *vlpf){

  lpfsimp *lpf = (lpfsimp *)vlpf;
  sample nxt = 
    lpf->in->next(lpf->in->mod);
  return nxt;

}

void lpfsimp_init(lpfsimp **fs){

  (*fs) = (lpfsimp *) calloc(1, sizeof(lpfsimp));
  (*fs)->resonance = 1.0;
  (*fs)->cutoff = 20000.; 
}

void lpfsimp_setin(lpfsimp *fs, module *in){
  fs->in = in;
}

void mod_mklpfsimp(module *m, lpfsimp *fs){

  m->mod = (void *)fs;
  fs->mod = m;
  m->next = lpfsimp_next;

}
