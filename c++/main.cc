#include <iostream>
#include <math.h>
#include <string>
#include "arrayman.h"
#include "arrayopr.h"
#include "source_function.h"
#include "fin_diff.h"

int main(){
	int ncols,nrows;
	nrows=100;
	ncols=100;
	float T=0.1;
	float dt=0.001;//sampling
	
	int nt=T/dt+1;
	
	float h=10.0;
	float *Vel_Mod = new float [nrows*ncols];
	float *f_src = new float [nrows*ncols];
	float **P=alloc_mat(nt,nrows*ncols);
	
	//Create Uniform Velocity model
	for (int i=0; i<nrows;i++){
		for (int j=0;j<ncols;j++){
			Vel_Mod[i*ncols+j] = 2000.00;
		}
	}
	
	float src;
	float fmax=50.0;
	float t;
	float *tp=&t;
	int src_loc=(ncols)*nrows/2+ncols/2;
	float *wve_prog;
	for( int i=1;i<nt-1;i++){
		*tp=i*dt;
		// add source term
		f_src[src_loc]=ricker_wavelet(fmax,t);
		wve_prog=Wve_prog(P,Vel_Mod,dt/h,i,nrows,ncols);
		P[i+1]=vek_addition(wve_prog,f_src,nrows*ncols);
		
		std::cout << " Time : " << *tp ;
		std::cout << " \t Source Value : " <<  ricker_wavelet(fmax, *tp);
		std::cout << " \t Wavefield Value : " << P[i+1][src_loc]<<std::endl;
	
	}
	std::cout<< " Time domain iteration is done\n";
	w_dat("data/convFD",Vel_Mod,P,dt,h,nt,nrows,1,ncols);

	//free memories
	delete [] Vel_Mod;
	delete [] f_src;
	free_mat_mem(P,nt);
}
