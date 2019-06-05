#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "module.h"
#include "noise.h"

sample noise_next(void *v){

  return (sample)( rand() );

}


void noise_init(noise **n){
  
  *n = (noise *)malloc(sizeof(noise)); 

}

void mod_mknoise(module *m, noise *w){

  m->mod = (void *)w;
  w->mod = m;
  m->next = noise_next;

}

module *noise_new( ){

  srand( time(NULL) );
  module *m;
  noise *w;
  
  /*Create module*/
  mod_init(&m);

  /*Create noise*/
  noise_init(&w);

  /*Make module noise*/
  mod_mknoise(m,w);
  
  return m;

}
