#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libs/utils_arrayman/arrayman.h"
#include "libs/utils_arrayopr/arrayopr.h"
#include "libs/source_function/source_function.h"

void writing_file(char *filename, float **mat,int nt,int nrows,int ncols){
	FILE *fp;
	fp=fopen(filename,"w");
	for(int i=0;i<nt;i++){
		for(int j=0;j<nrows;j++){
			for(int k=0;k<ncols;k++){
				fprintf(fp,"%.3f \t",mat[i][j*ncols+k]);
			}
			fprintf(fp,"\n");
		}
	}
	fclose(fp);
}

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

void main(){
	int ncols,nrows;
	nrows=10;
	ncols=10;
	
	float T=0.5;
	float dt=0.001;//sampling
	
	int nt=T/dt+1;
	
	float h=10.0;
	float *Vel_Mod= malloc(nrows*ncols*sizeof(float));
	float **P=alloc_mat(nt,nrows*ncols);
	float *fd_coeff = malloc(5*sizeof(float)) ;
	fd_coeff[0]=1.0;
	fd_coeff[1]=1.0;
	fd_coeff[2]=-4.0;
	fd_coeff[3]=1.0;
	fd_coeff[4]=1.0;
	float *fd_coeff_coor = malloc(5*sizeof(float)) ;
	fd_coeff[0]=-1.0*ncols;
	fd_coeff[1]=-1.0;
	fd_coeff[2]=0.0;
	fd_coeff[3]=1.0;
	fd_coeff[4]=1.0*ncols;
	
	//fin_diff(fd_coeff,fd_coeff_coor,nrows,ncols,5,Vel_Mod);
	//Create Uniform Velocity model
	for (int i=0; i<nrows;i++){
		for (int j=0;j<ncols;j++){
			Vel_Mod[i*ncols+j] = 100.00;
		}
	}
	
	float src;
	float fmax=50.0;
	float t=0.01;
	float *tp=&t;
	int src_loc=(ncols)*nrows/2+ncols/2;
	float *srcptr;
	float *A,*B,*C,*CC,*FD,*CFD;
	for( int i=1;i<nt;i++){
		printf("%d\n",i);
		*tp=i*dt;
		B=scalar_mult(2.0,P[i],nrows*ncols);
		A=vek_subtraction(B,P[i+1],ncols*nrows);
		C=scalar_mult(dt/h,Vel_Mod,nrows*ncols);
		CC=vek_elmwise_mult(C,C,nrows*ncols);
		FD=fin_diff(fd_coeff,fd_coeff_coor,nrows,ncols,5,P[i]);
		CFD=vek_elmwise_mult(CC,FD,nrows*ncols);
		P[i+1]=vek_addition(A,CFD,nrows*ncols);
		srcptr=&P[i+1][src_loc];
		*srcptr+=ricker_wavelet(fmax,t);
		
		free(A);
		free(B);
		free(C);
		free(CC);
		free(FD);
		free(CFD);
	}
	printf(" Time domain iteration is done");
	writing_file("coba_tulis1.txt",P,nt,nrows,ncols);

	//free memories
	free(fd_coeff);
	free(fd_coeff_coor);
	free(Vel_Mod);
	free_mat_mem(P,nt);
}
