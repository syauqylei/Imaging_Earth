#include "arrayopr.h"
#include "arrayman.h"
#include "source_function.h"
#include "fin_diff_opr.h"
#include <iostream>

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

double fd_2d(double *P,int j,double *coeff,double *coeff_coo,int nx, int ny,int nstencil){
	double val=0;
	for (int k=0; k < nstencil; k++){
		if ( j+coeff_coo[k]< 0 || j+coeff_coo[k]> ny*nx-1){continue;}
		if ( j%nx == 0){
			if ( coeff_coo[k] == -1 || coeff_coo[k]==-nx-1){continue;}}
		if ( j%nx == nx-1){
			if ( coeff_coo[k] == 1 || coeff_coo[k]==+nx+1){continue;}}
		val+=P[j+(int)coeff_coo[k]]*coeff[k];
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
			CDTH2[j]*(/* laplace */ fd_2d(P[i],j,hd.fd_cf,hd.fd_cf_coo,nx,ny,5));
		}
	}
	delete [] CDTH2;
	return P;
	}


/*
double *lap2d(double *P,double *Px,double *Py,double h,int nx,int ny){
	hd2d HD;
	double *lap2d= new double [nx*ny];
	double *ad2x=fd_2d(HD.ad2x,HD.Cad2x,ny,nx,3,P);
	double *bd2x=fd_2d(HD.bd2x,HD.Cbd2x,ny,nx,2,Px);
	double *ad2y=fd_2d(HD.ad2y,HD.Cad2y,ny,nx,3,P);
	double *bd2y=fd_2d(HD.bd2y,HD.Cbd2y,ny,nx,2,Py);
	
	for (int i=0; i<ny; i++){
		for (int j=0; j<nx; j++){
			lap2d[i*nx+j]=ad2x[i*nx+j]*2.0/h/h-bd2x[i*nx+j]/2.0/h+
						  ad2y[i*nx+j]*2.0/h/h-bd2y[i*nx+j]/2.0/h;
			}
		}
		
	delete [] ad2x;
	delete [] bd2x;
	delete [] ad2y;
	delete [] bd2y;
	return lap2d;
	}

double *lap2d2(double *P,double *Px,double *Py,double h,int nx,int ny){
	hd2d HD;
	double *lap2d= new double [nx*ny];
	double *ad4x=fd_2d(HD.ad2x,HD.Cad2x,ny,nx,3,P);
	double *bd4x=fd_2d(HD.bd2x,HD.Cbd2x,ny,nx,2,Px);
	double *ad4y=fd_2d(HD.ad2y,HD.Cad2y,ny,nx,3,P);
	double *bd4y=fd_2d(HD.bd2y,HD.Cbd2y,ny,nx,2,Py);
	double *d2x2y=fd_2d(HD.d2x2y,HD.Cd2x2y,ny,nx,3,P);
	
	for (int i=0; i<ny; i++){
		for (int j=0; j<nx; j++){
			lap2d[i*nx+j]=ad4x[i*nx+j]*-12.0/h/h/h/h-bd4x[i*nx+j]*6.0/h/h/h+
						  ad4y[i*nx+j]*-12.0/h/h/h/h-bd4y[i*nx+j]*6.0/h/h/h+
						  d2x2y[i*nx+j]/h/h/h/h;
			}
		}
		
	delete [] ad4x;
	delete [] bd4x;
	delete [] ad4y;
	delete [] bd4y;
	delete [] d2x2y;
	return lap2d;
	}
*/
