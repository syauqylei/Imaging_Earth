#include "arrayopr.h"
#include "arrayman.h"
#include "source_function.h"
#include "fin_diff_opr.h"
#include <iostream>
#include <iomanip>

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
		double t=i*dt;
		//add source term
		P[i+1][src_loc]+=ricker_wavelet(freq,t);
		for(int j=0;j<nx*ny;j++){
			P[i+1][j]+=2.0*P[i][j]-P[i-1][j]+
			CDTH2[j]*(/* laplace */ fd_2d(P[i],j,hd.fd_cf,hd.fd_cf_coo,nx,ny,5)/h/h);
		}
		std:: cout<<"Computing Wavefield ....."<<std::setprecision(3)<<(float)i/(nt-2)*100<<"%"<<std::endl;
	}
	delete [] CDTH2;
	return P;
	}

double **Wve_nadm(int src_loc, double freq,double *Vel_Mod,double h, double dt,int nt,int nx,int ny){
	double **P=alloc_mat(nt,nx*ny);
	double **Px=alloc_mat(nt,nx*ny);
	double **Py=alloc_mat(nt,nx*ny);
	double *CDTH2=cdth2(Vel_Mod,dt,h,nx,ny,1);
	double *CDTH4=cdth4(Vel_Mod,dt,h,nx,ny,1);
	float tprint=nt/10;
	hd2d hd;
	
	hd = input((double)nx);
	
	//Time-step loop
	for (int i=1;i<nt-1;i++){
		std:: cout<<"Computing Wavefield ....."<<std::setprecision(3)<<(float)i/(nt-2)*100<<"%"<<std::endl;
		double t=i*dt;
		//add source term
		P[i+1][src_loc]+=ricker_wavelet(freq,t);
		for(int j=0;j<nx*ny;j++){
			/*P Wavefield */
			P[i+1][j]+=2.0*P[i][j]-P[i-1][j]+
			CDTH2[j]*
			(/* d2x + d2y*/ 
			/* d2x */
			fd_2d(P[i],j,hd.ad2x,hd.Cad2x,nx,ny,3)*2.0/h/h+
			fd_2d(Px[i],j,hd.bd2x,hd.Cbd2x,nx,ny,2)/2.0/h+
			
			/* d2y */
			fd_2d(P[i],j,hd.ad2y,hd.Cad2y,nx,ny,3)*2.0/h/h+
			fd_2d(Py[i],j,hd.bd2y,hd.Cbd2y,nx,ny,2)/2.0/h
			)+
			CDTH4[j]/12.0*
			(/* d4x + d4y + 2*d2x2y */
			/* d4x */
			fd_2d(P[i],j,hd.ad4x,hd.Cad4x,nx,ny,3)*(-12.0)/h/h/h/h +
			fd_2d(Px[i],j,hd.bd4x,hd.Cbd4x,nx,ny,2)*(6.0)/h/h/h +
			
			/* d4y */
			fd_2d(P[i],j,hd.ad4y,hd.Cad4y,nx,ny,3)*(-12.0)/h/h/h/h +
			fd_2d(Py[i],j,hd.bd4y,hd.Cbd4y,nx,ny,2)*(6.0)/h/h/h +
			
			/* 2*d2x2y */2.0*(
			fd_2d(P[i],j,hd.d2x2y,hd.Cd2x2y,nx,ny,9)/h/h/h/h)
			);
			
			/* Px Wavefield */
			Px[i+1][j]+=2.0*Px[i][j]-Px[i-1][j]+
			CDTH2[j]*
			(/* d3x + d2yx*/ 
			/* d3x */
			fd_2d(P[i],j,hd.ad3x,hd.Cad3x,nx,ny,2)*15.0/2.0/h/h/h+
			fd_2d(Px[i],j,hd.bd3x,hd.Cbd3x,nx,ny,3)*-3.0/2.0/h/h+
			/* dx2y */
			fd_2d(P[i],j,hd.adx2y,hd.Cadx2y,nx,ny,8)/4.0/h/h/h+
			fd_2d(Py[i],j,hd.bd3x,hd.Cbd3x,nx,ny,7)/2.0/h/h+
			fd_2d(Px[i],j,hd.cdx2y,hd.Ccd2xy,nx,ny,3)/h/h
			)+
			CDTH4[j]/12.0*
			(/* d5x + d4yx + 2*d3x2y */
			/* d5x */
			fd_2d(P[i],j,hd.ad5x,hd.Cad5x,nx,ny,2)*-90.0/h/h/h/h/h+
			fd_2d(Px[i],j,hd.bd5x,hd.Cbd5x,nx,ny,3)*30.0/h/h/h/h+
			
			/* dx4y */
			fd_2d(P[i],j,hd.adx4y,hd.Cadx4y,nx,ny,8)*-3.0/h/h/h/h/h+
			fd_2d(Py[i],j,hd.bdx4y,hd.Cbdx4y,nx,ny,7)*6.0/h/h/h/h+
			
			/* 2*d3x2y */2.0*(
			fd_2d(P[i],j,hd.ad3x2y,hd.Cad3x2y,nx,ny,6)*3.0/h/h/h/h/h+
			fd_2d(Px[i],j,hd.bd3x2y,hd.Cbd3x2y,nx,ny,3)*-6.0/h/h/h/h)
			);
			
			/* Py Wavefield */
			Py[i+1][j]+=2.0*Py[i][j]-Py[i-1][j]+
			CDTH2[j]*
			(/* d2xy + d3y*/ 
			/* d2xy */
			fd_2d(P[i],j,hd.ad2xy,hd.Cad2xy,nx,ny,8)/4.0/h/h/h+
			fd_2d(Px[i],j,hd.bd2xy,hd.Cbd2xy,nx,ny,7)/2.0/h/h+
			fd_2d(Py[i],j,hd.cd2xy,hd.Ccd2xy,nx,ny,3)/h/h+
			
			/* d3y */
			fd_2d(P[i],j,hd.ad3y,hd.Cad3y,nx,ny,2)*15.0/2.0/h/h/h+
			fd_2d(Py[i],j,hd.bd3y,hd.Cbd3y,nx,ny,3)*-3.0/2.0/h/h
			
			)+
			CDTH4[j]/12.0*
			(/* d4xy + d5y + 2*d2x3y */
			/* d4xy */
			fd_2d(P[i],j,hd.ad4xy,hd.Cad4xy,nx,ny,8)*-3.0/h/h/h/h/h+
			fd_2d(Px[i],j,hd.bd4xy,hd.Cbd4xy,nx,ny,7)*6.0/h/h/h/h+
			
			/* d5y */
			fd_2d(P[i],j,hd.ad5y,hd.Cad5y,nx,ny,2)*-90.0/h/h/h/h/h+
			fd_2d(Py[i],j,hd.bd5y,hd.Cbd5y,nx,ny,3)*30.0/h/h/h/h+
			
			/* 2*d2x3y */2.0*(
			fd_2d(P[i],j,hd.ad2x3y,hd.Cad2x3y,nx,ny,6)*3.0/h/h/h/h/h+
			fd_2d(Py[i],j,hd.bd2x3y,hd.Cbd2x3y,nx,ny,3)*-6.0/h/h/h/h)
			);
			
			Px[i][j]=fd_2d(P[i],j,hd.bd2x,hd.Cbd2x,nx,ny,2)/2/h;
			Py[i][j]=fd_2d(P[i],j,hd.bd2y,hd.Cbd2y,nx,ny,2)/2/h;
		}
	}
	delete [] CDTH2;
	free_mat_mem(Px);
	free_mat_mem(Py);
	return P;
	}
