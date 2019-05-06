#include <stdio.h>
#include <stdlib.h>

#include "module.h"
#include "wave.h"
#include "sbuf.h"
#include "sine.h"


module *m;
wave *w;
sbuf *sine;

int main( int argc, char * argv[]){

  /*Make standard out unbuffered for raw output*/
  setbuf(stdout,NULL);

  /*Create module*/
  mod_init(&m);

  /*Create wave*/
  wave_init(&w);

  /*Make module wave*/
  mod_mkwave(m,w);

  /*Add wavetable to wave module*/
  sbuf_init(&sine,WTAB_SIN_LEN,wtab_sin);
  wave_mkwtab(w,sine);


  while(1){

    sample ns;

    ns = m->next((void*)(m->mod));

    fwrite(&ns,sizeof(sample),1,stdout);

  }

}
