#ifndef FINDIFF_H
#define FINDIFF_H
double *fd_2d(double *fd_coeff,double *fd_coeff_coor,int nrows,int ncols,int npoints,double *val);
double *cdth4(double *Vel_Mod,double dt,double h,int nx,int ny, int nz);
double *cdth2(double *Vel_Mod,double dt,double h,int nx,int ny, int nz);
double **Wve_stfd(int src_loc, double freq,double *Vel_Mod,double h, double dt,int nt,int nx,int ny);
double **Wve_nadm(int src_loc, double freq,double *Vel_Mod,double h, double dt,int nt,int nx,int ny);
#endif
