#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "intrin.h"
#include "logger.h"

using namespace std;

void imaxSerial(int *values, int *output, int N) {
  int x = 0xffffffff;
  int index = 0;
  for (int i = 0; i < N; i++) {
    if (values[i] > x) {
      x = values[i];
      index = i;
    }
  }
  *output = index;
}

// implementation of imax using instrinsics
void imaxVector(int *values, int *output, int N) {
  
  for(int i=0; i<N; i += VLEN){
    int j=0;
    int max = 0xffffffff;
    int max_index = 0;
    __cs295_vec_int x_v;
    __cs295_mask m1 = _cs295_init_ones();
    _cs295_vload_int(x_v,&values[i],m1);
    while(j < VLEN){
      if(x_v.value[j] > max){
        max = x_v.value[j];
        max_index = i + j;
      }
      ++j;
    }
  }
  *output = max_index;
  return;
}