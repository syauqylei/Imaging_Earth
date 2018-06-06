#include <iostream>
#include <cmath>
#include "coeff.h"

const double b = 0.4;

double qx(double bta,double cfv){
	double rslt=(b*(bta+cfv)-cfv)/((bta+cfv)*(1-b));
	return rslt;
	}

double qt(double bta,double cfv){
	double rslt=(b*(bta+cfv)-bta)/((bta+cfv)*(1-b));
	return rslt;
	}

double hiabc(double **U,int t,int s, int sdifopr, double cfl,double *beta,int ndeg){
	
	double abc_eq[ndeg][4];
	double qxt=b/(b-1);
	
	for (int i=0;i<ndeg;i++){
			abc_eq[i][0]=1;
			abc_eq[i][1]=qx(beta[i],cfl);
			abc_eq[i][2]=qt(beta[i],cfl);
			abc_eq[i][3]=qxt;
		}
	
	int nelement=int(pow(4,ndeg));
	double cff[nelement];
	cff[0]=abc_eq[0][0];
	cff[1]=abc_eq[0][1];
	cff[2]=abc_eq[0][2];
	cff[3]=abc_eq[0][3];
	
	int topr[nelement];
	topr[0]=0;
	topr[1]=0;
	topr[2]=-1;
	topr[3]=-1;
	
	int sopr[nelement];
	sopr[0]=0;
	sopr[1]=sdifopr;
	sopr[2]=0;
	sopr[3]=sdifopr;
	
	int iter[ndeg-1];
	for (int i=0;i<ndeg-1;i++){
		iter[i]=int(pow(4,i+1));
		}
	
	for (int i=0;i<ndeg-1;i++){
		for (int j=0; j<3;j++){
			for (int k=0; k<iter[i];k++){
				sopr[iter[i]+j*iter[i]+k]=sopr[k]+sopr[j+1];
				cff[iter[i]+j*iter[i]+k]=cff[k]*abc_eq[i+1][j+1];
				topr[iter[i]+j*iter[i]+k]=topr[k]+topr[j+1];
				}
			}
		}
	
		
	cff[0]=0;
	
	double u=0;
	int tdf;
	int sdf;
	for (int i=0; i<nelement;i++){
		sdf=s+sopr[i];
		if(t+topr[i]<0){tdf=0;}
		else {tdf=t+topr[i];}
		u+=-U[tdf][sdf]*cff[i];
		}
	return u;
	}
