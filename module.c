#include <stdlib.h>

#include "module.h"


void mod_init(module **m){

  *m = (module *)malloc(sizeof(module));

}
