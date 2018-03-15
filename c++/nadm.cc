#include "source_function.h"
#include "arrayman.h"

double *cdth2(double *Vel_Mod,double dt,double h,int nx,int ny, int nz){
	double *Cdth2=new double [nx*nz*ny];
	for(int i=0; i<nz;i++){
		for (int j=0; j<ny; j++){
			for (int k=0; k<nx;k++){
				Cdth2[i*nx*ny+j*nx+k]=Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]*dt*dt/h/h;
				}
			}
		}
	return Cdth2;
	}

double *cdth4(double *Vel_Mod,double dt,double h,int nx,int ny, int nz){
	double *Cdth4=new double[nx*nz*ny];
	for(int i=0; i<nz;i++){
		for (int j=0; j<ny; j++){
			for (int k=0; k<nx;k++){
				Cdth4[i*nx*ny+j*nx+k]=Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]
				*Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]*dt*dt*dt*dt/h/h/h/h;
				}
			}
		}
	return Cdth4;
	}

/*
double **nadm_prog_2d(int src_loc,double freq,double *Vel_Mod,double dt, int nstep, double h, int nx, int ny){
	int ntot=nx*ny;
	double **P=alloc_mat(nstep,nx*nz);
	double **Px=alloc_mat(nstep,nx*nz);
	double **Pz=alloc_mat(nstep,nx*nz);
	double *cdth2;
	double *cdth4;	
	for (int i=1; i < nstep-1; i++){
		P[i+1][src_loc]+=ricker_wavelet(freq,(double)i*dt);
		double *laplacian=lap(P,Px,Pz,nx,ny,h);
		double *laplacian2;
		double *laplacianX;
		double *laplacianX2;
		double *laplaciany;
		double *laplaciany2;
		for (int j=0;j<ntot;j++){
			P[i+1][j]=2.0*P[i][j]-P[i-1][j]+cdth2[j]*laplacian[j]+cdth4[j]*laplacian2[j];
			Px[i+1][j]=2.0*Px[i][j]-Px[i-1][j]+cdth2[j]*laplacianX[j]+cdth4[j]*laplacianX2[j];
			Py[i+1][j]=2.0*Py[i][j]-Py[i-1][j]+cdth2[j]*laplaciany[j]+cdth4[j]*laplaciany2[j];
			
		}
	}
	return P;
	}
double **nadm_prog_3d(int src_loc,double freq,double *Vel_Mod,double dt, int nstep, double h, int nx, int ny, int nz){
	int ntot=nx*ny*nz;
	double **P=alloc_mat(nstep,nx*ny*nz);
	double **Px=alloc_mat(nstep,nx*ny*nz);
	double **Py=alloc_mat(nstep,nx*ny*nz);
	double **Pz=alloc_mat(nstep,nx*ny*nz);
	double *cdth2;
	double *cdth4;	
	for (int i=1; i < nstep-1; i++){
		P[i+1][src_loc]+=ricker_wavelet(freq,(double)i*dt);
		double *laplacian=lap(P,Px,Py,Pz,nx,ny,nz,h);
		double *laplacian2;
		double *laplacianX;
		double *laplacianX2;
		double *laplacianY;
		double *laplacianY2;
		double *laplacianZ;
		double *laplacianZ2;
		for (int j=0;j<ntot;j++){
			P[i+1][j]=2.0*P[i][j]-P[i-1][j]+cdth2[j]*laplacian[j]+cdth4[j]*laplacian2[j];
			Px[i+1][j]=2.0*Px[i][j]-Px[i-1][j]+cdth2[j]*laplacianX[j]+cdth4[j]*laplacianX2[j];
			Py[i+1][j]=2.0*Py[i][j]-Py[i-1][j]+cdth2[j]*laplacianY[j]+cdth4[j]*laplacianY2[j];
			Pz[i+1][j]=2.0*Pz[i][j]-Pz[i-1][j]+cdth2[j]*laplacianZ[j]+cdth4[j]*laplacianZ2[j];
			
		}
	}
	return P;
	}
*/
