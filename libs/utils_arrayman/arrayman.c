#include <stdio.h>
#include <stdlib.h>

int len(float *a){
	int n;
	n=*(&a+1)-a;
	printf("%d\n",n);
	return n;
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
