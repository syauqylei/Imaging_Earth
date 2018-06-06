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

void write_rec(const std::string& filename, double **U,int srcloc, double h,double dt, int nx,int nt){
	std::ofstream file;
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(5) << srcloc;
	std::string ext1=".rec";
	std::string ext2=".txt";
	file.open(filename+ss.str()+ext1);
	for (int i=0;i<nt;i++){
		for (int j=0;j<nx;j++){
		file << std::fixed() <<std::setprecision(5) << U[i][j]<<"\t";
		}
		std::cout<<"\n";
	}
	file.close();
	
	file.open(filename+ss.str()+ext2);
	file<<srcloc<<"\t"<<h<<"\t"<<nx<<"\t"<<"\t"<<nt<<"\n";
	file.close();
}
