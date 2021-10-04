#ifndef _wavetable_h_
#define _wavetable_h_
#include <stddef.h>
#include "wavloader.h"
#include "sample.h"

typedef struct wavetable{

  unsigned samplerate; /*in Hz*/
  unsigned short channels;
  unsigned short samplesz; /*in bytes*/
  size_t len; /*#samples * #channels * samplesz*/
  sample *data; 

} wavetable;

sample wavetable_getn(wavetable *wt,unsigned n);

void wavtab_from_wavfile(wavetable *wt,wavfile *wf);
/*Constructor*/
wavetable * wavetable_new(char *fname);
#endif
