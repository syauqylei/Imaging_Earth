
double dx(double *U,int i, int nx,double h){
	double hd;
	hd=(U[i+1]-U[i-1])/2.0/h;
	return hd;
	}
double dy(double *U,int i, int nx,double h){
	double hd;
	hd=(U[i+nx]-U[i-nx])/2.0/h;
	return hd;
	}
	
double d2xd2y(double *U,int i, int nx,double h){
	double hd;
	hd=(U[i-1]+U[i+1]+U[i-nx]+U[i+nx]-4.0*U[i])/h/h;
	return hd;
	}


double d4x(double *U,double *Ux,int i, int nx,double h){
	double hd;
	hd=-12.0/h/h/h/h*(U[i+1]-2.0*U[i]+U[i-1])+(Ux[i+1]-Ux[i-1])*6.0/h/h/h;
	return hd;
	}

double d4y(double *U,double *Uy,int i, int nx,double h){
	double hd;
	hd=-12.0/h/h/h/h*(U[i+nx]-2.0*U[i]+U[i-nx])+6.0/h/h/h*(Uy[i+nx]-Uy[i-nx]);
	return hd;
	}
	
double d5x(double *U,double *Ux,int i, int nx,double h){
	double hd;
	hd=-90.0/h/h/h/h/h*(U[i+1]-U[i-1])+30.0/h/h/h/h*(Ux[i+1]+4.0*Ux[i]+Ux[i-1]);
	return hd;
	}
	
double d5y(double *U,double *Uy,int i, int nx,double h){
	double hd;
	hd=-90.0/h/h/h/h/h*(U[i+nx]-U[i-nx])+30.0/h/h/h/h*(Uy[i+nx]+4.0*Uy[i]+Uy[i-nx]);
	return hd;
	}

double d2x2y(double *U,double *Ux, double *Uy,int i, int nx,double h){
	double hd;
	hd=1.0/h/h/h/h*(2.0*(U[i+nx]+U[i+1]-2.0*U[i]+U[i-1]+U[i-nx])
					- U[i-nx+1]-U[i-nx-1]-U[i+nx+1]-U[i+nx-1])
		+1.0/2.0/h/h/h*(Ux[i+nx+1]+Ux[i-nx+1]-Ux[i-nx-1]-Ux[i+nx-1]-2.0*Ux[i+1]+2.0*Ux[i-1])
		+1.0/2.0/h/h/h*(Uy[i+nx+1]+Uy[i+nx-1]-Uy[i-nx-1]-Uy[i-nx+1]-2.0*Uy[i+nx]+2.0*Uy[i-nx]);
	return hd;
	}

double d3x2y(double *U,double *Ux,int i, int nx,double h){
	double hd;
	hd=-3.0/2.0/h/h/h/h/h*(U[i+nx+1]-U[i-1-nx]+U[i+1-nx]-U[i-1+nx]+2.0*U[i-1]-2.0*U[i+1])
		+3.0/2.0/h/h/h/h*(Ux[i+nx+1]+Ux[i-nx-1]+Ux[i+nx-1]+Ux[i-nx+1]-2.0*Ux[i+1]-2.0*Ux[i-1]);
	return hd;
	}

double d2x3y(double *U,double *Uy,int i, int nx,double h){
	double hd;
	hd=-3.0/2.0/h/h/h/h/h*(U[i+nx+1]-U[i-1-nx]+U[i-1+nx]-U[i+1-nx]+2.0*U[i-nx]-2.0*U[i+nx])
		+3.0/2.0/h/h/h/h*(Uy[i+nx+1]+Uy[i-nx-1]+Uy[i+nx-1]+Uy[i-nx+1]-2.0*Uy[i+nx]-2.0*Uy[i-nx]);
	return hd;
	}

double d4xy(double *U,double *Ux,int i, int nx,double h){
	double hd;
	hd=-6.0/h/h/h/h/h*(U[i+nx+1]-U[i-1-nx]+U[i-1+nx]-U[i+1-nx]+2.0*U[i-nx]-2.0*U[i+nx])
		+3.0/h/h/h/h*(Ux[i+nx+1]+Ux[i-nx-1]-Ux[i+nx-1]-Ux[i-nx+1]);
	return hd;
	}

double dx4y(double *U,double *Uy,int i, int nx,double h){
	double hd;
	hd=-6.0/h/h/h/h/h*(U[i+nx+1]-U[i-1-nx]-U[i-1+nx]+U[i+1-nx]+2.0*U[i-1]-2.0*U[i+1])
		+3.0/h/h/h/h*(Uy[i+nx+1]+Uy[i-nx-1]-Uy[i+nx-1]-Uy[i-nx+1]);
	return hd;
	}
