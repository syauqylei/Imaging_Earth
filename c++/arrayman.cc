#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

void w_dat(char *filename,float *Vel_mod, float **P,float dt,float h,int nt,int nx, int ny, int nz){
	std::string ext=".dat";
	std::string fname;
	std::ofstream myfile;
	for (int t=0; t<nt;t++){
		std::stringstream ss;
		ss <<std::setfill('0')<< std::setw(3) <<t;
		fname=filename+ss.str()+ ext;
		myfile.open(fname);
		
		myfile << "TITLE = "<<"\""<<fname<<"\""<<std::endl;
		myfile << "VARIABLES = "<<"\"x\""<<","<<"\"y\""<<","<<"\"z\""<<","<<"\"Wavefield\""<<","<<"\"Velocity\""<<std::endl;
		myfile << "ZONE T = "<<"\"Frame "<<std::to_string(t)<<"\""<<", I = "<< std::to_string(nx)<<", J = "<< std::to_string(ny)<<", K = "<< std::to_string(nz)<<std::endl;
		for (int i=0; i<nz;i++){
			for (int j=0; j<nx;j++){
				for (int k=0;k<ny;k++){
					myfile << std::fixed<< std::setprecision(5)<<j*h+h/2.0<<","<< k*h+h/2.0<<","<< i*h+h/2.0<<","<<P[t][k*nx*nz+i*nx+j]<<","<<Vel_mod[k*nx*nz+i*nx+j]<<"\n";
				}
			}
		}
	myfile.close();
	}
}

void w_csv(char *filename,float *Vel_mod, float **P,float dt,float h,int nt,int nx, int ny, int nz){
	std::string ext=".csv";
	std::string fname;
	std::ofstream myfile;
	for (int t=0; t<nt;t++){
		std::stringstream ss;
		ss <<std::setfill('0')<< std::setw(3) <<t;
		fname=filename+ss.str()+ ext;
		myfile.open(fname);
		myfile << "t,x,y,z,value"<<std::endl;		
		for (int i=0; i<nz;i++){
			for (int j=0; j<nx;j++){
				for (int k=0;k<ny;k++){
					myfile << std::fixed<< std::setprecision(5)<<t*dt<<","<<j*h+h/2.0<<","<< k*h+h/2.0<<","<< i*h+h/2.0<<","<<P[t][k*nx*nz+i*nx+j]<<"\n";
				}
			}
		}
	myfile.close();
	}
}

void w_vtk(char *filename,float *Vel_mod, float **P,float h,int nt,int nx, int ny, int nz){
	std::string ext=".vtk";
	std::string fname;
	std::ofstream myfile;
	for (int t=0; t<nt;t++){
		std::stringstream ss;
		ss <<std::setfill('0')<< std::setw(3) <<t;
		fname=filename+ss.str()+ ext;
		myfile.open(fname);
		myfile << "#vtk DataFile Version 2.0"<<std::endl;
		myfile << fname<<std::endl;
		myfile << "ASCII"<<std::endl;
		myfile << "DATASET STRUCTURED_GRID"<<std::endl;
		myfile << "DIMENSION "<<std::to_string(nx)<<" "<<std::to_string(ny)<<" "<<std::to_string(nz)<<std::endl;
		myfile << "POINTS "<<std::to_string(nx*nz*ny)<<" float"<<std::endl;
		
		for (int i=0; i<nz;i++){
			for (int j=0; j<nx;j++){
				for (int k=0;k<ny;k++){
					myfile << std::fixed<< std::setprecision(5)<< j*h+h/2.0<<" "<< k*h+h/2.0<<" "<< i*h+h/2.0<<"\n";
				}
			}
		}
		myfile <<std::endl;
		myfile << "SCALARS Wavefield float 1"<<std::endl;
		myfile << "LOOKUP_TABLE default"<<std::endl;
		
		for (int i=0; i<nz;i++){
			for (int j=0; j<nx;j++){
				for (int k=0;k<ny;k++){
					myfile << P[t][k*nx*nz+i*nx+j]<<"\n";
				}
			}
		}
		/*
		myfile <<std::endl;
		myfile << "SCALARS Velocity_Model float 1"<<std::endl;
		myfile << "LOOKUP_TABLE default"<<std::endl;
		for (int i=0; i<nz;i++){
			for (int j=0; j<nx;j++){
				for (int k=0;k<ny;k++){
					myfile << Vel_mod[k*nx*nz+i*nx+j]<<"\n";
				}
			}
		}*/
	myfile.close();
	}
}

void w_file_mat(char *filename, float **P,int nt,int nrows, int ncols){
	std::ofstream myfile;
	myfile.open (filename);
	for (int i=0; i<nt;i++){
		for (int j=0; j<nrows;j++){
			for (int k=0;k<ncols;k++){
				myfile << std::fixed<<P[i][j*ncols+k] <<"\t";
			}
			
			myfile << "\n";
		}
		myfile << "\n";
	}
	myfile.close();
}

float *mat_to_vek(float **arr,const int nrows, const int ncols){
	float *vek=new float[nrows*ncols];
	for (int i=0; i<nrows;i++){
		for (int j=0; j<ncols;j++){
			vek[i*ncols+j]=arr[i][j];
		}
	}	
	return vek;
}

float **alloc_mat(const int nrows, const int ncols){
	float **mat=new float*[nrows];
	
	mat[0]= new float[nrows*ncols];
	for (int i=1; i<nrows;i++){
		mat[i]=&mat[0][i*ncols];
	}	
	return mat;
}

void free_mat_mem(float **mat,const int nrows){
	delete [] mat[0];
	delete [] mat;
}
void print_mat(float **mat,const int nrows,const int ncols){
	for (int i=0; i<nrows;i++){
		for (int j=0;j<ncols;j++){
			std:: cout<<mat[i][j]<<"\t";
		}
		std::cout<<"\n";
	}
}

void print_vek(float *mat,const int nelmts){
	for (int i=0; i<nelmts;i++){
		std::cout<<i<<mat[i]<<"\n";
	}
}
