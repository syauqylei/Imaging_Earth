double *A1(double h){
	double w1=2./h/h;
	double w2=-1./2./h;
	double *cf = new double [5];
	cf[0]=1*w1;
	cf[1]=-2*w1;
	cf[2]=1*w1;
	cf[3]=-1*w2;
	cf[4]=1*w2;
	return cf;
	}
double *A2(double h){
	double w1=15./2./h/h/h;
	double w2=-3./2./h/h;
	double *cf = new double [5];
	cf[0]=-1*w1;
	cf[1]=1*w1;
	cf[2]=1*w2;
	cf[3]=8*w2;
	cf[4]=1*w2;
	return cf;
}
double *A3(double h){
	double w1=1./4./h/h/h;
	double w2=1./2./h/h;
	double w3=1./h/h;
	double *cf= new double[18];
	cf[0]=-5*w1;
	cf[1]=4*w1;
	cf[2]=1*w1;
	cf[3]=6*w1;
	cf[4]=-6*w1;
	cf[5]=-1*w1;
	cf[6]=-4*w1;
	cf[7]=5*w1;
	cf[8]=-1*w2;
	cf[9]=1*w2;
	cf[10]=-2*w2;
	cf[11]=4*w2;
	cf[12]=-2*w2;
	cf[13]=1*w2;
	cf[14]=-1*w2;
	cf[15]=1*w3;
	cf[16]=-2*w3;
	cf[17]=1*w3;
	return cf;
}
int *CA1(int nx, int ny){
	int *coo = new int [5];
	coo[0]=-1;
	coo[1]=0;
	coo[2]=1;
	coo[3]=nx*ny-1;
	coo[4]=nx*ny+1;
	return coo;
	}

int *CA2(int nx, int ny){
	int *coo = new int [5];
	coo[0]=-1;
	coo[1]=1;
	coo[2]=nx*ny-1;
	coo[3]=nx*ny;
	coo[4]=nx*ny+1;
	return coo;
}
int *CA3(int nx, int ny){
	int *coo= new int[18];
	coo[0]=-nx-1;
	coo[1]=-nx;
	coo[2]=-nx+1;
	coo[3]=-1;
	coo[4]=1;
	coo[5]=nx-1;
	coo[6]=nx;
	coo[7]=nx+1;
	coo[8]=2*nx*ny-nx-1;
	coo[9]=2*nx*ny-nx;
	coo[10]=2*nx*ny-1;
	coo[11]=2*nx*ny;
	coo[12]=2*nx*ny+1;
	coo[13]=2*nx*ny+nx;
	coo[14]=2*nx*ny+nx+1;
	coo[15]=nx*ny-nx;
	coo[16]=nx*ny;
	coo[17]=nx*ny+nx;
	return coo;
}

double *B1(double h){
	double w1=2./h/h;
	double w2=-1./2./h;
	double *cf = new double [5];
	cf[0]=1*w1;
	cf[1]=-2*w1;
	cf[2]=1*w1;
	cf[3]=-1*w2;
	cf[4]=1*w2;
	return cf;
	}

double *B2(double h){
	double w1=1./4./h/h/h;
	double w2=1./2./h/h;
	double w3=1./h/h;
	double *cf= new double[18];
	cf[0]=-5*w1;
	cf[1]=6*w1;
	cf[2]=-1*w1;
	cf[3]=4*w1;
	cf[4]=-4*w1;
	cf[5]=1*w1;
	cf[6]=-6*w1;
	cf[7]=5*w1;
	cf[8]=-1*w2;
	cf[9]=-2*w2;
	cf[10]=1*w2;
	cf[11]=4*w2;
	cf[12]=1*w2;
	cf[13]=-2*w2;
	cf[14]=-1*w2;
	cf[15]=1*w3;
	cf[16]=-2*w3;
	cf[17]=1*w3;
	return cf;
}
double *B3(double h){
	double w1=15./2./h/h/h;
	double w2=-3./2./h/h;
	double *cf = new double [5];
	cf[0]=-1*w1;
	cf[1]=1*w1;
	cf[2]=1*w2;
	cf[3]=8*w2;
	cf[4]=1*w2;
	return cf;
}
int *CB1(int nx, int ny){
	int *coo = new int [5];
	coo[0]=-nx;
	coo[1]=0;
	coo[2]=nx;
	coo[3]=nx*ny-nx;
	coo[4]=nx*ny+nx;
	return coo;
	}

