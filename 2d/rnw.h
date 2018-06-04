#ifndef READNWRITE
#define READNWRITE
void read_vel(const std::string& filename, std::vector<double>& vel,int &nx,int &ny, int &nz, double &h);
void read_fwdset(const std::string& filename, std::vector<int>& srcloc,int &ns, double &dt,double &T,double &f);
void write_wve(const std::string& filename, double **U , int nx,int ny, int nz, int nt, double h, double dt);
double **read_wve(const std::string& filename, int &nx, int &ny, int &nz, int &nt, double &h,double &dt);
void write_vtk(std::string& filename,double **U,double h,int nt,int nx, int ny,int nz);
#endif
