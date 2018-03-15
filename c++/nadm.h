#ifndef NADM_H
#define NADM_H
double *cdth2(double *Vel_Mod,double dt,double h,int nx,int ny, int nz);
double *cdth4(double *Vel_Mod,double dt,double h,int nx,int ny, int nz);
double **nadm_prog_2d(int src_loc,double freq,double *Vel_Mod,double dt, int nstep, double h, int nx, int nz);
double **nadm_prog_3d(int src_loc,double freq,double *Vel_Mod,double dt, int nstep, double h, int nx, int ny, int nz);
#endif
