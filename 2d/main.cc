#include <iostream>
#include <fstream>
#include <vector>
#include "rnw.h"
#include "arrayman.h"
#include "wavesim.h"

int main(){
	int nx,ny,nz,ns;
	int *srcloc;
	double h,dt,T,fm;
	double *velocities;
	double **U;
	std::vector<double> vel;
	read_vel("x_iter_349.txt",vel,nx,ny,nz,h);
	velocities=&vel[0];
	std::vector<int> sourceloc;
	read_fwdset("fwdset.txt",sourceloc,ns,dt,T,fm);
	srcloc=&sourceloc[0];
	int nt=int(T/dt+1);
	U=wvenacd(velocities,ny,nz,srcloc[10],fm,h,dt,T);
	write_wve("/scratch/syauqy/sample",U,1,ny,nz,nt,dt,h);
	w_dat("/scratch/syauqy/data/sample", velocities,U,dt,h,nt,ny,nz,1);
	free_mat_mem(U);
	}

