#include <iostream>
#include "source_function.h"
#include "arrayman.h"
#include "hider.h"
#include "coeff.h"
#include "abcon.h"


double **wvenacd(double *vel, int nx, int ny, int nz,int srcloc, double fmax,double h, double dt,double T){
	
	int nt=int(T/dt+1);
	double t;
	double **U=alloc_mat(nt,nx*ny*nz);
	double **Ux=alloc_mat(nt,nx*ny*nz);
	double **Uy=alloc_mat(nt,nx*ny*nz);
	double **Uy=alloc_mat(nt,nx*ny*nz);
	
	//angle factor for abc higdon
	double *beta= new double[4];
	beta[0]=0.99;
	beta[1]=0.79;
	beta[2]=0.52;
	beta[3]=0.31;
	int boundelm[nx*ny*nz]={0};
	for (int i=0;i<nz;i++){
		for(int j=0;j<ny;j++){
			for (int k=0;k<nx;k++){
				if(i%nz==0||i%nz==nz-1){boundelm[i*nx*ny+j*nx+k]=i*nx*ny+j*nx+k;}
				}
			}
		}
	for (int i=1; i<nt-1;i++){
		//time step
		t=dt*i;
		std::cout<<t<<"\n";
		//boundary Neumann
		
		for (int j=0;j<nx;j++){U[i][j]=U[i][j+nx];
								Ux[i][j]=Ux[i][j+nx];
								Uy[i][j]=Uy[i][j+nx];}
		for (int j=nx*ny-nx;j<nx*ny;j++){U[i][j]=U[i][j-nx];
											Ux[i][j]=Ux[i][j-nx];
											Uy[i][j]=Uy[i][j-nx];}
		for (int j=nx; j<nx*ny-nx;j++){
			if(j%nx==0){U[i][j]=U[i][j+1];
						Ux[i][j]=Ux[i][j+1];
						Uy[i][j]=Uy[i][j+1];} 
			if(j%nx==nx-1){U[i][j]=U[i][j-1];
							Ux[i][j]=Ux[i][j-1];
							Uy[i][j]=Uy[i][j-1];} 
			}
		
		
		for (int j=0; j<nx*ny*nz;j++){
			//solution of nacd
			if(j==boundelm[j]){continue;}
			U[i+1][j]=2.0*U[i][j]-U[i-1][j]+cfl1(vel[j],dt)*d2xd2y2z(U[i],j,nx,ny,h)
											-cfl2(vel[j],dt,h)*(d4x(U[i],Ux[i],j,h)+d4y(U[i],Uy[i],j,nx,h)+d4z(U[i],Uz[i],j,nx,ny,h))
											+cfl3(vel[j],dt)*(d2x2y(U[i],Ux[i],Uy[i],j,nx,h)+d2x2z(U[i],Ux[i],Uz[i],j,nx,ny,h)+d2y2z(U[i],Uy[i],Uz[i],j,nx,ny,h));
			
			Ux[i+1][j]=2.0*Ux[i][j]-Ux[i-1][j]+cfl1(vel[j],dt)*d2xd2y2z(Ux[i],j,nx,h)
											-cfl2(vel[j],dt,h)*(d5x(U[i],Ux[i],j,nx,h)+dx4y(U[i],Uy[i],j,nx,h)+dx4z())
											+cfl3(vel[j],dt)*(d3x2y(U[i],Ux[i],j,nx,h));
			
			Uy[i+1][j]=2.0*Uy[i][j]-Uy[i-1][j]+cfl1(vel[j],dt)*d2xd2y2z(Uy[i],j,nx,h)
											-cfl2(vel[j],dt,h)*(d4xy(U[i],Ux[i],j,nx,h)+d5y(U[i],Uy[i],j,nx,h))
											+cfl3(vel[j],dt)*(d2x3y(U[i],Uy[i],j,nx,h));
			Uz[i+1][j]=2.0*Uz[i][j]-Uz[i-1][j]+cfl1(vel[j],dt)*
			}
			
		U[i+1][srcloc]+=ricker_wavelet_1(fmax,t);
		//abc boundary
		
		//bot
		for (int j=nx*ny-2*nx+1; j<nx*ny-nx-1;j++){
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,-nx,cf,beta,4);
			Ux[i+1][j]=hiabc(Ux,i+1,j,-nx,cf,beta,4);
			Uy[i+1][j]=hiabc(Uy,i+1,j,-nx,cf,beta,4);
			}
		//left
		for (int j=nx+1; j<nx*ny-nx;j=j+nx){
			//std::cout<<j<<"\n";
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,1,cf,beta,4);
			Ux[i+1][j]=hiabc(Ux,i+1,j,1,cf,beta,4);
			Uy[i+1][j]=hiabc(Uy,i+1,j,1,cf,beta,4);
			}
		//right
		for (int j=2*nx-2; j<nx*ny-nx;j=j+nx){
			//std::cout<<j<<"\n";
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,-1,cf,beta,4);
			Ux[i+1][j]=hiabc(Ux,i+1,j,-1,cf,beta,4);
			Uy[i+1][j]=hiabc(Uy,i+1,j,-1,cf,beta,4);
			}
		}
		
	free_mat_mem(Ux);
	free_mat_mem(Uy);
	delete [] beta;
	return U;
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
