#include "arrayopr.h"

struct A

	//operator for high order approximation
struct hi2d{
	int nx;
	int nz;
	
	//a : first operator b: second operator c :third operator C : Coeff operator
	//d2x
	float *ad2x=new float[3];
	ad2x[0]=1;
	ad2x[1]=-2;
	ad2x[2]=1;
	int *Cad2x=new int[3];
	Cad2x[0]=-1;
	Cad2x[1]=0;
	Cad2x[2]=1;
	float *bd2x=new float[2];
	bd2x[0]=-1;
	bd2x[1]=1;
	int *Cbd2x=new int[2];
	Cbd2x[0]=-1;
	Cbd2x[1]=1;
	
	//d2z
	float *ad2z=ad2x;
	int *Cad2z=new int[3];
	Cad2z[0]=-nx;
	Cad2z[1]=0;
	Cad2z[2]=nx;
	float *bd2z=bd2x;
	int *Cbd2z=new int[2];
	Cbd2z[0]=-nx;
	Cbd2z[1]=nx;
	
	//d3x
	float *ad3x = b2dx;
	int *Cad3x = Cbd2x;
	float *bd3x = new float[3];
	b3dx[0]=1;
	b3dx[1]=8;
	b3dx[2]=1
	int *Cbd3x =Cad2x;
	 
	 //d3z
	float *ad3z = b2dx;
	int *Cad3z = Cb2dz;
	float *bd3z = bd3x;
	int *Cbd3z = Cad2z;
	
	float d2xz;
	float dx2z;
	float d3xz;
	float dx3z;
	float d2x2z;
	float d4z;
	float d4x;
	float d4xz;
	float dx4z;
	float d2x3z;
	float d3x2z;
	float d5x;
	float d5z;
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
	float *fd_coeff = new float[5];
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
	
	float *C,*CC,*FD,*CFD;
	C=scalar_mult(dtdivh,vel,nrows*ncols);
	CC=vek_elmwise_mult(C,C,nrows*ncols);
	FD=fin_diff(fd_coeff,fd_coeff_coor,nrows,ncols,5,P[time_step]);
	CFD=vek_elmwise_mult(CC,FD,nrows*ncols);
	
	delete [] C;
	delete [] CC;
	delete [] FD;
	delete [] fd_coeff;
	delete [] fd_coeff_coor;
	float *A,*B,*sum;
	
	A=scalar_mult(2.0,P[time_step],nrows*ncols);
	B=vek_subtraction(A,P[time_step-1],nrows*ncols);
	sum=vek_addition(B,CFD,nrows*ncols);
	delete [] A; delete [] B;
	return sum;
	}
