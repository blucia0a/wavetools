void sbuf_init(sbuf **s){
  *s = (sbuf*)malloc(sizeof(sbuf));
}

void sbuf_createbuf(sbuf *s,size_t sz){
  s->buf = (sample *)malloc(sizeof(sample));
  s->sz = sz;
}

void sbuf_put(sbuf *s){

}

void sbuf_get(sbuf *s){

}
