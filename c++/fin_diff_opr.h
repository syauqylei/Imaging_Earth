#ifndef FIN_DIFF_OPR_H
#define FIN_DIFF_OPR_H
struct hd2d{
	float fd_cf[5];
	float fd_cf_coo[5];
	//d2x
	float ad2x[3];
	float bd2x[2];
	float Cad2x[3];
	float Cbd2x[2];
	//d2z
	float ad2z[3];
	float bd2z[2];
	float Cad2z[3];
	float Cbd2z[2];
	
	//d3x
	float ad3x[2];
	float Cad3x[2];
	float bd3x[3];
	float Cbd3x[3];
	
	//d3z
	float ad3z[2];
	float Cad3z[2];
	float bd3z[3];
	float Cbd3z[3];
	//d2xz
	float ad2xz[8];
	float bd2xz[7];
	float *cd2xz = &ad2x[0];
	float Cad2xz[8];
	float Cbd2xz[7];
	float *Ccd2xz=&Cad2x[0];
	
	//dx2z
	float adx2z[8];
	float bdx2z[7];
	float *cdx2z=&ad2z[0];
	float *Cadx2z=&Cad2xz[0];
	float *Cbdx2z=&Cbd2xz[0];
	float *Ccdx2z=&Cad2z[0];
	
	//d4x
	float *ad4x=&ad2x[0];
	float *Cad4x=&Cad2x[0];
	float *bd4x=&bd2x[0];
	float *Cbd4x=&Cbd2x[0];
	
	//d4z
	float *ad4z=&ad2z[0];
	float *Cad4z=&Cad2z[0];
	float *bd4z=&bd2z[0];
	float *Cbd4z=&Cbd2z[0];
	
	//d2x2z
	float d2x2z[9];
	float Cd2x2z[9];
	
	//d5x
	float *ad5x=&ad3x[0];
	float *Cad5x=&Cad3x[0];
	float *bd5x=&bd3x[0];
	float *Cbd5x=&Cbd3x[0];
	
	//d5z
	float *ad5z=&ad3z[0];
	float *Cad5z=&Cad3z[0];
	float *bd5z=&bd3z[0];
	float *Cbd5z=&Cbd3z[0];
	
	//d4xz
	float *ad4xz=&ad2xz[0];
	float bd4xz[7];
	float *Cad4xz=&Cad2xz[0];
	float Cbd4xz[7];
	
	//dx4z
	float *adx4z=&adx2z[0];
	float bdx4z[7];
	float *Cadx4z=&Cadx2z[0];
	float *Cbdx4z=&Cbd4xz[0];
	
	//d3x2z
	float ad3x2z[6];
	float *bd3x2z=&ad2z[0];
	float Cad3x2z[6];
	float *Cbd3x2z=&Cad2z[0];

	//d2x3z
	float ad2x3z[6];
	float *bd2x3z=&ad2x[0];
	float Cad2x3z[6];
	float *Cbd2x3z=&Cad2x[0];
	
	};

