#ifndef HIDER
#define HIDER
double dx(double *U,int i, int nx,double h);
double dy(double *U,int i, int nx,double h);
double d2xd2y(double *U,int i, int nx,double h);
double d4x(double *U,double *Ux,int i, int nx,double h);
double d4y(double *U,double *Uy,int i, int nx,double h);
double d5x(double *U,double *Ux,int i, int nx,double h);
double d5y(double *U,double *Uy,int i, int nx,double h);
double d2x2y(double *U,double *Ux, double *Uy,int i, int nx,double h);
double d3x2y(double *U,double *Ux,int i, int nx,double h);
double d2x3y(double *U,double *Uy,int i, int nx,double h);
double d4xy(double *U,double *Ux,int i, int nx,double h);
double dx4y(double *U,double *Uy,int i, int nx,double h);
#endif
