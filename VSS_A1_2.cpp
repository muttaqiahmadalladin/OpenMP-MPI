#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <omp.h>

using namespace std;


int main(){
    //---------Declaring A lower Triangualr Matrix------
    int size =3000;//change size to whatever!
    int** Ar= new int *[size];
    for(int i=0;i<size;i++){
        Ar[i]=new int[size];
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(j>i){
                Ar[i][j]=0;
            }
        else{
            Ar[i][j]=rand();
            }
        }

    }
    //printf("%d",Ar[1][1]);
    //--------------------------DONE---------------------------
    //------------------------Declaring Vector-----------
    int* vec= new int [size];
    for(int i=0;i<size;i++){
        vec[i]=rand();

    }
    //-----------------Declaring the result vector---------
    float* result= new float [size];
    for(int i=0;i<size;i++){
        result[i]=0;

    }
    //---------------DONE---------------------
    //-------------------Matrix Vector Multiplication--------
    int i,j;
    double start_time = clock();
    int size_i=size;
    int size_j=size;
    int tam =size;

    #pragma omp parallel num_threads(4)
      {
        double sLocal = 0;
        int i, j;
        for (i = 0; i < tam; i++) {
    #pragma omp for schedule(static)
          for (j = 0; j < tam; j++) {
            sLocal += Ar[i][j] * vec[j];
          }
    #pragma omp critical
          {
            result[i] += sLocal;
            sLocal = 0;
          }
        }
    }
    double end_time = clock();
    double result_time = (end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time: %f\n", result_time);

}
