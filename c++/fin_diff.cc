#include "arrayopr.h"
#include "arrayman.h"
#include "source_function.h"
#include "fin_diff_opr.h"
#include <iostream>

double *fd_2d(double *fd_coeff,double *fd_coeff_coor,int ny,int nx,int npoints,double *val){
	double *fd_val=new double[ny*nx];
	int aab;
	for (int i=0;i<ny;i++){
		for (int j =0; j<nx;j++){
			for(int k=0;k<npoints;k++){
				aab=i*nx+j+fd_coeff_coor[k];
				if(aab==i*nx-1 && i*nx+j == i*nx ){continue;}
				if(aab==(i+1)*nx && i*nx+j == (i+1)*nx-1 ){continue;}
				if(aab < 0 || aab > nx*ny-1 ){continue;}
				if(aab==i*nx && i*nx+j == (i+1)*nx-1 ){continue;}
				if(aab==(i+2)*nx && i*nx+j == (i+1)*nx-1 ){continue;}
				if(aab==(i-1)*nx-1 && i*nx+j == i*nx ){continue;}
				if(aab==(i+1)*nx-1 && i*nx+j == i*nx ){continue;}
				fd_val[i*nx+j]+=val[aab]*fd_coeff[k];

			}
		}	
	}
	return fd_val;
}

double *Wve_spas(double **P,double *vel,const double dtdivh,int time_step,const int ny,const int nx){

	hd2d hd;
	hd = input((double)nx);
	
	double *C,*CC,*FD,*CFD;
	C=scalar_mult(dtdivh,vel,ny*nx);
	CC=vek_elmwise_mult(C,C,ny*nx);
	FD=fd_2d(hd.fd_cf,hd.fd_cf_coo,ny,nx,5,P[time_step]);
	CFD=vek_elmwise_mult(CC,FD,ny*nx);
	delete [] C;
	delete [] CC;
	delete [] FD;
	double *A,*B,*sum;
	
	A=scalar_mult(2.0,P[time_step],ny*nx);
	B=vek_subtraction(A,P[time_step-1],ny*nx);
	sum=vek_addition(B,CFD,ny*nx);
	delete [] A; delete [] B;
	return sum;
	}

double **Wve_tim(double **P,double *Vel_mod,double h,double dt,double fmax, int src_loc,int nt, int ny,int nx ){
	double t;
	double f_src[ny*nx]={0};
	double *wve_prog;
	for( int i=1;i<nt-1;i++){
		t=i*dt;
		// add source term
		f_src[src_loc]=ricker_wavelet(fmax,t);
		wve_prog=Wve_spas(P,Vel_mod,dt/h,i,ny,nx);
		P[i+1]=vek_addition(wve_prog,f_src,ny*nx);
		/*
		std::cout << " Time : " << t;
		std::cout << " \t Wavefield Value : " << P[i+1][src_loc];
		std::cout << " \t Source Value = "<<ricker_wavelet(fmax,t)<<std::endl;	*/
	}
	delete [] wve_prog;
	return P;
}

double *cdth2(double *Vel_Mod,double dt,double h,int nx,int ny, int nz){
	double *Cdth2=new double [nx*nz*ny];
	for(int i=0; i<nz;i++){
		for (int j=0; j<ny; j++){
			for (int k=0; k<nx;k++){
				Cdth2[i*nx*ny+j*nx+k]=Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]*dt*dt/h/h;
				}
			}
		}
	return Cdth2;
	}

double *cdth4(double *Vel_Mod,double dt,double h,int nx,int ny, int nz){
	double *Cdth4=new double[nx*nz*ny];
	for(int i=0; i<nz;i++){
		for (int j=0; j<ny; j++){
			for (int k=0; k<nx;k++){
				Cdth4[i*nx*ny+j*nx+k]=Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]
				*Vel_Mod[i*nx*ny+j*nx+k]*Vel_Mod[i*nx*ny+j*nx+k]*dt*dt*dt*dt/h/h/h/h;
				}
			}
		}
	return Cdth4;
	}

