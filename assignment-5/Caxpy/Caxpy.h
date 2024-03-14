#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "intrin.h"
#include "logger.h"

using namespace std;

void CAXPYSerial(int N, int cond[], int a, int X[], int Y[]) {
  int i;
  for (i = 0; i < N; i++) {
    if (cond[i]) Y[i] = a * X[i] + Y[i];
  }
}

// implementation of relu using instrinsics
void CAXPYVector(int N, int cond[], int a, int X[], int Y[]) {
 // TODO
  for(int i = 0; i<N; i += VLEN){
    int num_1 = VLEN;
    if(i + VLEN > N)
      num_1 = N-i;
    __cs295_mask m1 = _cs295_init_ones(num_1);
    __cs295_vec_int X_v;
    __cs295_vec_int Y_v;
    __cs295_vec_int cond_v;
    _cs295_vload_int(X_v, &X[i], m1);
    _cs295_vload_int(Y_v, &Y[i], m1);
    _cs295_vload_int(cond_v, &cond[i], m1);
    __cs295_vec_int zero_v = _cs295_vset_int(0);
    __cs295_mask cond_mask = _cs295_init_ones(num_1);
    _cs295_veq_int(cond_mask, cond_v, zero_v, m1);
    cond_mask = _cs295_mask_not(cond_mask);
    __cs295_vec_int a_v = _cs295_vset_int(a);
    _cs295_vmult_int(X_v, X_v, a_v, cond_mask);
    _cs295_vadd_int(Y_v, X_v, Y_v, cond_mask);
    _cs295_vstore_int(&Y[i], Y_v, m1);
  }
}