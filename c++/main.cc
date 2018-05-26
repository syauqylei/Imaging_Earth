#include <iostream>
#include <iomanip>
#include <cmath>
#include "wavesim.h"
#include "arrayman.h"
#include "coeff.h"
#include "source_function.h"
#include "hider.h"

int main(){
	int nx=100;
	int ny=100;
	double *vel = new double [nx*ny];
	for (int i=0;i<ny;i++){
		for (int j=0;j<nx;j++){
			
			vel[i*nx+j]=2000.0;
			}
		}
	
	double t=0;
	double T=1;
	double h=10.00;
	double f=50.0;
	double dt=0.001;
	int nt=int(T/dt);
	double **u;
	double **v;
	u=wvenacd(vel,nx,ny,nx*(ny/2)+nx/2,f,h,dt,T);
	v=wvefd(vel,nx,ny,nx*(ny/2)+nx/2,f,h,dt,T);
	w_dat("data/nacd_sample",vel,u,dt,h,nt,nx,ny,1);
	w_dat("data/fd_sample",vel,v,dt,h,nt,nx,ny,1);
	}