hd2d input(float nx){
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
	
	//d2z
	HD.ad2z[0]=1;
	HD.ad2z[1]=-2;
	HD.ad2z[2]=1;
	HD.Cad2z[0]=-nx;
	HD.Cad2z[1]=0;
	HD.Cad2z[2]=nx;
	HD.bd2z[0]=-1;
	HD.bd2z[1]=1;
	HD.Cbd2z[0]=-nx;
	HD.Cbd2z[1]=nx;
	
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
	
	//d3z
	HD.ad3z[0]=-1;
	HD.ad3z[1]=1;
	HD.Cad3z[0]=-nx;
	HD.Cad3z[1]=nx;
	HD.bd3z[0]=1;
	HD.bd3z[1]=8;
	HD.bd3z[2]=1;
	HD.Cbd3z[0]=-nx;
	HD.Cbd3z[1]=0;
	HD.Cbd3z[2]=nx;
	
	//d2xz
	HD.ad2xz[0]=-5;
	HD.ad2xz[1]=4;
	HD.ad2xz[2]=1;
	HD.ad2xz[3]=6;
	HD.ad2xz[4]=-6;
	HD.ad2xz[5]=-1;
	HD.ad2xz[6]=-4;
	HD.ad2xz[7]=5;
	//
	HD.bd2xz[0]=-1;
	HD.bd2xz[1]=-2;
	HD.bd2xz[2]=1;
	HD.bd2xz[3]=4;
	HD.bd2xz[4]=1;
	HD.bd2xz[5]=-2;
	HD.bd2xz[6]=-1;
	//

	HD.Cad2xz[0]=-nx-1;
	HD.Cad2xz[1]=-nx;
	HD.Cad2xz[2]=-nx+1;
	HD.Cad2xz[3]=-1;
	HD.Cad2xz[4]=1;
	HD.Cad2xz[5]=nx-1;
	HD.Cad2xz[6]=nx;
	HD.Cad2xz[7]=nx+1;
	//
	HD.Cbd2xz[0]=-nx-1;
	HD.Cbd2xz[1]=-nx;
	HD.Cbd2xz[2]=-1;
	HD.Cbd2xz[3]=0;
	HD.Cbd2xz[4]=1;
	HD.Cbd2xz[5]=nx;
	HD.Cbd2xz[6]=nx+1;
	
	//dx2z
	HD.adx2z[0]=-5;
	HD.adx2z[1]=6;
	HD.adx2z[2]=-1;
	HD.adx2z[3]=4;
	HD.adx2z[4]=-4;
	HD.adx2z[5]=1;
	HD.adx2z[6]=-6;
	HD.adx2z[7]=5;
	//
	HD.bdx2z[0]=-1;
	HD.bdx2z[1]=1;
	HD.bdx2z[2]=-2;
	HD.bdx2z[3]=4;
	HD.bdx2z[4]=-2;
	HD.bdx2z[5]=1;
	HD.bdx2z[6]=-1;
	
	//d2x2z
	HD.d2x2z[0]=1;
	HD.d2x2z[1]=-2;
	HD.d2x2z[2]=1;
	HD.d2x2z[3]=-2;
	HD.d2x2z[4]=4;
	HD.d2x2z[5]=-2;
	HD.d2x2z[6]=1;
	HD.d2x2z[7]=-2;
	HD.d2x2z[8]=1;
	//
	HD.Cd2x2z[0]=-nx-1;
	HD.Cd2x2z[1]=-nx;
	HD.Cd2x2z[2]=-nx+1;
	HD.Cd2x2z[3]=-1;
	HD.Cd2x2z[4]=0;
	HD.Cd2x2z[5]=1;
	HD.Cd2x2z[6]=nx-1;
	HD.Cd2x2z[7]=nx;
	HD.Cd2x2z[8]=nx+1;
	
	//d4xz
	HD.bd4xz[0]=1;
	HD.bd4xz[1]=1;
	HD.bd4xz[2]=-1;
	HD.bd4xz[3]=-2;
	HD.bd4xz[4]=-1;
	HD.bd4xz[5]=1;
	HD.bd4xz[6]=1;
	//
	HD.Cbd4xz[0]=-nx-1;
	HD.Cbd4xz[1]=-nx;
	HD.Cbd4xz[2]=-1;
	HD.Cbd4xz[3]=0;	
	HD.Cbd4xz[4]=1;
	HD.Cbd4xz[5]=nx;
	HD.Cbd4xz[6]=nx+1;
	
	//dx4z
	HD.bdx4z[0]=1;
	HD.bdx4z[1]=-1;
	HD.bdx4z[2]=1;
	HD.bdx4z[3]=-2;
	HD.bdx4z[4]=1;
	HD.bdx4z[5]=-1;
	HD.bdx4z[6]=1;
	
	//d3x2z
	HD.ad3x2z[0]=-1;
	HD.ad3x2z[1]=1;
	HD.ad3x2z[2]=2;
	HD.ad3x2z[3]=-2;
	HD.ad3x2z[4]=-1;
	HD.ad3x2z[5]=1;
	//
	HD.Cad3x2z[0]=-nx-1;
	HD.Cad3x2z[1]=-nx+1;
	HD.Cad3x2z[2]=-1;
	HD.Cad3x2z[3]=1;
	HD.Cad3x2z[4]=nx-1;
	HD.Cad3x2z[5]=nx+1;
	
	//d2x3z
	HD.ad2x3z[0]=-1;
	HD.ad2x3z[1]=2;
	HD.ad2x3z[2]=-1;
	HD.ad2x3z[3]=1;
	HD.ad2x3z[4]=-2;
	HD.ad2x3z[5]=1;
	//
	HD.Cad2x3z[0]=-nx-1;
	HD.Cad2x3z[1]=-nx;
	HD.Cad2x3z[2]=-nx+1;
	HD.Cad2x3z[3]=nx-1;
	HD.Cad2x3z[4]=nx;
	HD.Cad2x3z[5]=nx+1;
	
	return HD;
	}
#endif
