#include <iostream>
#include <fstream>
#include <vector>
#include "rnw.h"
#include "arrayman.h"
#include "wavesim.h"

int main(){
	int nx=50;
	int ny=50;
	double h=10.0;
	double dt=0.001;
	double T=0.5;
	double fm=50;
	double *velocities;
	double **U;
	double *vel=new double[nx*ny];
	for (int i=0; i<nx*ny;i++){
		vel[i]=4000.0;
		}
	U=wvenacd(vel,nx,ny,nx/2,50.0,10.0,0.001,0.5); 
	int nt=int(0.5/0.001+1);
	w_dat("data/sample",vel,U,0.001,10,nt,nx,ny,1);
	free_mat_mem(U);
	delete [] vel;
	}

