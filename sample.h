#ifndef _sample_h_
#define _sample_h_

/*TODO: Find a way to create statically specialized versions of all code for
 * different sample types to avoid conversion logic*/
typedef short sample;

#define SAMP2SCALE(s)  ( ((float)(s+32767)) / 65536. )

#endif
