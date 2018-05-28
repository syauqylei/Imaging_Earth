#include <iostream>
#include <iomanip>
#include <cmath>
#include "wavesim.h"
#include "arrayman.h"

int main(){
	int nx=100;
	int ny=100;
	
	double *vel = new double [nx*ny];
	for (int i=0;i<ny;i++){
		for (int j=0;j<nx;j++){
			
			vel[i*nx+j]=2000.0;
			}
		}
	
	double t=0;
	double T=1;
	double h=10.00;
	double f=50.0;
	double dt=0.001;
	int nt=int(T/dt);
	}

