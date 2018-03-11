#ifndef ARRAYOPR_H
#define ARRAYOPR_H
float *vek_addition(float *A, float *B,const int nelmts);
float *vek_subtraction(float *A, float *B,const int nelmts);
float *vek_elmwise_mult(float *A, float *B,const int nelmts);
float *scalar_mult(float scalar_const,float *A,const int nelmts);
#endif
