#ifdef _module_h_
#define _module_h_

#include "sample.h"
#include "sbuf.h"
//#include "ctrlr.h"

typedef struct module_s {

  sample (*next)(void *);

  /*TODO:forward compatibility for controllers*/
  //ctrlr *ctrl;
  
  void *mod;

} module;


#endif
