#include <iostream>
#include <fstream>
#include <vector>
#include "rnw.h"
#include "arrayman.h"
#include "wavesim.h"

int main(){
	int nx=100;
	int ny=100;
	double h,dt,T,fm;
	double *velocities;
	double **U;
	/*
	std::vector<double> vel;
	read_vel("x_iter_349.txt",vel,nx,ny,nz,h);
	velocities=&vel[0];
	std::vector<int> sourceloc;
	read_fwdset("fwdset.txt",sourceloc,ns,dt,T,fm);
	srcloc=&sourceloc[0];
	int nt=int(T/dt+1);*/
	double *vel=new double[nx*ny];
	for (int i=0; i<nx*ny;i++){
		vel[i]=4000.0;
		}
	U=wvenacd(vel,nx,ny,nx+nx/2,50.0,10.0,0.001,0.5); 
	int nt=int(0.5/0.1+1);
	w_dat("data/sample",vel,U,0.001,10,nt,nx,ny,1);
	free_mat_mem(U);
	delete [] vel;
	}

