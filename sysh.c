#include <stdio.h>
#include <stdlib.h>

#include "module.h"
#include "wave.h"


module *m;
int main( int argc, char * argv[]){

  m = (malloc*)malloc(sizeof(m));
  wave_init(&w);
  mod_mkwave(m,w);

}
