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
  wavetable *cello = wavetable_new("/home/blucia/cvsandbox/AKWF-FREE/AKWF/AKWF_cello/AKWF_cello_0018.wav");
  //wavetable *meowtab = wavetable_new("wavlib/meow2.wav");
  module *mw1 = wave_new( sine, 440);
  module *mw2 = wave_new( sine, 235);
  module *mw3 = wave_new( sine, 100);
  module *mw5 = wave_new( sine, 125);
  module *mw6 = wave_new( sine, 248);
  module *mw7 = wave_new( sine, 390);
  module *mw4 = noise_new( );



  module *mlfow2 = wave_new( sine, 200);
  wave_setfreqmod(mw1->mod, mlfow2);



  module *mx = mixn_new();
  mixn_addin(mx->mod,mw1);
  mixn_addin(mx->mod,mw2);
  mixn_addin(mx->mod,mw3);
  mixn_addin(mx->mod,mw4);
  module *mlfo = wave_new( sine, 0.07);
  module *mlpf = lpfsimp_new(220., 1.0);
  lpfsimp_setin(mlpf->mod,mx);
  lpfsimp_setcutoffmod(mlpf->mod,mlfo);

  module *mx2 = mixn_new();
  mixn_addin(mx2->mod,mw5);
  mixn_addin(mx2->mod,mw6);
  mixn_addin(mx2->mod,mw7);
  module *mlfo2 = wave_new( sine, 0.03);
  module *mlpf2 = lpfsimp_new(320., 1.4);
  lpfsimp_setin(mlpf2->mod,mx2);
  lpfsimp_setcutoffmod(mlpf2->mod,mlfo2);

  module *mx3 = mixn_new();
  mixn_addin(mx3->mod,mlpf);
  mixn_addin(mx3->mod,mlpf2);


  module *mo = out_new();
  out_setin(mo->mod,mx3);

  while(1){

    mo->next((void*)mo->mod);

  }

}
