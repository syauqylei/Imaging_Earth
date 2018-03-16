#include <iostream>
#include <math.h>
#include <string>
#include "arrayman.h"
#include "arrayopr.h"
#include "source_function.h"
#include "fin_diff.h"

int main(){
	int nx,ny;
	ny=200;
	nx=200;
	double T=2;
	double dt=0.005;//sampling
	int nt=T/dt+1;	
	double h=50.0;
	
	double *Vel_Mod = new double [ny*nx];

	//Create Uniform Velocity model
	for (int i=0; i<ny;i++){
		for (int j=0;j<nx;j++){
			Vel_Mod[i*nx+j] = 4000.00;
		}
	}
	
	double **U=Wve_nadm((nx*(ny/2)+ny/2),15.0,Vel_Mod,h,dt,nt,nx,ny);
	
	w_dat("data/exp2_model.yang.2007_nadm",Vel_Mod,U,dt,h,nt,ny,nx,1);
	
	//print_vek(Vel_Mod,ny*nx);
	std::cout <<"die\n";
	free_mat_mem(U);
	delete [] Vel_Mod;
}
