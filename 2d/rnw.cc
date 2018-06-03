#include <iostream>
#include <fstream>
#include <iomanip>
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
	for(int i=0;i<nt;i++){
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
	std::cout<<nt<<"\t \n";
	std::cout<<Ufield.size()-6<<"\t \n";
	double **U=alloc_mat(nt,nx*ny*nz);
	return U;
	}
