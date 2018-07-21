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
	for (int i=0;i<ns;i++){
		U=wvenacd(Velocity,50,50,1250+25,50,20,0.002,5);
		write_rec("~/fin_proj_data/record/rec",U,25,50,0.00,50,501);
		}
	w_dat("data/coba",Velocity,U,0.005,20,1001,50,50,1,1,-1,1);
	free_mat_mem(U);
	delete [] Velocity;
	}

