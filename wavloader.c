#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wavloader.h"

int wavloader_load(wavfile *wav, char *wavfile){

  FILE *WAV = fopen(wavfile, "r");

  /*Read header*/
  fread(&wav->chunkid,1,sizeof(unsigned),WAV);
  fread(&wav->chunksz,1,sizeof(unsigned),WAV);
  fread(&wav->format,1,sizeof(unsigned),WAV);

  /*Big endian "RIFF"*/
  if(wav->chunkid != 0x46464952){
    fprintf(stderr,"expected 0x52494646, got %x\n",wav->chunkid);
    return -1;
  }
  
  if(wav->format != 0x45564157){
    fprintf(stderr,"expected 0x57415645, got %x\n",wav->format);
    return -1;
  }
  
  fread(&wav->fmtchunkid,1,sizeof(unsigned),WAV);

  /*Big endian "fmt "*/
  if(wav->fmtchunkid != 0x20746d66){
    fprintf(stderr,"expected 0x666d7420, got %x\n",wav->fmtchunkid);
    return -1;
  }

  fread(&wav->fmtchunksz,1,sizeof(unsigned),WAV);
  fread(&wav->audiofmt,1,sizeof(unsigned short),WAV);
  fread(&wav->channels,1,sizeof(unsigned short),WAV);
  fread(&wav->samplerate,1,sizeof(unsigned),WAV);
  fread(&wav->byterate,1,sizeof(unsigned),WAV);
  fread(&wav->blockalign,1,sizeof(unsigned short),WAV);
  fread(&wav->bitspersample,1,sizeof(unsigned short),WAV);
  
  fread(&wav->datachunkid,1,sizeof(unsigned),WAV);
  fread(&wav->datachunksz,1,sizeof(unsigned),WAV);
  wav->data = (char *)malloc(wav->datachunksz);
  fread(wav->data,wav->datachunksz,sizeof(char),WAV);
  fprintf(stderr,"loaded %u bytes of audio data\n",wav->datachunksz);

}
