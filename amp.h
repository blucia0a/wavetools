#ifndef _amp_h_
#define _amp_h_

#include "sample.h"
#include "module.h"

typedef struct amp_s{

  module *mod; /*pointer to container module*/
  module *in; /*pointer to container module*/
  module *ampmod; /*pointer to container module*/

  float level;
  float base_level;

} amp;

sample amp_next(void *);  
void amp_init(amp **w);
void amp_modulate(amp *w);
void amp_setin(amp *w, module *amod);
void amp_setampmod(amp *w, module *amod);
void mod_mkamp(module *m, amp *w);
module *amp_new( float level );

#endif
