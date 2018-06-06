#include <iostream>
#include <iomanip>
#include "source_function.h"
#include "arrayman.h"
#include "hider.h"
#include "coeff.h"
#include "abcon.h"


double **wvenacd(double *vel, int nx, int ny,int srcloc, double fmax,double h, double dt,double T){
	int nt=int(T/dt+1);
	int Nx=nx+2;
	int Ny=ny+2;
	double t;
	double **u=alloc_mat(nt,nx*ny);
	double *F=new double[nx*ny];
	double **U=alloc_mat(nt,Nx*Ny);
	double **Ux=alloc_mat(nt,Nx*Ny);
	double **Uy=alloc_mat(nt,Nx*Ny);
	
	//angle factor for abc higdon
	double *beta= new double[4];
	beta[0]=0.99;
	beta[1]=0.79;
	beta[2]=0.52;
	beta[3]=0.31;
	
	int *stencil= new int[nx*ny];
	for (int i=1;i<Ny-1;i++){
		for (int j=1;j<Nx-1;j++){
			stencil[(i-1)*nx+j-1]=i*Nx+j;
		}
	}
			
	int tprint=nt/10;
	
	for (int i=1; i<nt-1;i++){
		//time step./w	
		t=dt*i;
		F[srcloc]=ricker_wavelet_1(fmax,t);
		if(i%tprint==0){
		std::cout<<"Calculating Wavefield ... "<<float(i)/float(nt)*100<<"%\n";}
		//boundary Neumann
		for (int j=0;j<Nx;j++){
			U[i][j]=U[i][j+2*Nx];
			Ux[i][j]=Ux[i][j+2*Nx];
			Uy[i][j]=Uy[i][j+2*Nx];
			}
		for (int j=0;j<Nx;j++){
			U[i][j+Nx*Ny-Nx]=U[i][j+Nx*Ny-2*Nx];
			Ux[i][j+Nx*Ny-Nx]=Ux[i][j+Nx*Ny-2*Nx];
			Uy[i][j+Nx*Ny-Nx]=Uy[i][j+Nx*Ny-2*Nx];
			}
		for (int j=0;j<Ny;j++){
			U[i][j*Nx]=U[i][j*Nx+2];
			Ux[i][j*Nx]=Ux[i][j*Nx+2];
			Uy[i][j*Nx]=Uy[i][j*Nx+2];
			}
		for (int j=0;j<Ny;j++){
			U[i][j*Nx+Nx-1]=U[i][j*Nx+Nx-3];
			Ux[i][j*Nx+Nx-1]=Ux[i][j*Nx+Nx-3];
			Uy[i][j*Nx+Nx-1]=Uy[i][j*Nx+Nx-3];
			}
				
		//solution of nacd
		for (int j=0; j<nx*ny;j++){
			U[i+1][stencil[j]]=2.0*U[i][stencil[j]]-U[i-1][stencil[j]]+cfl1(vel[j],dt)*d2xd2y(U[i],stencil[j],Nx,h)
											-cfl2(vel[j],dt,h)*(d4x(U[i],Ux[i],stencil[j],Nx,h)+d4y(U[i],Uy[i],stencil[j],Nx,h))
											+cfl3(vel[j],dt)*(d2x2y(U[i],Ux[i],Uy[i],stencil[j],Nx,h))+F[j];
			u[i+1][j]=U[i+1][stencil[j]];//store wavefield
			Ux[i+1][stencil[j]]=2.0*Ux[i][stencil[j]]-Ux[i-1][stencil[j]]+cfl1(vel[j],dt)*d2xd2y(Ux[i],stencil[j],Nx,h)
											-cfl2(vel[j],dt,h)*(d5x(U[i],Ux[i],stencil[j],Nx,h)+dx4y(U[i],Uy[i],stencil[j],Nx,h))
											+cfl3(vel[j],dt)*(d3x2y(U[i],Ux[i],stencil[j],Nx,h));
			
			Uy[i+1][stencil[j]]=2.0*Uy[i][stencil[j]]-Uy[i-1][stencil[j]]+cfl1(vel[j],dt)*d2xd2y(Uy[i],stencil[j],Nx,h)
											-cfl2(vel[j],dt,h)*(d4xy(U[i],Ux[i],stencil[j],Nx,h)+d5y(U[i],Uy[i],stencil[j],Nx,h))
											+cfl3(vel[j],dt)*(d2x3y(U[i],Uy[i],stencil[j],Nx,h));
			
			}
			
		//abc boundary
		
		//bot
		for (int j=1; j<Nx-1;j++){
			double cf=cfl(vel[nx*ny-nx+j-1],dt,h);
			U[i+1][Nx*Ny-2*Nx+j]=hiabc(U,i+1,Nx*Ny-2*Nx+j,-Nx,cf,beta,4);
			Ux[i+1][Nx*Ny-2*Nx+j]=hiabc(Ux,i+1,Nx*Ny-2*Nx+j,-Nx,cf,beta,4);
			Uy[i+1][Nx*Ny-2*Nx+j]=hiabc(Uy,i+1,Nx*Ny-2*Nx+j,-Nx,cf,beta,4);
			}
		//left
		for (int j=1; j<Ny-1;j++){
			double cf=cfl(vel[(j-1)*nx],dt,h);
			U[i+1][j*Nx+1]=hiabc(U,i+1,j*Nx+1,1,cf,beta,4);
			Ux[i+1][j*Nx+1]=hiabc(Ux,i+1,j*Nx+1,1,cf,beta,4);
			Uy[i+1][j*Nx+1]=hiabc(Uy,i+1,j*Nx+1,1,cf,beta,4);
			}
		//right
		for (int j=1; j<Ny-1;j++){
			double cf=cfl(vel[(j-1)*nx+nx-1],dt,h);
			U[i+1][j*Nx+Nx-2]=hiabc(U,i+1,j*Nx+Nx-2,-1,cf,beta,4);
			Ux[i+1][j*Nx+Nx-2]=hiabc(Ux,i+1,j*Nx+Nx-2,-1,cf,beta,4);
			Uy[i+1][j*Nx+Nx-2]=hiabc(Uy,i+1,j*Nx+Nx-2,-1,cf,beta,4);
			}
		}
		
	free_mat_mem(Ux);
	free_mat_mem(Uy);
	free_mat_mem(U);
	delete [] beta;
	delete [] F;
	delete [] stencil;
	return u;
	}


