#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "module.h"
#include "out.h"

#define DEFAULT_OBUF_SZ 2048

sample out_next(void *v){
  
  out *o = (out *)v;

  sample r = o->in->next(o->in->mod);

  o->obuf[ o->i++ ] = r;

  if( o->i >= o->obufsz ){
    o->outf( o->obuf, o->obufsz );
    o->i = 0;
  }

}


void out_init(out **o){
  
  *o = (out *)malloc(sizeof(out)); 
  (*o)->obuf = calloc(DEFAULT_OBUF_SZ,sizeof(sample));
  (*o)->obufsz = DEFAULT_OBUF_SZ;
  (*o)->i = 0;
  (*o)->outf = out_stdout_outf;
}

void out_setin(out *o, module *in){

  o->in = in;

}

void out_setoutput(out *o, void (*outf)(sample *, size_t)){

  o->outf = outf;

}

void mod_mkout(module *m, out *o){

  m->mod = (void *)o;
  o->mod = m;
  m->next = out_next;

}

void out_stdout_outf(sample *b, size_t sz){
  fwrite(b,sizeof(sample),sz,stdout);
}

