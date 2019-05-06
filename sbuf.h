#ifndef _sbuf_h_
#define _sbuf_h_

#include <stddef.h>
#include "sample.h"

typedef struct sbuf{

  sample *buf;
  size_t sz;  
  size_t cur;

} sbuf;

void sbuf_init(sbuf **s, size_t sz, sample *data);
void sbuf_createbuf(sbuf *s,size_t sz);
void sbuf_put(sbuf *s);
sample sbuf_get(sbuf *s);

#endif
