double *vek_addition(double *A, double *B,const int nelmts){
	double *C=new double[nelmts];
	for (int i=0;i<nelmts;i++){
			C[i]=A[i]+B[i];
	}
	return C;
}
double *vek_subtraction(double *A, double *B ,const int nelmts){
	double *C=new double[nelmts];
	for (int i=0;i<nelmts;i++){
			C[i]=A[i]-B[i];
	}
	return C;
}
double *vek_elmwise_mult(double *A, double *B,const int nelmts){
	double *C=new double[nelmts];
	for (int i=0;i<nelmts;i++){
			C[i]=A[i]*B[i];
	}
	return C;
}
double *scalar_mult(const double scalar_const,double *A,const int nelmts){
	double *C=new double[nelmts];
	for (int i=0;i<nelmts;i++){
			C[i]=scalar_const*A[i];
	}
	return C;
}
