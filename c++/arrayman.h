#ifndef ARRAYMAN_H
#define ARRAYMAN_H
int len(float *a);
float *mat_to_vek(float **arr,const int nrows, const int ncols);
float **alloc_mat(const int nrows, const int ncols);
void free_mat_mem(float **mat,const int nrows);
void print_mat(float **mat,const int nrows,const int ncols);
void print_vek(float *mat,const int nelmts);
void w_file_mat(char *filename, float **P,int nt,int nrows, int ncols);
void w_vtk(char *filename,float *Vel_mod, float **P,float h,int nt,int nx, int ny, int nz);
void w_csv(char *filename,float *Vel_mod, float **P,float dt,float h,int nt,int nx, int ny, int nz);
void w_dat(char *filename,float *Vel_mod, float **P,float dt,float h,int nt,int nx, int ny, int nz);
#endif

