/*data structure for a wave file containing PCM audio data*/
typedef struct wavfile{
  unsigned chunkid;
  unsigned chunksz;
  unsigned format;

  unsigned fmtchunkid;
  unsigned fmtchunksz;
  unsigned short audiofmt;
  unsigned short channels;
  unsigned samplerate;
  unsigned byterate; //rate * channels * bitspersample / 8
  unsigned short blockalign; //channels * bitspersample
  unsigned short bitspersample;

  unsigned datachunkid;
  unsigned datachunksz; //samples * channels * bitspersample/8
  char *data; 
} wavfile;


int wavloader_load(wavfile *wav, char *wavfile);
