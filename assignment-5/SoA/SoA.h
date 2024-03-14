#include "intrin.h"
#include "logger.h"
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;

int SoASerial(int *values, int N)
{
  int sum = 0;
  for (int i = 0; i < N; i++)
  {
    sum += values[i];
  }

  return sum;
}
// Assume N % VLEN == 0
// Assume VLEN is a power of 2
int SoAVector(int *values, int N) {
 // TODO
 int sum = 0;
 for(int i=0; i<N; i += VLEN){
   __cs295_vec_int res_v;
   __cs295_mask m1 = _cs295_init_ones();
   _cs295_vload_int(res_v, &values[i], m1);
   int j = 1;
   while(j < VLEN){
    _cs295_hadd_int(res_v, res_v);
    _cs295_interleave_int(res_v, res_v);
    j *= 2;
   }
  __cs295_mask m2 = _cs295_init_ones(1);
  int store_value;
  _cs295_vstore_int(&store_value, res_v, m2);
  sum += store_value;
    
 }

 return sum;
}
