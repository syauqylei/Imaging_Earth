#include <stdio.h>
#include <stdlib.h>

float *vek_addition(float *A, float *B,const int nelmts){
	float *C=malloc(nelmts*sizeof(float));
	for (int i=0;i<nelmts;i++){
			C[i]=A[i]+B[i];
	}
	return C;
}
float *vek_subtraction(float *A, float *B ,const int nelmts){
	float *C=malloc(nelmts*sizeof(float));
	for (int i=0;i<nelmts;i++){
			C[i]=A[i]-B[i];
	}
	return C;
}
float *vek_elmwise_mult(float *A, float *B,const int nelmts){
	float *C=malloc(nelmts*sizeof(float));
	for (int i=0;i<nelmts;i++){
			C[i]=A[i]*B[i];
	}
	return C;
}
float *scalar_mult(float scalar_const,float *A,const int nelmts){
	float *C=malloc(nelmts*sizeof(float));
	for (int i=0;i<nelmts;i++){
			C[i]=scalar_const*A[i];
	}
	return C;
}
