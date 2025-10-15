/*
Filename: fir.cpp
FIR lab wirtten for WES/CSE237C class at UCSD.
Match filter
INPUT:
x: signal (chirp)

OUTPUT:
y: filtered output

*/

#include "fir.h"

void fir(data_t *y, data_t x)
{
#pragma HLS PIPELINE II=1

	coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

	static data_t shift_reg[N];
#pragma HLS ARRAY_PARTITION variable=shift_reg complete

	acc_t acc = 0;

	// shift
	for (int i = N - 1; i > 0; i--) {
#pragma HLS UNROLL
		shift_reg[i] = shift_reg[i - 1];
	}

	shift_reg[0] = x;

	// multiply–accumulate
	for (int i = 0; i < N; i++) {
#pragma HLS UNROLL
		acc += shift_reg[i] * c[i];
	}

	*y = acc;
}

