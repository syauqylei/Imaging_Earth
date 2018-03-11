#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void wfile_mat(char *filename, float **mat,int nt,int nrows,int ncols){
	FILE *fp;
	fp=fopen(filename,"w");
	for(int i=0;i<nt;i++){
		for(int j=0;j<nrows;j++){
			for(int k=0;k<ncols;k++){
				fprintf(fp,"%.3f \t",mat[i][j*ncols+k]);
			}
			fprintf(fp,"\n");
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

void wcsv_file(char filename, float **mat,int nt,int nrows,int ncols){
	FILE *fp[nt];
	char *format=".csv.0";
	char *fname=malloc(strlen(filename)+strlen(format));
	for(int i=0;i<nt;i++){
		fp[i]=fopen(sprintf(fname,".csv.%d",i),"w");
		for(int j=0;j<nrows;j++){
			for(int k=0;k<ncols;k++){
				fprintf(fp[i],"%d,%d,%d,%.3f\n",k,j,0,mat[i][j*ncols+k]);
			}
		}
		fclose(fp[i]);
	}
}
float *mat_to_vek(float **arr,const int nrows, const int ncols){
	float *vek=malloc(nrows*ncols*sizeof(float));
	for (int i=0; i<nrows;i++){
		for (int j=0; j<ncols;j++){
			vek[i*ncols+j]=arr[i][j];
		}
	}	
	return vek;
}

float **alloc_mat(const int nrows, const int ncols){
	float **mat=malloc(nrows*sizeof(float*));
	for (int i=0; i<nrows;i++){
		mat[i]=malloc(ncols*sizeof(float));
	}	
	return mat;
}

void free_mat_mem(float **mat,const int nrows){
	for(int i=0;i<nrows;i++){
		free(mat[i]);
	}
	free(mat);
}
void print_mat(float **mat,const int nrows,const int ncols){
	for (int i=0; i<nrows;i++){
		for (int j=0;j<ncols;j++){
			printf("%.3f\t",mat[i][j]);
		}
		printf("\n");
	}
}

void print_vek(float *mat,const int nelmts){
	for (int i=0; i<nelmts;i++){
		printf("[%d]: %.3f\n",i,mat[i]);
	}
}
