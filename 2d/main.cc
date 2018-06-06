#include <iostream>
#include <fstream>
#include <vector>
#include "rnw.h"
#include "arrayman.h"
#include "wavesim.h"

int main(){/*
	std::vector<double> vel;
	std::vector<int> srcloc;
	int nx,ny,nz,ns;
	double h,dt,T,fm;
	read_vel("Velocity.txt",vel , nx,ny,nz,h);
	read_fwdset("fwdset.txt",srcloc,ns,dt,T,fm);
	int nt=int(T/dt+1);
	std::cout<<nx<<" "<<ny<<" "<<nz<<" "<<nt<<" "<<ns<<" "<<dt<<" "<<T<<" "<<h<<" "<<fm<<"\n";
	double *Velocity=&vel[0];
	*/
	double *Velocity=new double[50*50];
	for(int i=0;i<2500;i++){Velocity[i]=4000;}
	double **U;
	for (int i=0;i<1;i++){
		U=wvenacd(Velocity,50,50,25,50,10,0.001,0.5);
		write_rec("~/fin_proj_data/record/rec",U,25,10,0.001,50,501);
		}
	//w_dat("/scratch/syauqy/data/sample",Velocity,U,dt,h,nt,nx,ny,1,1,-1,1);
	free_mat_mem(U);
	delete [] Velocity;
	}

