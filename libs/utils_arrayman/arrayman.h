#ifndef ARRAYMAN_H
#define ARRAYMAN_H
int len(float *a);
float *mat_to_vek(float **arr,const int nrows, const int ncols);
float **alloc_mat(const int nrows, const int ncols);
void free_mat_mem(float **mat,const int nrows);
void print_mat(float **mat,const int nrows,const int ncols);
void print_vek(float *mat,const int nelmts);
void wfile_mat(char *filename, float **mat,int nt,int nrows,int ncols);
void wcsv_file(char *filename, float **mat,int nt,int nrows,int ncols);
#endif
