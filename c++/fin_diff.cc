#include "arrayopr.h"
#include "arrayman.h"
#include <iostream>

struct hd2d{
	float fd_cf[5];
	float fd_cf_coo[5];
	};
hd2d input(float nx){
	hd2d HD;
	HD.fd_cf[0]=1;
	HD.fd_cf[1]=1;
	HD.fd_cf[2]=-4;
	HD.fd_cf[3]=1;
	HD.fd_cf[4]=1;
	HD.fd_cf_coo[0]=-nx;
	HD.fd_cf_coo[1]=-1;
	HD.fd_cf_coo[2]=0;
	HD.fd_cf_coo[3]=1;
	HD.fd_cf_coo[4]=nx;
	return HD;
	}
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
float *Wve_prog(float **P,float *vel,const float dtdivh,int time_step,const int nrows,const int ncols){
	/*float *fd_coeff = new float[5];
	fd_coeff[0]=1.0;
	fd_coeff[1]=1.0;
	fd_coeff[2]=-4.0;
	fd_coeff[3]=1.0;
	fd_coeff[4]=1.0;
	
	float *fd_coeff_coor = new float[5] ;
	fd_coeff_coor[0]=-1.0*ncols;
	fd_coeff_coor[1]=-1.0;
	fd_coeff_coor[2]=0.0;
	fd_coeff_coor[3]=1.0;
	fd_coeff_coor[4]=1.0*ncols;
	*/
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
	//delete [] fd_coeff;
	//delete [] fd_coeff_coor;
	float *A,*B,*sum;
	
	A=scalar_mult(2.0,P[time_step],nrows*ncols);
	B=vek_subtraction(A,P[time_step-1],nrows*ncols);
	sum=vek_addition(B,CFD,nrows*ncols);
	delete [] A; delete [] B;
	return sum;
	}