int *CB2(int nx, int ny){
	int *coo= new int[18];
	coo[0]=-nx-1;
	coo[1]=-nx;
	coo[2]=-nx+1;
	coo[3]=-1;
	coo[4]=1;
	coo[5]=nx-1;
	coo[6]=nx;
	coo[7]=nx+1;
	coo[8]=nx*ny-nx-1;
	coo[9]=nx*ny-nx;
	coo[10]=nx*ny-1;
	coo[11]=nx*ny;
	coo[12]=nx*ny+1;
	coo[13]=nx*ny+nx;
	coo[14]=nx*ny+nx+1;
	coo[15]=2*nx*ny-1;
	coo[16]=2*nx*ny;
	coo[17]=2*nx*ny+1;
	return coo;
}

int *CB3(int nx, int ny){
	int *coo = new int [5];
	coo[0]=-nx;
	coo[1]=nx;
	coo[2]=2*nx*ny-nx;
	coo[3]=2*nx*ny;
	coo[4]=2*nx*ny+nx;
	return coo;
}

double *C1(double h){
	double w1=-12./h/h/h/h;
	double w2=6./h/h/h;
	double *cf = new double [5];
	cf[0]=1*w1;
	cf[1]=-2*w1;
	cf[2]=1*w1;
	cf[3]=-1*w2;
	cf[4]=1*w2;
	return cf;
	}
double *C2(double h){
	double w1=-90./h/h/h/h/h;
	double w2=30./h/h/h/h;
	double *cf = new double [5];
	cf[0]=1*w1;
	cf[1]=-1*w1;
	cf[2]=1*w2;
	cf[3]=4*w2;
	cf[4]=1*w2;
	return cf;
	}
double *C3(double h){
	double w1=-3./h/h/h/h/h;
	double w2=6./h/h/h/h;
	double *cf= new double[15];
	cf[0]=-5*w1;
	cf[1]=4*w1;
	cf[2]=1*w1;
	cf[3]=6*w1;
	cf[4]=-6*w1;
	cf[5]=-1*w1;
	cf[6]=-4*w1;
	cf[7]=5*w1;
	cf[8]=1*w2;
	cf[9]=-1*w2;
	cf[10]=2*w2;
	cf[11]=-4*w2;
	cf[12]=2*w2;
	cf[13]=-1*w2;
	cf[14]=1*w2;
	return cf;
}

int *CC1(int nx,int ny){
	int *coo = new int [5];
	coo[0]=-1;
	coo[1]=0;
	coo[2]=1;
	coo[3]=nx*ny-1;
	coo[4]=nx*ny+1;
	return coo;
	}

int *CC2(int nx,int ny){
	int *coo = new int [5];
	coo[0]=-1;
	coo[1]=1;
	coo[2]=nx*ny-1;
	coo[3]=nx*ny;
	coo[4]=nx*ny+1;
	return coo;
	}

int *CC3(int nx,int ny){
	int *coo = new int [15];
	coo[0]=-nx-1;
	coo[1]=-nx;
	coo[2]=-nx+1;
	coo[3]=-1;
	coo[4]=1;
	coo[5]=nx-1;
	coo[6]=nx;
	coo[7]=nx+1;
	coo[8]=ny*nx-nx-1;
	coo[9]=ny*nx-nx;
	coo[10]=ny*nx-1;
	coo[11]=ny*nx;
	coo[12]=ny*nx+1;
	coo[13]=ny*nx+nx;
	coo[14]=ny*nx+nx+1;
	return coo;
	}

double *D1(double h){
	double w1=-12./h/h/h/h;
	double w2=6./h/h/h;
	double *cf = new double [5];
	cf[0]=1*w1;
	cf[1]=-2*w1;
	cf[2]=1*w1;
	cf[3]=-1*w2;
	cf[4]=1*w2;
	return cf;
	}

double *D2(double h){
	double w1=-3./h/h/h/h/h;
	double w2=6./h/h/h/h;
	double *cf = new double [15];
	cf[0]=-5*w1;
	cf[1]=6*w1;
	cf[2]=-1*w1;
	cf[3]=4*w1;
	cf[4]=-4*w1;
	cf[5]=1*w1;
	cf[6]=-6*w1;
	cf[7]=5*w1;
	cf[8]=1*w2;
	cf[9]=-1*w2;
	cf[10]=2*w2;
	cf[11]=-4*w2;
	cf[12]=2*w2;
	cf[13]=-1*w2;
	cf[14]=1*w2;
	return cf;
	}

