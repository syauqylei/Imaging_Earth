#include <iostream>
#include "wavesim.h"
#include "arrayman.h"

int main(){
	int nx=100;
	int ny=100;
	
	double *vel = new double [nx*ny];
	for (int i=0;i<ny;i++){
		for (int j=0;j<nx;j++){
			
			vel[i*nx+j]=4000.0;
			}
		}
	
	double t=0;
	double T=1;
	double h=10.00;
	double f=50.0;
	double dt=0.001;
	int nt=int(T/dt);
	double **U;
	U=wvenacd(vel,nx,ny,nx*(ny/2)+nx/2,f,h,dt,T);
	w_dat("data/nacd_abc_3sample",vel,U,dt,h,nt,nx,ny,1);
	free_mat_mem(U);
	delete [] vel;
	}

