double d2xd2yd2z(double *U,int i, int nx,int ny,double h){
	double hd;
	hd=(U[i-1]+U[i+1]+U[i-nx]+U[i+nx]+U[i-nx*ny]+U[i+nx*ny]-6.0*U[i])/h/h;
	return hd;
	}


double d4x(double *U,double *Ux,int i,double h){
	double hd;
	hd=-12.0/h/h/h/h*(U[i+1]-2.0*U[i]+U[i-1])+(Ux[i+1]-Ux[i-1])*6.0/h/h/h;
	return hd;
	}

double d4y(double *U,double *Uy,int i, int nx,double h){
	double hd;
	hd=-12.0/h/h/h/h*(U[i+nx]-2.0*U[i]+U[i-nx])+6.0/h/h/h*(Uy[i+nx]-Uy[i-nx]);
	return hd;
	}
	
double d4z(double *U,double *Uz,int i, int nx,int ny,double h){
	double hd;
	hd=-12.0/h/h/h/h*(U[i+nx*ny]-2.0*U[i]+U[i-nx*ny])+6.0/h/h/h*(Uz[i+nx*ny]-Uz[i-nx*ny]);
	return hd;
	}
	
double d5x(double *U,double *Ux,int i,double h){
	double hd;
	hd=-90.0/h/h/h/h/h*(U[i+1]-U[i-1])+30.0/h/h/h/h*(Ux[i+1]+4.0*Ux[i]+Ux[i-1]);
	return hd;
	}
	
double d5y(double *U,double *Uy,int i, int nx,double h){
	double hd;
	hd=-90.0/h/h/h/h/h*(U[i+nx]-U[i-nx])+30.0/h/h/h/h*(Uy[i+nx]+4.0*Uy[i]+Uy[i-nx]);
	return hd;
	}

double d5z(double *U,double *Uz,int i, int nx,int ny, double h){
	double hd;
	hd=-90.0/h/h/h/h/h*(U[i+nx*ny]-U[i-nx*ny])+30.0/h/h/h/h*(Uz[i+nx*ny]+4.0*Uz[i]+Uz[i-nx*ny]);
	return hd;
	}
	
double d2x2y(double *U,double *Ux, double *Uy,int i, int nx,double h){
	double hd;
	hd=1.0/h/h/h/h*(U[i+nx+1]+U[i-nx-1]+U[i+nx-1]+U[i-nx+1]+4.0*U[i]
					-2.0*U[i+1]-2.0*U[i-1]-2.0*U[i+nx]-2.0*U[i-nx])
		-1.0/2.0/h/h/h*(Ux[i+nx+1]-Ux[i-nx-1]+Ux[i-nx+1]-Ux[i+nx-1]-2.0*Ux[i+1]+2.0*Ux[i-1])
		-1.0/2.0/h/h/h*(Uy[i+nx+1]-Uy[i-nx-1]-Uy[i-nx+1]+Uy[i+nx-1]-2.0*Uy[i+nx]+2.0*Uy[i-nx]);
	return hd;
	}

double d2x2z(double *U,double *Ux, double *Uz,int i, int nx, int ny,double h){
	double hd;
	hd=1.0/h/h/h/h*(U[i+nx*ny+1]+U[i-nx*ny-1]+U[i+nx*ny-1]+U[i-nx*ny+1]+4.0*U[i]
					-2.0*U[i+1]-2.0*U[i-1]-2.0*U[i+nx*ny]-2.0*U[i-nx*ny])
		-1.0/2.0/h/h/h*(Ux[i+nx*ny+1]-Ux[i-nx*ny-1]+Ux[i-nx*ny+1]-Ux[i+nx*ny-1]-2.0*Ux[i+1]+2.0*Ux[i-1])
		-1.0/2.0/h/h/h*(Uz[i+nx*ny+1]-Uz[i-nx*ny-1]-Uz[i-nx*ny+1]+Uz[i+nx*ny-1]-2.0*Uz[i+nx*ny]+2.0*Uz[i-nx*ny]);
	return hd;
	}

