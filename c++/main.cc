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
	//print_vek(Vel_Mod,ny*nx);
	std::cout <<"die\n";
	delete [] Vel_Mod;
}
