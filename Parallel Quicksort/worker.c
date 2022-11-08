#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

void srandom (unsigned seed);
double dboard (int darts);
#define DARTS 50000     /* number of throws at dartboard */
#define ROUNDS 100      /* number of times "darts" is iterated */
#define MASTER 0        /* task ID of master task */

int main (int argc, char *argv[])
{
    int	processId,	        /* task ID - also used as seed number */
        numChildren,
        darts,
        recievedValue;       /* number of tasks */
    double workerResult,piSum;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numChildren);
    MPI_Comm_rank( MPI_COMM_WORLD, &processId );
    MPI_Comm commParent;  //Parent Communicator
    MPI_Comm_get_parent(&commParent);
    MPI_Status status;
    MPI_Request request;
    srandom (processId);





/* if from tag master is DIE then we can break */
piSum = 0;


   for(;;){
        MPI_Recv(&recievedValue, 1, MPI_INT,0,1, commParent, &status);
         if(recievedValue == -1){
                break;
        }
        workerResult = dboard(recievedValue);
       
        MPI_Send(&workerResult,1, MPI_DOUBLE,0,1, commParent);

    }


    MPI_Finalize();


}

double dboard(int darts)
{
#define sqr(x)	((x)*(x))
long random(void);
double x_coord, y_coord, pi, r; 
int score, n;
unsigned int cconst;  /* must be 4-bytes in size */
/*************************************************************************
 * The cconst variable must be 4 bytes. We check this and bail if it is
 * not the right size
 ************************************************************************/
if (sizeof(cconst) != 4) {
   printf("Wrong data size for cconst variable in dboard routine!\n");
   printf("See comments in source file. Quitting.\n");
   exit(1);
   }
   /* 2 bit shifted to MAX_RAND later used to scale random number between 0 and 1 */
   cconst = 2 << (31 - 1);
   score = 0;

   /* "throw darts at board" */
   for (n = 1; n <= darts; n++)  {
      /* generate random numbers for x and y coordinates */
      r = (double)random()/cconst;
      x_coord = (2.0 * r) - 1.0;
      r = (double)random()/cconst;
      y_coord = (2.0 * r) - 1.0;

      /* if dart lands in circle, increment score */
      if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
           score++;
      }

/* calculate pi */
pi = 4.0 * (double)score/(double)darts;
return(pi);
} 