double d2y2z(double *U,double *Uy, double *Uz,int i, int nx,int ny,double h){
	double hd;
	hd=1.0/h/h/h/h*(U[i+nx+nx*ny]+U[i-nx-nx*ny]+U[i+nx-nx*ny]+U[i-nx+nx*ny]+4.0*U[i]
					-2.0*U[i+nx*ny]-2.0*U[i-nx*ny]-2.0*U[i+nx]-2.0*U[i-nx])
		-1.0/2.0/h/h/h*(Uy[i+nx+nx*ny]-Uy[i-nx-nx*ny]+Uy[i+nx-nx*ny]-Uy[i-nx+nx*ny]-2.0*Uy[i+nx]+2.0*Uy[i-nx])
		-1.0/2.0/h/h/h*(Uz[i+nx+nx*ny]-Uz[i-nx-nx*ny]-Uz[i+nx-nx*ny]+Uz[i-nx+nx*ny]-2.0*Uz[i+nx*ny]+2.0*Uz[i-nx*ny]);
	return hd;
	}
	
double d3x2y(double *U,double *Ux,int i, int nx,double h){
	double hd;
	hd=-3.0/2.0/h/h/h/h/h*(U[i+nx+1]-U[i-1-nx]+U[i+1-nx]-U[i-1+nx]+2.0*U[i-1]-2.0*U[i+1])
		+3.0/2.0/h/h/h/h*(Ux[i+nx+1]+Ux[i-nx-1]+Ux[i+nx-1]+Ux[i-nx+1]-2.0*Ux[i+1]-2.0*Ux[i-1]);
	return hd;
	}

double d3x2z(double *U,double *Uz,int i, int nx,int ny,double h){
	double hd;
	hd=-3.0/2.0/h/h/h/h/h*(U[i+1+nx*ny]-U[i-1-nx*ny]+U[i+1-nx*ny]-U[i-1+nx*ny]+2.0*U[i-1]-2.0*U[i+1])
		+3.0/2.0/h/h/h/h*(Uz[i+nx*ny+1]+Uz[i-nx*ny-1]+Uz[i+nx*ny-1]+Uz[i-nx*ny+1]-2.0*Uz[i+1]-2.0*Uz[i-1]);
	return hd;
	}

double d2x3y(double *U,double *Uy,int i, int nx,double h){
	double hd;
	hd=-3.0/2.0/h/h/h/h/h*(U[i+nx+1]-U[i-1-nx]+U[i-1+nx]-U[i+1-nx]+2.0*U[i-nx]-2.0*U[i+nx])
		+3.0/2.0/h/h/h/h*(Uy[i+nx+1]+Uy[i-nx-1]+Uy[i+nx-1]+Uy[i-nx+1]-2.0*Uy[i+nx]-2.0*Uy[i-nx]);
	return hd;
	}

double d3y2z(double *U,double *Uz,int i, int nx,int ny, double h){
	double hd;
	hd=-3.0/2.0/h/h/h/h/h*(U[i+nx*ny+nx]-U[i-nx-nx*ny]+U[i-nx+nx*ny]-U[i+nx-nx*ny]+2.0*U[i-nx]-2.0*U[i+nx])
		+3.0/2.0/h/h/h/h*(Uz[i+nx*ny+nx]+Uz[i-nx*ny-nx]+Uz[i+nx*ny-nx]+Uz[i-nx*ny+nx]-2.0*Uz[i+nx]-2.0*Uz[i-nx]);
	return hd;
	}

double d2x3z(double *U,double *Uz,int i, int nx,int ny,double h){
	double hd;
	hd=-3.0/2.0/h/h/h/h/h*(U[i+nx*ny+1]-U[i-1-nx*ny]+U[i-1+nx*ny]-U[i+1-nx*ny]+2.0*U[i-nx*ny]-2.0*U[i+nx*ny])
		+3.0/2.0/h/h/h/h*(Uz[i+nx*ny+1]+Uz[i-nx*ny-1]+Uz[i+nx*ny-1]+Uz[i-nx*ny+1]-2.0*Uz[i+nx*ny]-2.0*Uz[i-nx*ny]);
	return hd;
	}

