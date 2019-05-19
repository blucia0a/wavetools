#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wavloader.h"
#include "wavetable.h"


void wavtab_from_wavfile(wavetable *wt, wavfile *wf){

  assert(wt);
  assert(wf);
  wt->samplerate = wf->samplerate;
  wt->channels = wf->channels;
  wt->samplesz = wf->bitspersample / 8;

  /*number of bytes of audio data / size of sample*/
  wt->len = wf->datachunksz / wt->samplesz; 

  fprintf(stderr,"rate: %u chan: %u sampsz: %u len %u\n",wt->samplerate,wt->channels,wt->samplesz,wt->len);

  if(wt->data){
    /*Free the previous wavetable's data*/
    free(wt->data);
  } 

  /*Can't create a wavetable from a null data buffer*/
  assert(wf->data);

  /*Careful if source sample size is not the same as target*/
  wt->data = (sample *)malloc(wt->len * sizeof(sample));
  
  signed short *s = (signed short *)wf->data;
  for(int i = 0; i < wt->len; i++){
    wt->data[i] = *s;
    s++;
  } 
  

}

wavetable * wavetable_new(char *fname){
  
  wavfile *wav = (wavfile *)calloc(1,sizeof(wavfile));
  wavetable *tab = (wavetable *)calloc(1,sizeof(wavetable));
  wavloader_load(wav, fname);
  wavtab_from_wavfile(tab, wav);
  return tab;
}
