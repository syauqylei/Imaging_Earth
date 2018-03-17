#ifndef FIN_DIFF_OPR_H
#define FIN_DIFF_OPR_H
struct hd2d{
	double fd_cf[5];
	double fd_cf_coo[5];
	//d2x
	double ad2x[3];
	double bd2x[2];
	double Cad2x[3];
	double Cbd2x[2];
	//d2y
	double ad2y[3];
	double bd2y[2];
	double Cad2y[3];
	double Cbd2y[2];
	
	//d3x
	double ad3x[2];
	double Cad3x[2];
	double bd3x[3];
	double Cbd3x[3];
	
	//d3y
	double ad3y[2];
	double Cad3y[2];
	double bd3y[3];
	double Cbd3y[3];
	//d2xy
	double ad2xy[8];
	double bd2xy[7];
	double *cd2xy = &ad2x[0];
	double Cad2xy[8];
	double Cbd2xy[7];
	double *Ccd2xy=&Cad2x[0];
	
	//dx2y
	double adx2y[8];
	double bdx2y[7];
	double *cdx2y=&ad2y[0];
	double *Cadx2y=&Cad2xy[0];
	double *Cbdx2y=&Cbd2xy[0];
	double *Ccdx2y=&Cad2y[0];
	
	//d4x
	double *ad4x=&ad2x[0];
	double *Cad4x=&Cad2x[0];
	double *bd4x=&bd2x[0];
	double *Cbd4x=&Cbd2x[0];
	
	//d4y
	double *ad4y=&ad2y[0];
	double *Cad4y=&Cad2y[0];
	double *bd4y=&bd2y[0];
	double *Cbd4y=&Cbd2y[0];
	
	//d2x2y
	double d2x2y[9];
	double Cd2x2y[9];
	
	//d5x
	double *ad5x=&ad3x[0];
	double *Cad5x=&Cad3x[0];
	double *bd5x=&bd3x[0];
	double *Cbd5x=&Cbd3x[0];
	
	//d5y
	double *ad5y=&ad3y[0];
	double *Cad5y=&Cad3y[0];
	double *bd5y=&bd3y[0];
	double *Cbd5y=&Cbd3y[0];
	
	//d4xy
	double *ad4xy=&ad2xy[0];
	double bd4xy[7];
	double *Cad4xy=&Cad2xy[0];
	double Cbd4xy[7];
	
	//dx4y
	double *adx4y=&adx2y[0];
	double bdx4y[7];
	double *Cadx4y=&Cadx2y[0];
	double *Cbdx4y=&Cbd4xy[0];
	
	//d3x2y
	double ad3x2y[6];
	double *bd3x2y=&ad2y[0];
	double Cad3x2y[6];
	double *Cbd3x2y=&Cad2y[0];

	//d2x3y
	double ad2x3y[6];
	double *bd2x3y=&ad2x[0];
	double Cad2x3y[6];
	double *Cbd2x3y=&Cad2x[0];
	
	};

