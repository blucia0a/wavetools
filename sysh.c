#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "lpfsimp.h"
#include "mixn.h"
#include "mix.h"
#include "sine.h"
#include "wave.h"
#include "wavloader.h"


module *mw1;
wave *w1;
module *mw2;
wave *w2;
module *mw3;
wave *w3;
module *mw4;
wave *w4;

module *mlpf1;
lpfsimp *lpf1;

module *mx1;
mixn *x1;



int main( int argc, char * argv[]){

  wavfile wav;
  wavloader_load(&wav, "wavlib/sine.wav");

  /*Make standard out unbuffered for raw output*/
  setbuf(stdout,NULL);

  /*Create module*/
  mod_init(&mw1);
  /*Create wave*/
  wave_init(&w1);
  /*Make module wave*/
  mod_mkwave(mw1,w1);
  
  /*Create module*/
  mod_init(&mw2);
  /*Create wave*/
  wave_init(&w2);
  /*Make module wave*/
  mod_mkwave(mw2,w2);
  
  /*Create module*/
  mod_init(&mw3);
  /*Create wave*/
  wave_init(&w3);
  /*Make module wave*/
  mod_mkwave(mw3,w3);
  
  /*Create module*/
  mod_init(&mw4);
  /*Create wave*/
  wave_init(&w4);
  /*Make module wave*/
  mod_mkwave(mw4,w4);

  /*Create module*/
  mod_init(&mlpf1);
  /*create mixn*/
  lpfsimp_init(&lpf1);
  /*make module mix*/
  mod_mklpfsimp(mlpf1,lpf1);
  
  /*Create module*/
  mod_init(&mx1);
  /*create mixn*/
  mixn_init(&x1);
  /*make module mix*/
  mod_mkmixn(mx1,x1);


  /*Add wavetable to wave module*/
  wavetable sine;
  memset(&sine,0,sizeof(wavetable));
  wavtab_from_wavfile(&sine, &wav);

  wave_mkwtab(w1,&sine);
  wave_mkwtab(w2,&sine);
  wave_mkwtab(w3,&sine);
  wave_mkwtab(w4,&sine);
 
  wave_freq(w1,230);
  wave_freq(w2,1000);
  wave_freq(w3,440);
  wave_freq(w4,550);

  mixn_addin(x1,mw1);
  mixn_addin(x1,mw2);
  mixn_addin(x1,mw3);
  mixn_addin(x1,mw4);

  lpfsimp_setres(lpf1,1.4);
  lpfsimp_setcutoff(lpf1,440.);
  lpfsimp_setin(lpf1,mx1);

  //fprintf(stderr,"step is %d\n",w->STEP);

  while(1){

    sample ns;

    ns = mlpf1->next((void*)mlpf1->mod);
    //ns = mx1->next((void*)mx1->mod);

    fwrite(&ns,sizeof(sample),1,stdout);

  }

}
