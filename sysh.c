#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "out.h"
#include "lpfsimp.h"
#include "mixn.h"
#include "mix.h"
#include "sine.h"
#include "wave.h"
#include "wavloader.h"



int main( int argc, char * argv[]){

  /*Make standard out unbuffered for raw output*/
  setbuf(stdout,NULL);

  wavfile wav;
  wavetable sine;
  
  wavloader_load(&wav, "wavlib/sine.wav");
  memset(&sine,0,sizeof(wavetable));
  wavtab_from_wavfile(&sine, &wav);
  
  wavfile meowav;
  wavetable meowtab;

  wavloader_load(&meowav, "wavlib/meow2.wav");
  memset(&meowtab,0,sizeof(wavetable));
  wavtab_from_wavfile(&meowtab, &meowav);


  module *mo = out_new();

  module *mw1 = wave_new( &sine, 220);
  module *mw2 = wave_new( &sine, 440);
  module *mw3 = wave_new( &meowtab, 2);
  module *mw4 = wave_new( &meowtab, 40);

  module *mx = mixn_new();
  
  module *mlpf = lpfsimp_new( 440., 1.4 );

  mixn_addin(mx->mod,mw1);
  mixn_addin(mx->mod,mw2);
  mixn_addin(mx->mod,mw3);
  mixn_addin(mx->mod,mw4);

  lpfsimp_setin(mlpf->mod,mx);

  out_setin(mo->mod,mlpf);

  /*
 *
 * w1 | w2 | w3 | w4 
 * \               /
 *  ---------------
 *         |
 *         x1
 *         |
 *         lpf1
 *         |
 *         o
 */

  while(1){

    mo->next((void*)mo->mod);
/*    sample ns;

    ns = mlpf1->next((void*)mlpf1->mod);
    //ns = mx1->next((void*)mx1->mod);

    fwrite(&ns,sizeof(sample),1,stdout);
*/
  }

}
