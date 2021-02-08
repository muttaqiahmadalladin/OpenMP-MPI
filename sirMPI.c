#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include "mpi.h"
int main(int argc,char** argv){
    double A[1000000];
    double elem,time2,time1;
    int other_i,other_rank,flag,i,global_pos,nvalues;//other_i is equivalent to dummy
    MPI_Request request;
    MPI_Comm comm;
    MPI_Status status;
    int rank,size;
    FILE *myfile;
    myfile=fopen("output2.txt","r");
    int numberarray[100];
    int inum,size_num;
    size_num =0;
    //elem=rand()%5000000;
    //read logic;
    for (inum=0;inum<100;inum++){
        if(fscanf(myfile,"%d",&numberarray[inum])==EOF){
        size_num=inum;
        break;
        }
    }


    elem= numberarray[0];

    //write logic
    myfile=fopen("output2.txt","w");
    for(inum=1;inum<size_num;inum++){
        fprintf(myfile,"%d\n",numberarray[inum]);
    }


    for(i=0;i<1000000;++i) {
      A[i]=rand()%5000000;
    }
    
    MPI_Init(&argc,&argv);
    time1=MPI_Wtime();
    comm= MPI_COMM_WORLD;
    MPI_Comm_rank(comm,&rank);
    MPI_Comm_size(comm,&size);
    other_rank = (rank==0)?1:0;
    /* the point of this is that the other processor is sort of initalised
    works only in 2 ranks need to use wild cards elsewhere*/
    MPI_Irecv(&other_i,1,MPI_INT,MPI_ANY_SOURCE,10,comm,&request);
  nvalues=1000000/size;
  i=rank*nvalues;
    for(;i<(rank*nvalues+nvalues);i++){
        if (A[i]==elem){
            //element found
            for(j=0;j<size;++j){
            MPI_Send(&i,1,MPI_INT,j,10,comm);//works for only 2 processors
            }
            if(rank==0){
                global_pos=i;
            }

        MPI_Cancel(&request);
        break;
        }
        else{
            MPI_Test(&request,&flag,&status);
            if(flag==1){
                if (rank==0){
                    global_pos=other_i+nvalues;
                }
                break;
            }
            
        }

    }
    if (rank==0){
        //printf("found the element %d at the pos %d\n",elem,global_pos);

    }
    time2 = MPI_Wtime();
    MPI_Finalize();
    if (rank==0){
        //printf("found the element %d at the pos %d\n",elem,global_pos);

    printf("total time is =%f\n",time2-time1);
    }
}