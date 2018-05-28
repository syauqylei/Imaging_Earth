#include <cmath>

double cfl(double c,double dt, double h){
	double cf=c*dt/h;
	return cf;
	}
double cf1( double c, double dt, double h){
	double cf=pow(c*dt/h,4)/6.0;
	return cf;
	}

double cf2( double c, double dt, double h){
	double cf=2.0*pow(c*dt/h,2)-2.0/3.0*pow(c*dt/h,4);
	return cf;
	}

double cf3( double c, double dt, double h){
	double cf=-8.0*pow(c*dt/h,2)+10.0/3.0*pow(c*dt/h,4)+2.0;
	return cf;
	}

double cf4( double c, double dt, double h){
	double cf=pow(c*dt,4)/h/h/h/12.0;
	return cf;
	}
	
double cf5( double c, double dt, double h){
	double cf=pow(c*dt,2)/h/2.0-pow(c*dt,4)/h/h/h/3.0;
	return cf;
	}

double cf6( double c, double dt, double h){
	double cf=pow(c*dt,2)/h/h/h/3.0-3.0*pow(c*dt,4)/h/h/h/2;
	return cf;
	}

double cf7( double c, double dt, double h){
	double cf=13.0*pow(c*dt,2)/h/h/h/2.0-6.0*pow(c*dt,4)/h/h/h/h/h;
	return cf;
	}

double cf8( double c, double dt, double h){
	double cf=pow(c*dt/h,4)/4.0/h/h/h/h;
	return cf;
	}
	
double cf9( double c, double dt, double h){
	double cf=pow(c*dt/h,2);
	return cf;
	}

double cf10( double c, double dt, double h){
	double cf=-3.0*pow(c*dt/h,2)/2.0+2.0*pow(c*dt/h,4);
	return cf;
	}


double cf11( double c, double dt, double h){
	double cf=-14.0*pow(c*dt/h,2)/2.0+10.0*pow(c*dt/h,4)+2.0;
	return cf;
	}

double cf12( double c, double dt, double h){
	double cf=pow(c*dt/h,4)/4.0-pow(c*dt/h,2)/4;
	return cf;
	}

double cfl1(double c,double dt){
	double cf=pow(c*dt,2);
	return cf;
	}

double cfl2(double c,double dt, double h){
	double cf=(pow(c*dt*h,2)-pow(c*dt,4))/12.0;
	return cf;
	}


double cfl3(double c,double dt){
	double cf=(pow(c*dt,4))/6.0;
	return cf;
	}
