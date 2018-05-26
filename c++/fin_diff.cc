#include "arrayopr.h"
#include "arrayman.h"
#include "fin_diff_opr.h"
#include "source_function.h"
#include <iostream>
#include <iomanip>

//coeff CFL^2
double *cdt2(double *Vel_Mod,double dt,int nx,int ny, int nz){
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
double *cdt4(double *Vel_Mod,double dt,int nx,int ny, int nz){
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
	
double cfl2(double Vel_Mod,double dt){
	double cfl2;
	cfl2=Vel_Mod*Vel_Mod*dt*dt;
	return cfl2;
	}
double cfl4(double Vel_Mod,double dt){
	double cfl4;
	cfl4=Vel_Mod*Vel_Mod*Vel_Mod*Vel_Mod*dt*dt*dt*dt;
	return cfl4;
	}

//fd operator
double fd_2d(double *P,int j,double *coeff,int *coeff_coo,int nx, int ny,int nstencil){
	double val=0;
	for (int k=0; k < nstencil; k++){
		if ( j+coeff_coo[k]< 0 || j+coeff_coo[k]> ny*nx-1){continue;}
		if ( j%nx == 0){
			if ( coeff_coo[k] == -1 || coeff_coo[k]==-nx-1 || 
				 coeff_coo[k] == nx*ny-1 || coeff_coo[k]== nx*ny-nx-1 ||
				 coeff_coo[k] == 2*nx*ny-1 || coeff_coo[k]== 2*nx*ny-nx-1  ){continue;}}
		if ( j%nx == nx-1){
			if ( coeff_coo[k] == 1 || coeff_coo[k]==nx+1  ||
				 coeff_coo[k] == nx*ny+1 || coeff_coo[k]== nx*ny+nx+1 ||
				 coeff_coo[k] == 2*nx*ny+1 || coeff_coo[k]== 2*nx*ny+nx+1  ){continue;}}
		
		val+=P[j+coeff_coo[k]]*coeff[k];
	}
		/*
		if ( j < nx && (nx-1 <= coeff_coo[k] <= nx+1 ||
						nx*ny+nx-1 <= coeff_coo[k] <= nx*ny+nx+1||
						2*nx*ny+nx-1 <= coeff_coo[k] <= 2*nx*ny+nx+1)){
		val+=P[j+coeff_coo[k]]*coeff[k];}
		
		if ( nx*ny <= j < nx*ny+nx && (nx-1 <= coeff_coo[k] <= nx+1 ||
						nx*ny+nx-1 <= coeff_coo[k] <= nx*ny+nx+1||
						2*nx*ny+nx-1 <= coeff_coo[k] <= 2*nx*ny+nx+1)){
		val+=P[j+coeff_coo[k]]*coeff[k];}
		
		if ( 2*nx*ny <= j < 2*nx*ny+nx && (nx-1 <= coeff_coo[k] <= nx+1 ||
						nx*ny+nx-1 <= coeff_coo[k] <= nx*ny+nx+1||
						2*nx*ny+nx-1 <= coeff_coo[k] <= 2*nx*ny+nx+1)){
		val+=P[j+coeff_coo[k]]*coeff[k];}
		}
		*/
	return val;
	}

double **Wve_stfd(int src_loc, double freq,double *Vel_Mod,double h, double dt,int nt,int nx,int ny){
	double **P=alloc_mat(nt,nx*ny);
	double *CDT2=cdt2(Vel_Mod,dt,nx,ny,1);
	int tprint=nt/10;
	double fd_cf[5] = {1,1,-4,1,1};
	int fd_cf_coo[5] = {-nx,-1,0,1,nx};
	//Time-step loop
	for (int i=1;i<nt-1;i++){
		
		double t=i*dt;
		//add source term
		P[i+1][src_loc]+=ricker_wavelet_1(freq,t);
		for(int j=0;j<nx*ny;j++){
			P[i+1][j]+=2.0*P[i][j]-P[i-1][j]+
			CDT2[j]*(/* laplace */ fd_2d(P[i],j,fd_cf,fd_cf_coo,nx,ny,5)/h/h);
		}if(i%tprint==0){
		std:: cout<<"Computing Wavefield ....."<<std::setprecision(3)<<(float)i/(nt-2)*100<<"%"<<std::endl;}
	}
	delete [] CDT2;
	return P;
	}

double **Wve_nadm(int src_loc, double freq,double *Vel_Mod,double h, double dt,int nt,int nx,int ny){
	double **P=alloc_mat(nt,3*nx*ny);
	double **Pout=alloc_mat(nt,nx*ny);
	int tprint=nt/10;
	
	double *cfA1=A1(h);
	double *cfA2=A2(h);
	double *cfA3=A3(h);
	int *cooA1=CA1(nx,ny);
	int *cooA2=CA2(nx,ny);
	int *cooA3=CA3(nx,ny);
	double *cfB1=B1(h);
	double *cfB2=B2(h);
	double *cfB3=B3(h);
	int *cooB1=CB1(nx, ny);
	int *cooB2=CB2(nx, ny);
	int *cooB3=CB3(nx, ny);
	double *cfC1=C1(h);
	double *cfC2=C2(h);
	double *cfC3=C3(h);
	int *cooC1=CC1(nx, ny);
	int *cooC2=CC2(nx, ny);
	int *cooC3=CC3(nx, ny);
	double *cfD1=D1(h);
	double *cfD2=D2(h);
	double *cfD3=D3(h);
	int *cooD1=CD1(nx, ny);
	int *cooD2=CD2(nx, ny);
	int *cooD3=CD3(nx, ny);
	double *cfE1=E1(h);
	double *cfE2=E2(h);
	double *cfE3=E3(h);
	int *cooE1=CE1(nx, ny);
	int *cooE2=CE2(nx, ny);
	int *cooE3=CE3(nx, ny);
	
	for (int i=1; i<nt-1;i++){
		P[i][src_loc]+=ricker_wavelet_1(freq,i*dt);
		for (int k=0; k< nx*ny;k++){
			P[i+1][k]=2.0*P[i][k]-P[i-1][k]+cfl2(Vel_Mod[k],dt)*
			/* d2x + d2y */(fd_2d(P[i],k,cfA1,cooA1,nx,ny,5)+fd_2d(P[i],k,cfB1,cooB1,nx,ny,5))+
			cfl4(Vel_Mod[k],dt)/12.0*
			/* d4x + d4y + 2d2x2y */(fd_2d(P[i],k,cfC1,cooC1,nx,ny,5)+fd_2d(P[i],k,cfD1,cooD1,nx,ny,5)+2.0*fd_2d(P[i],k,cfE1,cooE1,nx,ny,9));
			Pout[i][k]=P[i][k];
			}
		for (int k=nx*ny ; k < 2*nx*ny;k++){
			P[i+1][k]=2.0*P[i][k]-P[i-1][k]+cfl2(Vel_Mod[k-nx*ny],dt)*
			/* d3x + dx2y */(fd_2d(P[i],k,cfA2,cooA2,nx,ny,5)+fd_2d(P[i],k,cfB2,cooB2,nx,ny,18))+
			cfl4(Vel_Mod[k-nx*ny],dt)/12.0*
			/* d5x + dx4y + 2d3x2y */(fd_2d(P[i],k,cfC2,cooC2,nx,ny,5)+fd_2d(P[i],k,cfD2,cooD2,nx,ny,15)+2.0*fd_2d(P[i],k,cfE2,cooE2,nx,ny,9));	
			}
		
		for (int k=2*nx*ny ; k < 3*nx*ny;k++){
			P[i+1][k]=2.0*P[i][k]-P[i-1][k]+cfl2(Vel_Mod[k-2*nx*ny],dt)*
			/* d2xy + d2y */(fd_2d(P[i],k,cfA2,cooA3,nx,ny,18)+fd_2d(P[i],k,cfB2,cooB2,nx,ny,5))+
			cfl4(Vel_Mod[k-2*nx*ny],dt)/12.0*
			/* d4xy + d5y + 2d2x3y */(fd_2d(P[i],k,cfC3,cooC3,nx,ny,15)+fd_2d(P[i],k,cfD3,cooD3,nx,ny,5)+2.0*fd_2d(P[i],k,cfE3,cooE3,nx,ny,9));
			
			}
			
			if(i%tprint==0){
		std:: cout<<"Computing Wavefield ....."<<std::setprecision(3)<<(float)i/(nt-2)*100<<"%"<<std::endl;}
		std::cout<<P[i+1][src_loc]<<"\n";
		
		}
	
		
	free_mat_mem(P);
	delete [] cfA1;
	delete [] cfA2;
	delete [] cfA3;
	delete [] cooA1;
	delete [] cooA2;
	delete [] cooA3;
	delete [] cfB1;
	delete [] cfB2;
	delete [] cfB3;
	delete [] cooB1;
	delete [] cooB2;
	delete [] cooB3;
	delete [] cfC1;
	delete [] cfC2;
	delete [] cfC3;
	delete [] cooC1;
	delete [] cooC2;
	delete [] cooC3;
	delete [] cfD1;
	delete [] cfD2;
	delete [] cfD3;
	delete [] cooD1;
	delete [] cooD2;
	delete [] cooD3;
	delete [] cfE1;
	delete [] cfE2;
	delete [] cfE3;
	delete [] cooE1;
	delete [] cooE2;
	delete [] cooE3;
	return Pout;
}
	
