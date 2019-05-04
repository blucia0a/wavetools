#ifndef _sbuf_h_
#define _subf_h_

#include <stddef.h>
#include "sample.h"


typedef struct sbuf_s{

  sample *buf;
  size_t sz;  

} sbuf;

void sbuf_init(sbuf *s);
void sbuf_createbuf(sbuf *s,size_t sz);
void sbuf_put(sbuf *s);
void sbuf_get(sbuf *s);

#endif
