#include <iostream>
#include <math.h>
#include <string>
#include "arrayman.h"
#include "arrayopr.h"
#include "source_function.h"
#include "fin_diff.h"

int main(){
	int nx,ny;
	ny=100;
	nx=100;
	double T=1;
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
	
	double **U=Wve_conv_fd((nx*(ny/2)+ny/2),50.0,Vel_Mod,h,dt,nt,nx,ny);
	
	w_file_mat("coba_fd_opr_baru.txt",U,nt,ny,nx);
	
	//print_vek(Vel_Mod,ny*nx);
	std::cout <<"die\n";
	free_mat_mem(U);
	delete [] Vel_Mod;
}