double d2y3z(double *U,double *Uz,int i, int nx, int ny,double h){
	double hd;
	hd=-3.0/2.0/h/h/h/h/h*(U[i+nx+nx*ny]-U[i-nx*ny-nx]+U[i-nx*ny+nx]-U[i+nx*ny-nx]+2.0*U[i-nx*ny]-2.0*U[i+nx*ny])
		+3.0/2.0/h/h/h/h*(Uz[i+nx+nx*ny]+Uz[i-nx-nx*ny]+Uz[i+nx-nx*ny]+Uz[i-nx+nx*ny]-2.0*Uz[i+nx*ny]-2.0*Uz[i-nx*ny]);
	return hd;
	}

double d4xy(double *U,double *Ux,int i, int nx,double h){
	double hd;
	hd=-6.0/h/h/h/h/h*(U[i+nx+1]-U[i-1-nx]+U[i-1+nx]-U[i+1-nx]+2.0*U[i-nx]-2.0*U[i+nx])
		+3.0/h/h/h/h*(Ux[i+nx+1]+Ux[i-nx-1]-Ux[i+nx-1]-Ux[i-nx+1]);
	return hd;
	}

double d4xz(double *U,double *Ux,int i, int nx,int ny,double h){
	double hd;
	hd=-6.0/h/h/h/h/h*(U[i+nx*ny+1]-U[i-1-nx*ny]+U[i-1+nx*ny]-U[i+1-nx*ny]+2.0*U[i-nx*ny]-2.0*U[i+nx*ny])
		+3.0/h/h/h/h*(Ux[i+nx*ny+1]+Ux[i-nx*ny-1]-Ux[i+nx*ny-1]-Ux[i-nx*ny+1]);
	return hd;
	}
double dx4y(double *U,double *Uy,int i, int nx,double h){
	double hd;
	hd=-6.0/h/h/h/h/h*(U[i+nx+1]-U[i-1-nx]-U[i-1+nx]+U[i+1-nx]+2.0*U[i-1]-2.0*U[i+1])
		+3.0/h/h/h/h*(Uy[i+nx+1]+Uy[i-nx-1]-Uy[i+nx-1]-Uy[i-nx+1]);
	return hd;
	}

double d4yz(double *U,double *Uy,int i, int nx,int ny,double h){
	double hd;
	hd=-6.0/h/h/h/h/h*(U[i+nx+nx*ny]-U[i-nx*ny-nx]-U[i-nx*ny+nx]+U[i+nx*ny-nx]+2.0*U[i-nx*ny]-2.0*U[i+nx*ny])
		+3.0/h/h/h/h*(Uy[i+nx+nx*ny]+Uy[i-nx-nx*ny]-Uy[i+nx-nx*ny]-Uy[i-nx+nx*ny]);
	return hd;
	}

double dx4z(double *U,double *Uz,int i, int nx,int ny,double h){
	double hd;
	hd=-6.0/h/h/h/h/h*(U[i+nx*ny+1]-U[i-1-nx*ny]-U[i-1+nx*ny]+U[i+1-nx*ny]+2.0*U[i-1]-2.0*U[i+1])
		+3.0/h/h/h/h*(Uz[i+nx*ny+1]+Uz[i-nx*ny-1]-Uz[i+nx*ny-1]-Uz[i-nx*ny+1]);
	return hd;
	}

double dy4z(double *U,double *Uz,int i, int nx,int ny,double h){
	double hd;
	hd=-6.0/h/h/h/h/h*(U[i+nx+nx*ny]-U[i-nx*ny-nx]-U[i-nx*ny+nx]+U[i+nx*ny-nx]+2.0*U[i-nx*ny]-2.0*U[i+nx*ny])
		+3.0/h/h/h/h*(Uz[i+nx+nx*ny]+Uz[i-nx-nx*ny]-Uz[i+nx-nx*ny]-Uz[i-nx+nx*ny]);
	return hd;
	}