double fd_2d_opr(double *P,int i,double *coeff,double *coeff_coo,int nx, int ny,int nstencil){
	double val=0;
	for (int k=0; k < nstencil; k++){
		if ( i+coeff_coo[k]< 0 || i+coeff_coo[k]< ny*nx-1){continue;}
		if ( i%nx == 0){
			if ( coeff_coo[k] == -1 || coeff_coo[k]==-nx-1){continue;}}
		if ( i%nx == nx-1){
			if ( coeff_coo[k] == 1 || coeff_coo[k]==+nx+1){continue;}}
		val+=P[i+(int)coeff_coo[k]]*coeff[k];
		}
	return val;
	}

double **Wve_conv_fd(int src_loc, double freq,double *Vel_Mod,double h, double dt,int nt,int nx,int ny){
	double **P=alloc_mat(nt,nx*ny);
	double *CDTH2=cdth2(Vel_Mod,dt,h,nx,ny,1);
	hd2d hd;
	
	hd = input((double)nx);
	
	//Time-step loop
	for (int i=1;i<nt-1;i++){
		double t=i*dt;
		//add source term
		P[i+1][src_loc]+=ricker_wavelet(freq,t);
		std::cout<<"time step "<<t<<"source "<<P[i+1][src_loc]<<std::endl;
		for(int j=0;j<nx*ny;j++){
			P[i+1][j]=2.0*P[i][j]-P[i-1][j]+
			CDTH2[j]*((/* d2x */ 
						2.0/h/h*fd_2d_opr(P[i],j,hd.ad2x,hd.Cad2x,nx,ny,3)+
						1.0/2.0/h*fd_2d_opr(P[i],j,hd.bd2x,hd.Cbd2x,nx,ny,2))
					+ (/* d2z */
						2.0/h/h*fd_2d_opr(P[i],j,hd.ad2y,hd.Cad2y,nx,ny,3)+
						1.0/2.0/h*fd_2d_opr(P[i],j,hd.bd2y,hd.Cbd2y,nx,ny,2)));
			}
		}
	delete [] CDTH2;
	return P;
	}


/*
double *lap2d(double *P,double *Px,double *Py,double h,int nx,int ny){
	hd2d HD;
	double *lap2d= new double [nx*ny];
	double *ad2x=fd_2d(HD.ad2x,HD.Cad2x,ny,nx,3,P);
	double *bd2x=fd_2d(HD.bd2x,HD.Cbd2x,ny,nx,2,Px);
	double *ad2y=fd_2d(HD.ad2y,HD.Cad2y,ny,nx,3,P);
	double *bd2y=fd_2d(HD.bd2y,HD.Cbd2y,ny,nx,2,Py);
	
	for (int i=0; i<ny; i++){
		for (int j=0; j<nx; j++){
			lap2d[i*nx+j]=ad2x[i*nx+j]*2.0/h/h-bd2x[i*nx+j]/2.0/h+
						  ad2y[i*nx+j]*2.0/h/h-bd2y[i*nx+j]/2.0/h;
			}
		}
		
	delete [] ad2x;
	delete [] bd2x;
	delete [] ad2y;
	delete [] bd2y;
	return lap2d;
	}

double *lap2d2(double *P,double *Px,double *Py,double h,int nx,int ny){
	hd2d HD;
	double *lap2d= new double [nx*ny];
	double *ad4x=fd_2d(HD.ad2x,HD.Cad2x,ny,nx,3,P);
	double *bd4x=fd_2d(HD.bd2x,HD.Cbd2x,ny,nx,2,Px);
	double *ad4y=fd_2d(HD.ad2y,HD.Cad2y,ny,nx,3,P);
	double *bd4y=fd_2d(HD.bd2y,HD.Cbd2y,ny,nx,2,Py);
	double *d2x2y=fd_2d(HD.d2x2y,HD.Cd2x2y,ny,nx,3,P);
	
	for (int i=0; i<ny; i++){
		for (int j=0; j<nx; j++){
			lap2d[i*nx+j]=ad4x[i*nx+j]*-12.0/h/h/h/h-bd4x[i*nx+j]*6.0/h/h/h+
						  ad4y[i*nx+j]*-12.0/h/h/h/h-bd4y[i*nx+j]*6.0/h/h/h+
						  d2x2y[i*nx+j]/h/h/h/h;
			}
		}
		
	delete [] ad4x;
	delete [] bd4x;
	delete [] ad4y;
	delete [] bd4y;
	delete [] d2x2y;
	return lap2d;
	}
*/
