#ifndef FINDIFF_H
#define FINDIFF_H
float *fin_diff(float *fd_coeff,float *fd_coeff_coor,int nrows,int ncols,int npoints,float *val);
float *Wve_spas(float **P,float *vel,const float dtdivh,int time_step,const int nrows,const int ncols);
float **Wve_tim(float **P,float *Vel_mod,float h,float dt,float fmax, int src_loc,int nt, int nrows,int ncols );
#endif
