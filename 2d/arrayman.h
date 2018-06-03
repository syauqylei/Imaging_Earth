#ifndef ARRAYMAN_H
#define ARRAYMAN_H
int len(double *a);
double *mat_to_vek(double **arr,const int nrows, const int ncols);
double **alloc_mat(const int nrows, const int ncols);
void free_mat_mem(double **mat);
void print_mat(double **mat,const int nrows,const int ncols);
void print_vek(double *mat,const int nelmts);
void print_vek_int(int *mat, const int nelmts);
void w_file_mat(char *filename, double **P,int nt,int nrows, int ncols);
void w_vtk(char *filename,double *Vel_mod, double **P,double h,int nt,int nx, int ny, int nz);
void w_dat(const std::string& filename,double *Vel_mod, double **P,double dt,double h,int nt,int nx, int ny, int nz);
#endif

