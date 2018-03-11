#ifndef FINDIFF_H
#define FINDIFF_H
float *fin_diff(float *fd_coeff,float *fd_coeff_coor,int nrows,int ncols,int npoints,float *val);
float *Wve_prog(float **P,float *vel,const float dtdivh,int time_step,const int nrows,const int ncols);
#endif
