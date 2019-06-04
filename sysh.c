#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "out.h"
#include "noise.h"
#include "reslpf.h"
#include "lpfsimp.h"
#include "mixn.h"
#include "mix.h"
#include "sine.h"
#include "wave.h"
#include "wavloader.h"

 /*Synth sketch
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

int main( int argc, char * argv[]){

  /*Make standard out unbuffered for raw output*/
  setbuf(stdout,NULL);

  wavetable *sine = wavetable_new("wavlib/sine.wav");
  //wavetable *noise = wavetable_new("/home/blucia/cvsandbox/AKWF-FREE/AKWF/AKWF_cello/AKWF_cello_0018.wav");
  //wavetable *meowtab = wavetable_new("wavlib/meow2.wav");
  module *mw1 = wave_new( sine, 220);
  module *mw2 = wave_new( sine, 440);
  module *mw3 = wave_new( sine, 880);
  module *mw4 = noise_new( );
  module *mlfo = wave_new( sine, 0.1);
  //module *mw4 = wave_new( sine, 1340);


  module *mx = mixn_new();
  mixn_addin(mx->mod,mw1);
  mixn_addin(mx->mod,mw2);
  mixn_addin(mx->mod,mw3);
  mixn_addin(mx->mod,mw4);


  module *mlpf = lpfsimp_new(880., 1.0);
  lpfsimp_setin(mlpf->mod,mx);
  lpfsimp_setcutoffmod(mlpf->mod,mlfo);


  module *mo = out_new();
  out_setin(mo->mod,mlpf);

  while(1){

    mo->next((void*)mo->mod);

  }

}
