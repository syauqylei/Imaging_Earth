#include <cmath>
#include "coeff.h"

const double b = 0.5;

double qx(double bta,double cfv){
	double rslt=(b*(bta+cfv)-cfv)/((bta+cfv)*(1-b));
	return rslt;
	}

double qt(double bta,double cfv){
	double rslt=(b*(bta+cfv)-bta)/((bta+cfv)*(1-b));
	return rslt;
	}

double hiabc(double *U, double cfv,int k,int i,int polar){
	double beta[4]={0.99,0.79,0.52,0.31};
	double abc_eq[4][4];
	double qxt=b/(b-1);
	
	for (int i=0;i<4;i++){
			abc_eq[i][0]=1;
			abc_eq[i][1]=qx(beta[i],cfv);
			abc_eq[i][2]=qt(beta[i],cfv);
			abc_eq[i][3]=qxt;
		}
	double abcd[256];
	abcd[0]=abc[0][0];
	abcd[1]=abc[0][1];
	abcd[2]=abc[0][2];
	abcd[3]=abc[0][3];
	
	int iter[3]={4,16,64};
	for (int i=0;i<3;i++){
		for (int j=0; j<3;j++){
			for (int k=0; k<iter[i];k++){
				abcd[iter[i]+]=abcd[k]*abc_eq[i+1][j];
				}
			}
		}
	
	int topr[4]={0,0,-1,-1};
	
	int spasopr[4];
	spasopr[0]=0;
	spasopr[1]=polar;
	spasopr[2]=0;
	spasopr[3]=polar;
	
	double u;
	return u;
	}
