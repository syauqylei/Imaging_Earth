#include "arrayopr.h"
#include "arrayman.h"
#include "source_function.h"
#include "fin_diff_opr.h"
#include <iostream>

//coeff CFL^2
double *cdth2(double *Vel_Mod,double dt,double h,int nx,int ny, int nz){
	double *Cdth2=new double [nx*nz*ny];
	for(int i=0; i<nz;i++){
		for (int j=0; j<ny; j++){
			for (int k=0; k<nx;k++){
				Cdth2[i*nx*ny+j*nx+k]=Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]*dt*dt;
				}
			}
		}
	return Cdth2;
	}

//Coeff CFL^4
double *cdth4(double *Vel_Mod,double dt,double h,int nx,int ny, int nz){
	double *Cdth4=new double[nx*nz*ny];
	for(int i=0; i<nz;i++){
		for (int j=0; j<ny; j++){
			for (int k=0; k<nx;k++){
				Cdth4[i*nx*ny+j*nx+k]=Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]
				*Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]*dt*dt*dt*dt;
				}
			}
		}
	return Cdth4;
	}

//fd operator
double fd_2d(double *P,int j,double *coeff,double *coeff_coo,int nx, int ny,int nstencil){
	double val=0;
	for (int k=0; k < nstencil; k++){
		if ( j+coeff_coo[k]< 0 || j+coeff_coo[k]> ny*nx-1){continue;}
		if ( j%nx == 0){
			if ( coeff_coo[k] == -1 || coeff_coo[k]==-nx-1){continue;}}
		if ( j%nx == nx-1){
			if ( coeff_coo[k] == 1 || coeff_coo[k]==+nx+1){continue;}}
		val+=P[j+(int)coeff_coo[k]]*coeff[k];
		if ( j < nx && coeff_coo[k]>=nx-1){
		val+=P[j+(int)coeff_coo[k]]*coeff[k];}
		}
	return val;
	}

double **Wve_conv_fd(int src_loc, double freq,double *Vel_Mod,double h, double dt,int nt,int nx,int ny){
	double **P=alloc_mat(nt,nx*ny);
	double *CDTH2=cdth2(Vel_Mod,dt,h,nx,ny,1);
	hd2d hd;
	
	hd = input((double)nx);
	
	//Time-step loop
	for (int i=1;i<nt-1;i++){
		std:: cout<<i<<std::endl;
		double t=i*dt;
		//add source term
		P[i+1][src_loc]+=ricker_wavelet(freq,t);
		for(int j=0;j<nx*ny;j++){
			P[i+1][j]+=2.0*P[i][j]-P[i-1][j]+
			CDTH2[j]*(/* laplace */ fd_2d(P[i],j,hd.fd_cf,hd.fd_cf_coo,nx,ny,5)/h/h);
		}
	}
	delete [] CDTH2;
	return P;
	}

double **Wve_nadm(int src_loc, double freq,double *Vel_Mod,double h, double dt,int nt,int nx,int ny){
	double **P=alloc_mat(nt,nx*ny);
	double *CDTH2=cdth2(Vel_Mod,dt,h,nx,ny,1);
	double *CDTH4=cdth4(Vel_Mod,dt,h,nx,ny,1);
	hd2d hd;
	
	hd = input((double)nx);
	
	//Time-step loop
	for (int i=1;i<nt-1;i++){
		std:: cout<<i<<std::endl;
		double t=i*dt;
		//add source term
		P[i+1][src_loc]+=ricker_wavelet(freq,t);
		for(int j=0;j<nx*ny;j++){
			P[i+1][j]+=2.0*P[i][j]-P[i-1][j]+
			CDTH2[j]*(/* laplace */ fd_2d(P[i],j,hd.fd_cf,hd.fd_cf_coo,nx,ny,5));
		}
	}
	delete [] CDTH2;
	return P;
	}