double **wvefd(double *vel, int nx, int ny,int srcloc, double fmax,double h, double dt,double T){
	
	int nt=int(T/dt+1);
	double t;
	double **U=alloc_mat(nt,nx*ny);
	double *beta= new double[4];
	beta[0]=0.99;
	beta[1]=0.79;
	beta[2]=0.52;
	beta[3]=0.31;
	
	for (int i=1; i<nt-1;i++){
		//time step
		t=dt*i;
		//boundary Neumann
		for (int j=0;j<nx;j++){U[i][j]=U[i][j+nx];}
		for (int j=nx*ny-nx;j<nx*ny;j++){U[i][j]=U[i][j-nx];}
		for (int j=nx; j<nx*ny-nx;j++){
			if(j%nx==0){U[i][j]=U[i][j+1];} 
			if(j%nx==nx-1){U[i][j]=U[i][j-1];} 
			}
		
		//solution of nacd
		for (int j=nx; j<nx*ny-nx;j++){
			if(j%nx==0 || j%nx==nx-1){continue;}
			U[i+1][j]=2.0*U[i][j]-U[i-1][j]+cfl1(vel[j],dt)*d2xd2y(U[i],j,nx,h);
			}
		U[i+1][srcloc]+=ricker_wavelet_1(fmax,t);
		
		//bot
		for (int j=nx*ny-2*nx+1; j<nx*ny-nx-1;j++){
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,-nx,cf,beta,4);
			}
		//left
		for (int j=nx+1; j<nx*ny-nx;j=j+nx){
			//std::cout<<j<<"\n";
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,1,cf,beta,4);
			}
		//right
		for (int j=2*nx-2; j<nx*ny-nx;j=j+nx){
			//std::cout<<j<<"\n";
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,-1,cf,beta,4);
			}
		
		}
	delete [] beta;
	return U;
	}
