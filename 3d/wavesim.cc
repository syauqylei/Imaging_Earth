#include <iostream>
#include "source_function.h"
#include "arrayman.h"
#include "hider.h"
#include "coeff.h"
#include "abcon.h"


double **wvenacd(double *vel, int nx, int ny,int nz,int srcloc, double fmax,double h, double dt,double T){
	
	int nt=int(T/dt+1);
	double t;
	double **U=alloc_mat(nt,nx*ny*nz);
	double **Ux=alloc_mat(nt,nx*ny*nz);
	double **Uy=alloc_mat(nt,nx*ny*nz);
	double **Uz=alloc_mat(nt,nx*ny*nz);
	
	//angle factor for abc higdon
	double *beta= new double[4];
	beta[0]=0.99;
	beta[1]=0.79;
	beta[2]=0.52;
	beta[3]=0.31;
	
	int bdrelm[nx*ny*nz];
	
	for (int i=0;i<nz;i++){
		for (int j=0;j<ny;j++){
			for (int k=0;k<nx;k++){
				if (i%nz==0 || i%nz==nz-1 || j%ny==0 || j%ny==ny-1 ||
					k%nx==0 || k%nx==0){bdrelm[i*nx*ny+j*nx+k]=i*nx*ny+j*nx+k;}
				}
			}
		}
	
	for (int i=1; i<nt-1;i++){
		t=dt*i;
		std::cout<<t<<"this fkin error \n";
		for (int j=0;j<nx*ny;j++){
			U[i][j]=U[i][j+2*nx*ny];
			Ux[i][j]=Ux[i][j+2*nx*ny];
			Uy[i][j]=Uy[i][j+2*nx*ny];
			Uz[i][j]=Uz[i][j+2*nx*ny];
		}
		
		for (int j=0; j<nx*ny*nz;j++){
			if(bdrelm[j]==j){continue;}
			
			U[i+1][j]=2.0*U[i][j]-U[i-1][j]+cfl1(vel[j],dt)*d2xd2yd2z(U[i],j,nx,ny,h)
											-cfl2(vel[j],dt,h)*(d4x(U[i],Ux[i],j,h)+d4y(U[i],Uy[i],j,nx,h)+d4z(U[i],Uz[i],j,nx,ny,h))
											+cfl3(vel[j],dt)*(d2x2y(U[i],Ux[i],Uy[i],j,nx,h)+d2x2z(U[i],Ux[i],Uz[i],j,nx,ny,h)+d2y2z(U[i],Uy[i],Uz[i],j,nx,ny,h));
			
			Ux[i+1][j]=2.0*Ux[i][j]-Ux[i-1][j]+cfl1(vel[j],dt)*d2xd2yd2z(Ux[i],j,nx,ny,h)
											-cfl2(vel[j],dt,h)*(d5x(U[i],Ux[i],j,h)+dx4y(U[i],Uy[i],j,nx,h)+dx4z(U[i],Uz[i],j,nx,ny,h))
											+cfl3(vel[j],dt)*(d3x2y(U[i],Ux[i],j,nx,h)+d3x2z(U[i],Uz[i],j,nx,ny,h)+dx2y2z(U[i],Ux[i],Uy[i],Uz[i],j,nx,ny,h));
			
			Uy[i+1][j]=2.0*Uy[i][j]-Uy[i-1][j]+cfl1(vel[j],dt)*d2xd2yd2z(Uy[i],j,nx,ny,h)
											-cfl2(vel[j],dt,h)*(d4xy(U[i],Ux[i],j,nx,h)+d5y(U[i],Uy[i],j,nx,h)+dy4z(U[i],Uz[i],j,nx,ny,h))
											+cfl3(vel[j],dt)*(d2x3y(U[i],Uy[i],j,nx,h)+d2xy2z(U[i],Ux[i],Uy[i],Uz[i],j,nx,ny,h)+d3y2z(U[i],Uz[i],j,nx,ny,h));
			
			Uz[i+1][j]=2.0*Uz[i][j]-Uz[i-1][j]+cfl1(vel[j],dt)*d2xd2yd2z(Uz[i],j,nx,ny,h)
											-cfl2(vel[j],dt,h)*(d4xz(U[i],Ux[i],j,nx,ny,h)+d4yz(U[i],Uy[i],j,nx,ny,h)+d5z(U[i],Uz[i],j,nx,ny,h))
											+cfl3(vel[j],dt)*(d2x2yz(U[i],Ux[i],Uy[i],Uz[i],j,nx,ny,h)+d2x3z(U[i],Uz[i],j,nx,ny,h)+d2y3z(U[i],Uz[i],j,nx,ny,h));
			
			}
			
		U[i+1][srcloc]+=ricker_wavelet_1(fmax,t);
		//abc boundary
		
		//bdrzmin
		for (int j=nx*ny*nz-2*nx*ny; j<nx*ny*nz-nx*ny;j++){
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,-nx*ny,cf,beta,4);
			Ux[i+1][j]=hiabc(Ux,i+1,j,-nx*ny,cf,beta,4);
			Uy[i+1][j]=hiabc(Uy,i+1,j,-nx*ny,cf,beta,4);
			Uz[i+1][j]=hiabc(Uy,i+1,j,-nx*ny,cf,beta,4);
			}
		
		//bdrxmin
		for (int j=1; j<nx*ny*nz;j=j+nx){
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,1,cf,beta,4);
			Ux[i+1][j]=hiabc(Ux,i+1,j,1,cf,beta,4);
			Uy[i+1][j]=hiabc(Uy,i+1,j,1,cf,beta,4);
			Uz[i+1][j]=hiabc(Uy,i+1,j,1,cf,beta,4);
			}
		
		//bdrxmax
		for (int j=nx-2; j<nx*ny*nz;j=j+nx){
			double cf=cfl(vel[j],dt,h);
			U[i+1][j]=hiabc(U,i+1,j,-1,cf,beta,4);
			Ux[i+1][j]=hiabc(Ux,i+1,j,-1,cf,beta,4);
			Uy[i+1][j]=hiabc(Uy,i+1,j,-1,cf,beta,4);
			Uz[i+1][j]=hiabc(Uz,i+1,j,-1,cf,beta,4);
			}
		
		}
	free_mat_mem(Ux);
	free_mat_mem(Uy);
	free_mat_mem(Uz);
	delete [] beta;
	return U;
}

