#include <iostream>
#include "wavesim.h"
#include "arrayman.h"

int main(){
	int nx=50;
	int ny=50;
	int nz=10;
	
	double *vel = new double [nx*ny*nz];
	
	for (int i=0;i<nz;i++){
		for (int j=0;j<ny;j++){
			for (int k=0; k<nx;k++){
				vel[i*nx+j]=4000.0;
				}
			}
		}
	
	double t=0;
	double T=1;
	double h=10.00;
	double f=50.0;
	double dt=0.001;
	int nt=int(T/dt);
	double **U;
	
	U=wvenacd(vel, nx, ny,nz, nx*ny*(nz/2)+nx*(ny/2)+nx/2, f,h,dt,0.2);
	w_dat("data/nacd", vel,U,dt,h, nt, nx, ny, nz);
	free_mat_mem(U);
	delete [] vel;
	}