double d2x2yz(double *U,double *Ux, double *Uy, double *Uz,int i, int nx,int ny,double h){
	double hd;
	hd=1.0/4.0/h/h/h/h/h*(3.0*(U[i-1-nx-nx*ny]-U[i-1-nx+nx*ny]+U[i-1+nx-nx*ny]-U[i-1+nx+nx*ny]
								+U[i+1-nx-nx*ny]-U[i+1-nx+nx*ny]+U[i+1+nx-nx*ny]-U[i+1+nx+nx*ny])
							-6.0*(U[i-1-nx*ny]-U[i-1+nx*ny]+U[i-nx-nx*ny]-U[i-nx+nx*ny]
								+U[i+nx-nx*ny]-U[i+nx+nx*ny]+U[i+1-nx*ny]-U[i+1+nx*ny])
							+12.0*(U[i-nx*ny]-U[i+nx*ny]))
		+1.0/4.0/h/h/h/h*((Ux[i-1-nx-nx*ny]-Ux[i-1-nx+nx*ny]+Ux[i-1+nx-nx*ny]-Ux[i-1+nx+nx*ny]
							-Ux[i+1-nx-nx*ny]+Ux[i+1-nx+nx*ny]-Ux[i+1+nx-nx*ny]+Ux[i+1+nx+nx*ny])
							-2.0*(Ux[i-1-nx*ny]-Ux[i-1+nx*ny]-Ux[i+1-nx*ny]+Ux[i+1+nx*ny]))
		+1.0/4.0/h/h/h/h*((Uy[i-1-nx-nx*ny]-Uy[i-1-nx+nx*ny]-Uy[i-1+nx-nx*ny]+Uy[i-1+nx+nx*ny]
							+Uy[i+1-nx-nx*ny]-Uy[i+1-nx+nx*ny]-Uy[i+1+nx-nx*ny]+Uy[i+1+nx+nx*ny])
							-2.0*(Uy[i-nx-nx*ny]-Uy[i-nx+nx*ny]-Uy[i+nx-nx*ny]+Uy[i+nx+nx*ny]))
		+1.0/4.0/h/h/h/h*((Uz[i-1-nx-nx*ny]+Uz[i-1-nx+nx*ny]+Uz[i-1+nx-nx*ny]+Uz[i-1+nx+nx*ny]
							+Uz[i+1-nx-nx*ny]+Uz[i+1-nx+nx*ny]+Uz[i+1+nx-nx*ny]+Uz[i+1+nx+nx*ny])
							-2.0*(Uz[i-1-nx*ny]+Uz[i-1+nx*ny]+Uz[i-nx-nx*ny]+Uz[i-nx+nx*ny]
							+Uz[i+nx-nx*ny]+Uz[i+nx+nx*ny]+Uz[i+1-nx*ny]+Uz[i+1+nx*ny])
							+4.0*(Uz[i-nx*ny]+Uz[i+nx*ny])
								);
	return hd;
	}

double d2xy2z(double *U,double *Ux,double *Uy, double *Uz,int i, int nx, int ny,double h){
	double hd;
	hd=1.0/4.0/h/h/h/h/h*(3.0*(U[i-1-nx-nx*ny]+U[i-1-nx+nx*ny]-U[i-1+nx-nx*ny]-U[i-1+nx+nx*ny]
								+U[i+1-nx-nx*ny]+U[i+1-nx+nx*ny]-U[i+1+nx-nx*ny]-U[i+1+nx+nx*ny])
							-6.0*(U[i-1-nx]-U[i-1+nx]+U[i-nx-nx*ny]+U[i-nx+nx*ny]
								-U[i+nx-nx*ny]-U[i+nx+nx*ny]+U[i+1-nx]-U[i+1+nx])
							+12.0*(U[i-nx]-U[i+nx]))
		+1.0/4.0/h/h/h/h*((Ux[i-1-nx-nx*ny]+Ux[i-1-nx+nx*ny]-Ux[i-1+nx-nx*ny]-Ux[i-1+nx+nx*ny]
							-Ux[i+1-nx-nx*ny]-Ux[i+1-nx+nx*ny]+Ux[i+1+nx-nx*ny]+Ux[i+1+nx+nx*ny])
							-2.0*(Ux[i-1-nx]-Ux[i-1+nx]-Ux[i+1-nx]+Ux[i+1+nx]))
		+1.0/4.0/h/h/h/h*((Uy[i-1-nx-nx*ny]+Uy[i-1-nx+nx*ny]+Uy[i-1+nx-nx*ny]+Uy[i-1+nx+nx*ny]
							+Uy[i+1-nx-nx*ny]+Uy[i+1-nx+nx*ny]+Uy[i+1+nx-nx*ny]+Uy[i+1+nx+nx*ny])
							-2.0*(Uy[i-1-nx]+Uy[i-1+nx]+Uy[i-nx-nx*ny]+Uy[i-nx+nx*ny]
							+Uy[i+nx-nx*ny]+Uy[i+nx+nx*ny]+Uy[i+1-nx]+Uy[i+1+nx])
							+4.0*(Uy[i-nx]+Uy[i+nx]))
		+1.0/4.0/h/h/h/h*((Uz[i-1-nx-nx*ny]-Uz[i-1-nx+nx*ny]-Uz[i-1+nx-nx*ny]+Uz[i-1+nx+nx*ny]
							+Uz[i+1-nx-nx*ny]-Uz[i+1-nx+nx*ny]-Uz[i+1+nx-nx*ny]+Uz[i+1+nx+nx*ny])
							-2.0*(Uz[i-nx-nx*ny]-Uz[i-nx+nx*ny]-Uz[i+nx-nx*ny]+Uz[i+nx+nx*ny]));
	return hd;
	}

