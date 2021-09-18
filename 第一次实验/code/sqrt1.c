#include <stdio.h>
#include <mpi.h>
#include <math.h>
#define N 1002
int main(int argc, char **argv)
{
    
    int myid, P, numprocs, C = 0;
    double data[N], SqrtSum = 0.0;
    double result;
    double d;
    int i;
    for (i = 0; i < N; ++i)
        data[i] = i*(i+1);
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    for(i = myid;i<N;i=i+numprocs)
    {
        SqrtSum+=sqrt(data[i]);
        C++;
    }

    MPI_Reduce(&SqrtSum,&result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    printf("I am process %d. I calculate total %d ,and SqrtSum=%f.\n", myid, C, SqrtSum);
    if(myid==0)
        printf("I am process 0. final result is %f.\n",result);
    MPI_Finalize();
    return 0;
}
