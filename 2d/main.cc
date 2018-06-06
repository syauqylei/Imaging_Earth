#include <iostream>
#include <fstream>
#include <vector>
#include "rnw.h"
#include "arrayman.h"
#include "wavesim.h"

int main(){
	std::vector<double> vel;
	std::vector<int> srcloc;
	int nx,ny,nz,ns;
	double h,dt,T,fm;
	read_vel("Velocity.txt",vel , nx,ny,nz,h);
	read_fwdset("fwdset.txt",srcloc,ns,dt,T,fm);
	int nt=int(T/dt+1);
	std::cout<<nx<<" "<<ny<<" "<<nz<<" "<<nt<<" "<<ns<<" "<<dt<<" "<<T<<" "<<h<<" "<<fm<<"\n";
	double *Velocity=&vel[0];
	double **U;
	U=wvenacd(Velocity,nx,ny,nx/2,fm,h,dt,T);
	w_dat("data/sample",Velocity,U,dt,h,nt,nx,ny,1);
	free_mat_mem(U);
	}

