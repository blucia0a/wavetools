#ifndef _module_h_
#define _module_h_

#include "sample.h"


typedef struct module {

  sample (*next)(void *);
  void *mod;

} module;


void mod_init(module **m);

#endif
