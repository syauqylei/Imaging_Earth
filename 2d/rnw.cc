#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "arrayman.h"

void read_vel(const std::string& filename, std::vector <double>& vel , int &nx,int &ny, int &nz, double &h){
	std::ifstream f(filename);
	
	int i=0;
	double content;
	while (f >> content)
	{
		i++;
		if(i==1){
			nx=content;}
		else if(i==2){
			ny=content;}
		else if(i==3){
			nz=content;}
		else if(i==4){
			h=content;}
		else{vel.push_back(content);}
	}
	}

void read_fwdset(const std::string& filename, std::vector <int>& srcloc,int &ns, double &dt,double &T,double &fm){
	std::ifstream f(filename);
	std::vector<double> source_loc;
	int i=0;
	double content;while (f >> content)
	{
		i++;
		if(i==1){
			dt=content;}
		else if(i==2){
			T=content;}
		else if(i==3){
			fm=content;}
		else{srcloc.push_back(content);}
	}
	ns=srcloc.size()-3;
	}

void write_wve(const std::string& filename, double **U , int nx,int ny, int nz, int nt, double h, double dt){
	std::string ext=".wve";
	std::string fname=filename+ext;
	std::ofstream file;
	file.open(fname);
	file << nx <<"\t"<< ny <<"\t"<< nz <<"\t"<< nt <<"\t"<< h <<"\t"<< dt<<std::endl;
	int tprint=nt/10;
	for(int i=0;i<nt;i++){
		if(i%tprint==0){
		std::cout<<"Writing Wavefield ... "<<float(i)/float(nt)*100<<"%\n";}
		for(int j=0;j<nx*ny*nz;j++){
			file<<std::fixed<<std::setprecision(3)<<U[i][j]<<"\t"; 
			}
		}
	file.close();
	}

double **read_wve(const std::string& filename, int &nx, int &ny, int &nz, int &nt, double &h,double &dt){
	std::ifstream f(filename);
	double content;
	std::vector<double> Ufield;
	int i=0;
	while (f >> content)
	{
		i++;
		if(i==1){
			nx=content;}
		else if(i==2){
			ny=content;}
		else if(i==3){
			nz=content;}
		else if(i==4){
			nt=content;}
		else if(i==5){
			h=content;}
		else if(i==6){
			dt=content;}
		else{Ufield.push_back(content);}
	}
	double **U=alloc_mat(nt,nx*ny*nz);
	std::cout<<nx<<"\t "<<ny<<"\t "<<nz<<"\t "<<nt<<"\t \n";
	std::cout<<Ufield.size()-6<<"\t \n";
	return U;
	}
	
void write_vtk(const std::string& filename,double **U,double h,int nt,int nx, int ny,int nz)
{
	std::string ext=".vtk";
	int tprint=float(nt)/10.0;
	for(int l=0;l<nt;l++)
	{
		if(l%tprint==0){std::cout<<"Writing Vtk File ........"<<float(l+1)/nt*100.0<<"% \n";}
		std::stringstream ss;
		ss << std::setfill('0') << std::setw(5) << l;
		std::string fname=filename+ss.str()+ext;
		std::ofstream file;
		file.open(fname);
		file <<"# vtk DataFile Version 2.0"<<std::endl;
		file <<filename<<std::endl;
		file <<"ASCII"<<std::endl;
		file <<"DATASET"<<"\t"<<"STRUCTURED_POINTS"<<std::endl;
		file <<"DIMENSIONS"<<"\t"<<nx<<"\t"<<ny<<"\t"<<nz<<std::endl;
		file <<"SPACING"<<"\t"<<h<<"\t"<<h<<"\t"<<h<<std::endl;
		file <<"ORIGIN"<<"\t"<<"0"<<"\t"<<"0"<<"\t"<<"0"<<std::endl;
		file <<"POINT_DATA"<<"\t"<<nx*ny*nz<<std::endl;
		file <<"SCALARS"<<"\t"<<"Wavefield"<<"\t"<<"float"<<"\t"<<"4"<<std::endl;
		file <<"LOOKUP_TABLE"<<"\t"<<"default"<<std::endl;
		for (int i=0;i<nz;i++)
		{
			for (int j=0;j<ny;j++)
			{
				for(int k=0;k<nx;k++)
				{
				file <<std::fixed<<std::setprecision(5)<<k*h<<" "<<j*h<<" "<<i*h<<" "<<U[i][i*nx*ny+j*nx+k]<<std::endl;
				}
			}
		}
		file.close();
	}
}
