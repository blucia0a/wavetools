#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>

#include "module.h"
#include "mixn.h"

sample mixn_next(void *v){
  
  mixn *m = (mixn *)v;

  sample r = 0;
  for(int i = 0; i < m->nextin; i++){

    sample ri = m->ins[i]->next(m->ins[i]->mod) / m->nextin;
    r += ri;

  } 
  return r;

}


void mixn_init(mixn **w){
  
  (*w)      = (mixn   *)calloc(1, sizeof(mixn)); 
  (*w)->ins = (module **)calloc(MIXN_DEFAULT_NUM_INS, sizeof(module*));
  (*w)->numins = MIXN_DEFAULT_NUM_INS;
  (*w)->nextin = 0;

}

void mixn_addin(mixn *mx, module *in){

  /*Make space for more inputs if necessary*/
  if( mx->nextin == mx->numins ){
    mx->ins = realloc(mx->ins, mx->numins * 2);
    mx->numins *= 2;
  }

  /*Add the next input and bmp the number of inputs*/
  mx->ins[ mx->nextin ] = in;
  mx->nextin++;
}

void mod_mkmixn(module *m, mixn *mx){

  m->mod = (void *)mx;
  mx->mod = m;
  m->next = mixn_next;

}
