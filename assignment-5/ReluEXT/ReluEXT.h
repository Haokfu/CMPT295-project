#include "intrin.h"
#include "logger.h"
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;

void ReluSerial(int *values, int *output, int N)
{
  for (int i = 0; i < N; i++)
  {
    int x = values[i];
    if (x < 0)
    {
      output[i] = 0;
    }
    else
    {
      output[i] = x;
    }
  }
}

// implementation of relu using instrinsics
void ReluVector(int *values, int *output, int N)
{
// TODO
for(int i = 0; i<N; i += VLEN){
    int num_1 = VLEN;
    if(i + VLEN > N)
      num_1 = N-i;
    __cs295_mask m1 = _cs295_init_ones(num_1);
    __cs295_vec_int value_v;
    _cs295_vload_int(value_v, &values[i], m1);
    __cs295_vec_int zero_v = _cs295_vset_int(0);
    __cs295_mask comp_mask = _cs295_init_ones(num_1);
    _cs295_vgt_int(comp_mask, value_v, zero_v, m1);
    comp_mask = _cs295_mask_not(comp_mask);
    _cs295_vset_int(value_v, 0, comp_mask);
    _cs295_vstore_int(&output[i], value_v, m1);
  }
}