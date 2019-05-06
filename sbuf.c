#include <stdlib.h>
#include <stdio.h>


#include "sample.h"
#include "sbuf.h"

void sbuf_init(sbuf **s, size_t sz, sample *data){

  *s = (sbuf*)malloc(sizeof(sbuf));

  (*s)->buf = (sample *)malloc(sizeof(sample) * sz);
  (*s)->sz = sz;
  (*s)->cur = 0;

  for(int i = 0; i < sz; i++){

    (*s)->buf[i] = data[i];

  }
  fprintf(stderr,"created a buffer with %u elems\n",sz);

}

void sbuf_put(sbuf *s){

}

sample sbuf_get(sbuf *s){

  sample r = s->buf[s->cur];
  s->cur = (s->cur + 1) % s->sz;
  return r; 

}

sample sbuf_getn(sbuf *s, size_t n){

  sample r = s->buf[s->cur];
  s->cur = (s->cur + n) % s->sz;
  return r; 

}