double dx2y2z(double *U,double *Ux,double *Uy, double *Uz,int i, int nx,int ny,double h){
	double hd;
	hd=1.0/4.0/h/h/h/h/h*(3.0*(U[i-1-nx-nx*ny]+U[i-1-nx+nx*ny]+U[i-1+nx-nx*ny]+U[i-1+nx+nx*ny]
								-U[i+1-nx-nx*ny]-U[i+1-nx+nx*ny]-U[i+1+nx-nx*ny]-U[i+1+nx+nx*ny])
							-6.0*(U[i-1-nx]+U[i-1-nx*ny]+U[i-1+nx*ny]+U[i-1+nx]
								-U[i+1-nx]-U[i+1-nx*ny]-U[i+1+nx*ny]-U[i+1+nx])
							+12.0*(U[i-1]-U[i+1]))
		+1.0/4.0/h/h/h/h*((Ux[i-1-nx-nx*ny]+Ux[i-1-nx+nx*ny]+Ux[i-1+nx-nx*ny]+Ux[i-1+nx+nx*ny]
							+Ux[i+1-nx-nx*ny]+Ux[i+1-nx+nx*ny]+Ux[i+1+nx-nx*ny]+Ux[i+1+nx+nx*ny])
							-2.0*(Ux[i-1-nx]+Ux[i-1-nx*ny]+Ux[i-1+nx*ny]+Ux[i-1+nx]
							+Ux[i+1-nx]+Ux[i+1-nx*ny]+Ux[i+1+nx*ny]+Ux[i+1+nx])
							+4.0*(Ux[i-1]+Ux[i+1]))
		+1.0/4.0/h/h/h/h*((Uy[i-1-nx-nx*ny]+Uy[i-1-nx+nx*ny]-Uy[i-1+nx-nx*ny]-Uy[i-1+nx+nx*ny]
							-Uy[i+1-nx-nx*ny]-Uy[i+1-nx+nx*ny]+	Uy[i+1+nx-nx*ny]+Uy[i+1+nx+nx*ny])
							-2.0*(Uy[i-1-nx]-Uy[i-nx+nx]-Uy[i+1-nx]+Uy[i+1+nx]))
		+1.0/4.0/h/h/h/h*((Uz[i-1-nx-nx*ny]-Uz[i-1-nx+nx*ny]+Uz[i-1+nx-nx*ny]-Uz[i-1+nx+nx*ny]
							-Uz[i+1-nx-nx*ny]+Uz[i+1-nx+nx*ny]-Uz[i+1+nx-nx*ny]+Uz[i+1+nx+nx*ny])
							-2.0*(Uz[i-1-nx*ny]-Uz[i-1+nx*ny]-Uz[i+1-nx*ny]+Uz[i+1+nx*ny]));
	return hd;
	}
