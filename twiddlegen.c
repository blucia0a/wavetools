#include <stdio.h>
#include <complex.h>

static const float TwoPi = 6.283185307179586476925286766559f;
int main(int argc, char *argv[]){

  printf("complex float twid[10][1024] = {");
  for(int n = 0; n < 10; n++){
    printf("{");
    for(int k = 0; k < 1024; k++){
      complex float v = cexp(-1.0 * TwoPi * I * k / ((float)(2 << n)));
      if( k == 1023 ){
        printf("%f + %f * I",creal(v),cimag(v));
      }else{
        printf("%f + %f * I,",creal(v),cimag(v));
      }
    }

    if( n == 10 ){
      printf("}\n");
    }else{
      printf("},\n");
    }

  }

  printf("};\n");

}
