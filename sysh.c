#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "wave.h"
#include "sbuf.h"
#include "sine.h"
#include "wavloader.h"


module *m;
wave *w;
sbuf *sine;

int main( int argc, char * argv[]){

  wavfile wav;
  wavloader_load(&wav, "sineout.wav");

  /*Make standard out unbuffered for raw output*/
  setbuf(stdout,NULL);

  /*Create module*/
  mod_init(&m);

  /*Create wave*/
  wave_init(&w);

  /*Make module wave*/
  mod_mkwave(m,w);

  /*Add wavetable to wave module*/
  wavetable sine;
  memset(&sine,0,sizeof(wavetable));
  wavtab_from_wavfile(&sine, &wav);
  wave_mkwtab(w,&sine);
 
  wave_freq(w,440);

  fprintf(stderr,"step is %d\n",w->STEP);

  while(1){

    sample ns;

    ns = m->next((void*)(m->mod));

    fwrite(&ns,sizeof(sample),1,stdout);

  }

}