hd2d input(double nx){
	hd2d HD;
	
	//Conventional Finite difference
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
	
	//d2x
	HD.ad2x[0]=1;
	HD.ad2x[1]=-2;
	HD.ad2x[2]=1;
	HD.Cad2x[0]=-1;
	HD.Cad2x[1]=0;
	HD.Cad2x[2]=1;
	
	HD.bd2x[0]=-1;
	HD.bd2x[1]=1;
	HD.Cbd2x[0]=-1;
	HD.Cbd2x[1]=1;
	
	//d2y
	HD.ad2y[0]=1;
	HD.ad2y[1]=-2;
	HD.ad2y[2]=1;
	HD.Cad2y[0]=-nx;
	HD.Cad2y[1]=0;
	HD.Cad2y[2]=nx;
	HD.bd2y[0]=-1;
	HD.bd2y[1]=1;
	HD.Cbd2y[0]=-nx;
	HD.Cbd2y[1]=nx;
	
	//d3x
	HD.ad3x[0]=-1;
	HD.ad3x[1]=1;
	HD.Cad3x[0]=-1;
	HD.Cad3x[1]=1;
	HD.bd3x[0]=1;
	HD.bd3x[1]=8;
	HD.bd3x[2]=1;
	HD.Cbd3x[0]=-1;
	HD.Cbd3x[1]=0;
	HD.Cbd3x[2]=1;
	
	//d3y
	HD.ad3y[0]=-1;
	HD.ad3y[1]=1;
	HD.Cad3y[0]=-nx;
	HD.Cad3y[1]=nx;
	HD.bd3y[0]=1;
	HD.bd3y[1]=8;
	HD.bd3y[2]=1;
	HD.Cbd3y[0]=-nx;
	HD.Cbd3y[1]=0;
	HD.Cbd3y[2]=nx;
	
	//d2xy
	HD.ad2xy[0]=-5;
	HD.ad2xy[1]=4;
	HD.ad2xy[2]=1;
	HD.ad2xy[3]=6;
	HD.ad2xy[4]=-6;
	HD.ad2xy[5]=-1;
	HD.ad2xy[6]=-4;
	HD.ad2xy[7]=5;
	//
	HD.bd2xy[0]=-1;
	HD.bd2xy[1]=-2;
	HD.bd2xy[2]=1;
	HD.bd2xy[3]=4;
	HD.bd2xy[4]=1;
	HD.bd2xy[5]=-2;
	HD.bd2xy[6]=-1;
	//

	HD.Cad2xy[0]=-nx-1;
	HD.Cad2xy[1]=-nx;
	HD.Cad2xy[2]=-nx+1;
	HD.Cad2xy[3]=-1;
	HD.Cad2xy[4]=1;
	HD.Cad2xy[5]=nx-1;
	HD.Cad2xy[6]=nx;
	HD.Cad2xy[7]=nx+1;
	//
	HD.Cbd2xy[0]=-nx-1;
	HD.Cbd2xy[1]=-nx;
	HD.Cbd2xy[2]=-1;
	HD.Cbd2xy[3]=0;
	HD.Cbd2xy[4]=1;
	HD.Cbd2xy[5]=nx;
	HD.Cbd2xy[6]=nx+1;
	
	//dx2y
	HD.adx2y[0]=-5;
	HD.adx2y[1]=6;
	HD.adx2y[2]=-1;
	HD.adx2y[3]=4;
	HD.adx2y[4]=-4;
	HD.adx2y[5]=1;
	HD.adx2y[6]=-6;
	HD.adx2y[7]=5;
	//
	HD.bdx2y[0]=-1;
	HD.bdx2y[1]=1;
	HD.bdx2y[2]=-2;
	HD.bdx2y[3]=4;
	HD.bdx2y[4]=-2;
	HD.bdx2y[5]=1;
	HD.bdx2y[6]=-1;
	
	//d2x2y
	HD.d2x2y[0]=1;
	HD.d2x2y[1]=-2;
	HD.d2x2y[2]=1;
	HD.d2x2y[3]=-2;
	HD.d2x2y[4]=4;
	HD.d2x2y[5]=-2;
	HD.d2x2y[6]=1;
	HD.d2x2y[7]=-2;
	HD.d2x2y[8]=1;
	//
	HD.Cd2x2y[0]=-nx-1;
	HD.Cd2x2y[1]=-nx;
	HD.Cd2x2y[2]=-nx+1;
	HD.Cd2x2y[3]=-1;
	HD.Cd2x2y[4]=0;
	HD.Cd2x2y[5]=1;
	HD.Cd2x2y[6]=nx-1;
	HD.Cd2x2y[7]=nx;
	HD.Cd2x2y[8]=nx+1;
	
	//d4xy
	HD.bd4xy[0]=1;
	HD.bd4xy[1]=1;
	HD.bd4xy[2]=-1;
	HD.bd4xy[3]=-2;
	HD.bd4xy[4]=-1;
	HD.bd4xy[5]=1;
	HD.bd4xy[6]=1;
	//
	HD.Cbd4xy[0]=-nx-1;
	HD.Cbd4xy[1]=-nx;
	HD.Cbd4xy[2]=-1;
	HD.Cbd4xy[3]=0;	
	HD.Cbd4xy[4]=1;
	HD.Cbd4xy[5]=nx;
	HD.Cbd4xy[6]=nx+1;
	
	//dx4y
	HD.bdx4y[0]=1;
	HD.bdx4y[1]=-1;
	HD.bdx4y[2]=1;
	HD.bdx4y[3]=-2;
	HD.bdx4y[4]=1;
	HD.bdx4y[5]=-1;
	HD.bdx4y[6]=1;
	
	//d3x2y
	HD.ad3x2y[0]=-1;
	HD.ad3x2y[1]=1;
	HD.ad3x2y[2]=2;
	HD.ad3x2y[3]=-2;
	HD.ad3x2y[4]=-1;
	HD.ad3x2y[5]=1;
	//
	HD.Cad3x2y[0]=-nx-1;
	HD.Cad3x2y[1]=-nx+1;
	HD.Cad3x2y[2]=-1;
	HD.Cad3x2y[3]=1;
	HD.Cad3x2y[4]=nx-1;
	HD.Cad3x2y[5]=nx+1;
	
	//d2x3y
	HD.ad2x3y[0]=-1;
	HD.ad2x3y[1]=2;
	HD.ad2x3y[2]=-1;
	HD.ad2x3y[3]=1;
	HD.ad2x3y[4]=-2;
	HD.ad2x3y[5]=1;
	//
	HD.Cad2x3y[0]=-nx-1;
	HD.Cad2x3y[1]=-nx;
	HD.Cad2x3y[2]=-nx+1;
	HD.Cad2x3y[3]=nx-1;
	HD.Cad2x3y[4]=nx;
	HD.Cad2x3y[5]=nx+1;
	
	return HD;
	}
#endif
