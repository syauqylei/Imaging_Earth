#include <iostream>
#include <math.h>
#include <string>
#include "nadm.h"
#include "arrayman.h"
#include "arrayopr.h"
#include "source_function.h"
#include "fin_diff.h"

int main(){
	int ncols,nrows;
	nrows=100;
	ncols=100;
	double T=1;
	double dt=0.002;//sampling
	int nt=T/dt+1;
	
	double h=20.0;
	
	double *Vel_Mod = new double [nrows*ncols];

	//Create Uniform Velocity model
	for (int i=0; i<nrows;i++){
		for (int j=0;j<ncols;j++){
			Vel_Mod[i*ncols+j] = 2000.00;
		}
	}
	//print_vek(Vel_Mod,nrows*ncols);
	std::cout <<"die\n";
	double *cfl2=cdth4(Vel_Mod,dt,h,ncols,nrows,1);
	print_vek(cfl2,nrows*ncols);
	delete [] Vel_Mod;
	delete [] cfl2;
}
