#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "wave.h"
#include "mix.h"
#include "sbuf.h"
#include "sine.h"
#include "wavloader.h"


module *mw1;
module *mw2;
module *mx1;

wave *w1;
wave *w2;
mix *x1;


int main( int argc, char * argv[]){

  wavfile wav;
  wavloader_load(&wav, "sine.wav");

  /*Make standard out unbuffered for raw output*/
  setbuf(stdout,NULL);

  /*Create module*/
  mod_init(&mw1);
  /*Create module*/
  mod_init(&mw2);
  /*Create module*/
  mod_init(&mx1);

  /*Create wave*/
  wave_init(&w1);
  /*Create wave*/
  wave_init(&w2);
  /*create mix*/
  mix_init(&x1);

  /*Make module wave*/
  mod_mkwave(mw1,w1);
  /*Make module wave*/
  mod_mkwave(mw2,w2);
  /*make module mix*/
  mod_mkmix(mx1,x1);

  /*Add wavetable to wave module*/
  wavetable sine;
  memset(&sine,0,sizeof(wavetable));
  wavtab_from_wavfile(&sine, &wav);

  wave_mkwtab(w1,&sine);
  wave_mkwtab(w2,&sine);
 
  wave_freq(w1,440);
  wave_freq(w2,640);

  mix_setins(x1,mw1,mw2);

  //fprintf(stderr,"step is %d\n",w->STEP);

  while(1){

    sample ns;

    ns = mx1->next((void*)mx1->mod);

    fwrite(&ns,sizeof(sample),1,stdout);

  }

}
