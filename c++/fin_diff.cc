#include "arrayopr.h"
#include "arrayman.h"
#include "source_function.h"
#include "fin_diff_opr.h"
#include <iostream>

float *fin_diff(float *fd_coeff,float *fd_coeff_coor,int nrows,int ncols,int npoints,float *val){
	float *fd_val=new float[nrows*ncols];
	int aab;
	for (int i=0;i<nrows;i++){
		for (int j =0; j<ncols;j++){
			for(int k=0;k<npoints;k++){
				aab=i*ncols+j+fd_coeff_coor[k];
				if(aab==i*ncols-1 && i*ncols+j == i*ncols ){continue;}
				if(aab==(i+1)*ncols && i*ncols+j == (i+1)*ncols-1 ){continue;}
				if(aab < 0 || aab > ncols*nrows-1 ){continue;}
				if(aab==i*ncols && i*ncols+j == (i+1)*ncols-1 ){continue;}
				if(aab==(i+2)*ncols && i*ncols+j == (i+1)*ncols-1 ){continue;}
				if(aab==(i-1)*ncols-1 && i*ncols+j == i*ncols ){continue;}
				if(aab==(i+1)*ncols-1 && i*ncols+j == i*ncols ){continue;}
				fd_val[i*ncols+j]+=val[aab]*fd_coeff[k];

			}
		}	
	}

	return fd_val;
}

float *Wve_spas(float **P,float *vel,const float dtdivh,int time_step,const int nrows,const int ncols){

	hd2d hd;
	hd = input((float)ncols);
	
	float *C,*CC,*FD,*CFD;
	C=scalar_mult(dtdivh,vel,nrows*ncols);
	CC=vek_elmwise_mult(C,C,nrows*ncols);
	FD=fin_diff(hd.fd_cf,hd.fd_cf_coo,nrows,ncols,5,P[time_step]);
	CFD=vek_elmwise_mult(CC,FD,nrows*ncols);
	delete [] C;
	delete [] CC;
	delete [] FD;
	float *A,*B,*sum;
	
	A=scalar_mult(2.0,P[time_step],nrows*ncols);
	B=vek_subtraction(A,P[time_step-1],nrows*ncols);
	sum=vek_addition(B,CFD,nrows*ncols);
	delete [] A; delete [] B;
	return sum;
	}

float **Wve_tim(float **P,float *Vel_mod,float h,float dt,float fmax, int src_loc,int nt, int nrows,int ncols ){
	float t;
	float f_src[nrows*ncols]={0};
	float *wve_prog;
	for( int i=1;i<nt-1;i++){
		t=i*dt;
		// add source term
		f_src[src_loc]=ricker_wavelet(fmax,t);
		wve_prog=Wve_spas(P,Vel_mod,dt/h,i,nrows,ncols);
		P[i+1]=vek_addition(wve_prog,f_src,nrows*ncols);
		/*
		std::cout << " Time : " << t;
		std::cout << " \t Wavefield Value : " << P[i+1][src_loc];
		std::cout << " \t Source Value = "<<ricker_wavelet(fmax,t)<<std::endl;	*/
	}
	delete [] wve_prog;
	return P;
}

float *wve_prog(float **P,float dt,float h,int nx, int nx, int nz){
	float *p;
	int ntot=nrows*ncols;
	int nstep=0;
	for (int i=0;i<ntot;i++){
		P[nstep+1][i]=2.0*P[nstep][i]-P[nstep-1][i]\
		+nstep;
	}
	return p;
	}
