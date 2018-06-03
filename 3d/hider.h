#ifndef HIDER
#define HIDER
double d2xd2yd2z(double *U,int i, int nx,int ny,double h);
double d4x(double *U,double *Ux,int i,double h);
double d4y(double *U,double *Uy,int i, int nx,double h);
double d4z(double *U,double *Uz,int i, int nx,int ny,double h);
double d5x(double *U,double *Ux,int i,double h);
double d5y(double *U,double *Uy,int i, int nx,double h);
double d5z(double *U,double *Uz,int i, int nx,int ny, double h);
double d2x2y(double *U,double *Ux, double *Uy,int i, int nx,double h);
double d2x2z(double *U,double *Ux, double *Uz,int i, int nx,int ny,double h);
double d2y2z(double *U,double *Uy, double *Uz,int i, int nx,int ny,double h);
double d3x2y(double *U,double *Ux,int i, int nx,double h);
double d3x2z(double *U,double *Uz,int i, int nx,int ny,double h);
double d2x3y(double *U,double *Uy,int i, int nx,double h);
double d3y2z(double *U,double *Uz,int i, int nx,int ny, double h);
double d2x3z(double *U,double *Uz,int i, int nx,int ny,double h);
double d2y3z(double *U,double *Uz,int i, int nx, int ny,double h);
double d4xy(double *U,double *Ux,int i, int nx,double h);
double d4xz(double *U,double *Ux,int i, int nx,int ny,double h);
double dx4y(double *U,double *Uy,int i, int nx,double h);
double d4yz(double *U,double *Uy,int i, int nx,int ny,double h);
double dx4z(double *U,double *Uz,int i, int nx,int ny,double h);
double dy4z(double *U,double *Uz,int i, int nx,int ny,double h);
double d2x2yz(double *U,double *Ux, double *Uy, double *Uz,int i, int nx,int ny,double h);
double d2xy2z(double *U,double *Ux,double *Uy, double *Uz,int i, int nx, int ny,double h);
double dx2y2z(double *U,double *Ux,double *Uy, double *Uz,int i, int nx,int ny,double h);
#endif