double *D3( double h){
	double w1=-90./h/h/h/h/h;
	double w2=30./h/h/h/h;
	double *cf= new double[5];
	cf[0]=-1*w1;
	cf[1]=1*w1;
	cf[2]=1*w2;
	cf[3]=4*w2;
	cf[4]=1*w2;
	return cf;
	}

int *CD1(int nx,int ny){
	int *coo=new int [5];
	coo[0]=-nx;
	coo[1]=0;
	coo[2]=nx;
	coo[3]=2*nx*ny-nx;
	coo[4]=2*nx*ny+nx;
	return coo;
	}

int *CD2(int nx, int ny){
	int *coo= new int[15];
	coo[0]=-nx-1;
	coo[1]=-nx;
	coo[2]=-nx+1;
	coo[3]=-1;
	coo[4]=1;
	coo[5]=nx-1;
	coo[6]=nx;
	coo[7]=nx+1;
	coo[8]=2*ny*nx-nx-1;
	coo[9]=2*ny*nx-nx;
	coo[10]=2*ny*nx-1;
	coo[11]=2*ny*nx;
	coo[12]=2*ny*nx+1;
	coo[13]=2*ny*nx+nx;
	coo[14]=2*ny*nx+nx+1;
	return coo;
	}

int *CD3(int nx,int ny){
	int *coo=new int [5];
	coo[0]=-nx;
	coo[1]=nx;
	coo[2]=2*nx*ny-nx;
	coo[3]=2*nx*ny;
	coo[4]=2*nx*ny+nx;
	return coo;
	}

double *E1(double h){
	double w1=1./4./h/h/h/h;
	double *cf = new double [9];
	cf[0]=1*w1;
	cf[1]=-2*w1;
	cf[2]=1*w1;
	cf[3]=-2*w1;
	cf[4]=4*w1;
	cf[5]=-2*w1;
	cf[6]=1*w1;
	cf[7]=-2*w1;
	cf[8]=1*w1;
	return cf;
	}

double *E2(double h){
	double w1=3.0/h/h/h/h/h;
	double w2=-6.0/h/h/h/h;
	double *cf = new double[9];
	cf[0]=-1*w1;
	cf[1]=1*w1;
	cf[2]=2*w1;
	cf[3]=-2*w1;
	cf[4]=-1*w1;
	cf[5]=1*w1;
	cf[6]=1*w2;
	cf[7]=-2*w2;
	cf[8]=1*w2;
	return cf;
	}


double *E3(double h){
	double w1=3./h/h/h/h/h;
	double w2=-6./h/h/h/h;
	double *cf = new double[9];
	cf[0]=-1*w1;
	cf[1]=2*w1;
	cf[2]=-1*w1;
	cf[3]=1*w1;
	cf[4]=-2*w1;
	cf[5]=1*w1;
	cf[6]=1*w2;
	cf[7]=-2*w2;
	cf[8]=1*w2;
	return cf;
	}

int *CE1(int nx , int ny){
	int *coo= new int [9];
	coo[0]=-nx-1;
	coo[1]=-nx;
	coo[2]=-nx+1;
	coo[3]=-1;
	coo[4]=0;
	coo[5]=1;
	coo[6]=nx-1;
	coo[7]=nx;
	coo[8]=nx+1;
	return coo;
	}

int *CE2(int nx, int ny){
	int *coo =  new int [9];
	coo[0]=-nx-1;
	coo[1]=-nx+1;
	coo[2]=-1;
	coo[3]=1;
	coo[4]=nx-1;
	coo[5]=nx+1;
	coo[6]=nx*ny-nx;
	coo[7]=nx*ny;
	coo[8]=nx*ny+nx;
	return coo;
	}

int *CE3(int nx, int ny){
	int *coo =  new int [9];
	coo[0]=-nx-1;
	coo[1]=-nx;
	coo[2]=-nx+1;
	coo[3]=nx-1;
	coo[4]=nx;
	coo[5]=nx+1;
	coo[6]=2*nx*ny-1;
	coo[7]=2*nx*ny;
	coo[8]=2*nx*ny+1;
	return coo;
	}
