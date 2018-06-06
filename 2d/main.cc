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
	for (int i=0;i<1;i++){
		U=wvenacd(Velocity,nx,ny,srcloc[i],fm,h,dt,T);
		write_rec("~/fin_proj_data/record/rec",U,srcloc[i],h,dt,nx,nt);
		}
	//w_dat("/scratch/syauqy/data/sample",Velocity,U,dt,h,nt,nx,ny,1,1,-1,1);
	free_mat_mem(U);
	}

