#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libs/utils_arrayman/arrayman.h"
#include "libs/utils_arrayopr/arrayopr.h"
#include "libs/source_function/source_function.h"

float *fin_diff(float *fd_coeff,float *fd_coeff_coor,int nrows,int ncols,int npoints,float *val){
	float *fd_val=malloc(nrows*ncols*sizeof(float));
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

float *Wve_prog(float **P,float *vel,const float dtdivh,int time_step,const int nrows,const int ncols){
	float *fd_coeff = malloc(5*sizeof(float)) ;
	fd_coeff[0]=1.0;
	fd_coeff[1]=1.0;
	fd_coeff[2]=-4.0;
	fd_coeff[3]=1.0;
	fd_coeff[4]=1.0;
	
	float *fd_coeff_coor = malloc(5*sizeof(float)) ;
	fd_coeff_coor[0]=-1.0*ncols;
	fd_coeff_coor[1]=-1.0;
	fd_coeff_coor[2]=0.0;
	fd_coeff_coor[3]=1.0;
	fd_coeff_coor[4]=1.0*ncols;
	
	float *ret_val=malloc(ncols*nrows*sizeof(float));
	
	float *C,*CC,*FD,*CFD;
	C=scalar_mult(dtdivh,vel,nrows*ncols);
	CC=vek_elmwise_mult(C,C,nrows*ncols);
	FD=fin_diff(fd_coeff,fd_coeff_coor,nrows,ncols,5,P[time_step]);
	CFD=vek_elmwise_mult(CC,FD,nrows*ncols);
	
	free(C);
	free(CC);
	free(FD);
	free(fd_coeff);
	free(fd_coeff_coor);
	float *A,*B,*sum;
	
	A=scalar_mult(2.0,P[time_step],nrows*ncols);
	B=vek_subtraction(A,P[time_step-1],nrows*ncols);
	sum=vek_addition(B,CFD,nrows*ncols);
	return sum;
	}

void main(){
	int ncols,nrows;
	nrows=100;
	ncols=100;
	float T=0.2;
	float dt=0.001;//sampling
	
	int nt=T/dt+1;
	
	float h=10.0;
	float *Vel_Mod= malloc(nrows*ncols*sizeof(float));
	float *f_src= malloc(nrows*ncols*sizeof(float));
	float **P=alloc_mat(nt,nrows*ncols);
	
	//Create Uniform Velocity model
	for (int i=0; i<nrows;i++){
		for (int j=0;j<ncols;j++){
			Vel_Mod[i*ncols+j] = 1000.00;
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
		printf(" time : %f src val : %f  Wvefield : %f \n",*tp,ricker_wavelet(fmax,t),P[i+1][src_loc]);
	
	}
	printf(" Time domain iteration is done\n");
	//wfile_mat("coba_tulis1.txt",P,nt,nrows,ncols);
	//wcsv_file("coba_tulis1.txt",P,nt,nrows,ncols);

	//free memories
	free(Vel_Mod);
	free(f_src);
	free_mat_mem(P,nt);
}
