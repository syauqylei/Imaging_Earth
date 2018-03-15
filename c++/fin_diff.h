#ifndef FINDIFF_H
#define FINDIFF_H
double *fin_diff(double *fd_coeff,double *fd_coeff_coor,int nrows,int ncols,int npoints,double *val);
double *Wve_spas(double **P,double *vel,const double dtdivh,int time_step,const int nrows,const int ncols);
double **Wve_tim(double **P,double *Vel_mod,double h,double dt,double fmax, int src_loc,int nt, int nrows,int ncols );
#endif
