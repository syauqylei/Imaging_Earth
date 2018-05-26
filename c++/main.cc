#include <iostream>
#include <string>
#include "arrayman.h"
#include "arrayopr.h"
#include "fin_diff.h"
int main(){
	int nx,ny;
	ny=50;
	nx=50;
	double T=0.5;
	double dt=0.002;//sampling
	int nt=T/dt+1;	
	double h=20.0;
	
	double *Vel_Mod = new double [ny*nx];

	//Create Uniform Velocity model
	for (int i=0; i<ny;i++){
		for (int j=0;j<nx;j++){
			Vel_Mod[i*nx+j] = 2000.00;
		}
	}
	
	std::cout <<"die\n";
	double **U=Wve_nadm(nx*ny/2+nx/2,30.0,Vel_Mod,h,dt,nt,nx,ny);
	double **P=Wve_stfd(nx*ny/2+nx/2,30.0,Vel_Mod,h,dt,nt,nx,ny);
	w_dat("data/exp4_stdfd",Vel_Mod,P,dt,h,nt,ny,nx,1);
	w_dat("data/exp12_nadm",Vel_Mod,U,dt,h,nt,ny,nx,1);
	
	//print_vek(Vel_Mod,ny*nx);
	free_mat_mem(U);
	//free_mat_mem(P);
	
	delete [] Vel_Mod;
}
