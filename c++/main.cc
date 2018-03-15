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
	
	double src;
	double fmax=50.0;
	double t;
	int src_loc=(ncols)*nrows/2+ncols/2;

	delete [] Vel_Mod;
}
