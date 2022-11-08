/**********************************************************************
 * FILE: mpi_pi_reduce.c
 * OTHER FILES: dboard.c
 * DESCRIPTION:  
 *   MPI pi Calculation Example - C Version 
 *   Collective Communication example:  
 *   This program calculates pi using a "dartboard" algorithm.  See
 *   Fox et al.(1988) Solving Problems on Concurrent Processors, vol.1
 *   page 207.  All processes contribute to the calculation, with the
 *   master averaging the values for pi. This version uses mpc_reduce to 
 *   collect results
 * AUTHOR: Blaise Barney. Adapted from Ros Leibensperger, Cornell Theory
 *   Center. Converted to MPI: George L. Gusciora, MHPCC (1/95) 
 * LAST REVISED: 06/13/13 Blaise Barney
**********************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

void srandom (unsigned seed);
double dboard (int darts);
#define DARTS 200000     /* number of throws at dartboard */
#define ROUNDS 100      /* number of times "darts" is iterated */
#define MASTER 0        /* task ID of master task */

int main (int argc, char *argv[])
{
double	homepi,         /* value of pi calculated by current task */
	pisum,	        /* sum of tasks' pi values */
	pi,
	startTime,
	duration,
	global,
	endTime,		       
	avepi;	        /* average pi value for all iterations */
		 /* average of pi after "darts" is thrown */
int	taskid,	        /* task ID - also used as seed number */
	numtasks,       /* number of tasks */
	rc,             /* return code */
	i,
   ready,
   childId,
   totalDarts,
   numChildren;

const int dartsToSend = 5000;
int dartsLeft = DARTS;
int dartsSent = 0;
int kill = -1;
MPI_Status status;

/* Obtain number of tasks and task ID */
MPI_Comm childComm;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);

totalDarts = DARTS;

 if ( argc != 2 )
        printf( "usage: %s <number of workers>\n", argv[0]);
    else
        numChildren = atoi( argv[1] ); //Given by user in command line e.g: 'mpirun -np 1 master 4' -> numChildren=4

startTime = MPI_Wtime();
printf ("MPI task %d has started...\n", taskid);

MPI_Comm_spawn( "c", argv, numChildren, MPI_INFO_NULL, 0, MPI_COMM_SELF, &childComm, MPI_ERRCODES_IGNORE );


for(i = 0; i < numChildren;i++){
	MPI_Send(&dartsToSend,1,MPI_INT,i,1, childComm);
	totalDarts-= dartsToSend;
}



avepi = 0;

int increment = 0;
while(dartsLeft > 0){

	MPI_Recv(&pi,1,MPI_DOUBLE,MPI_ANY_SOURCE,1,childComm,&status);
	MPI_Send(&dartsToSend,1,MPI_INT,status.MPI_SOURCE,1, childComm);
	

	avepi = ((avepi * increment) + pi)/(increment + 1); 
    printf("   After %8d throws, average value of pi = %10.8f\n",
    (DARTS * (increment + 1)),avepi);
	increment++;
	dartsLeft-= dartsToSend;
	dartsSent+= dartsToSend;
}

// for(;;){

// 	MPI_Recv(&pi,1,MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, childComm, &status);

	

// }

while(dartsSent < DARTS){
	MPI_Recv(&pi,1,MPI_DOUBLE,MPI_ANY_SOURCE,1,childComm,&status);
	avepi = ((avepi * increment) + pi)/(increment + 1); 
    printf("   After %8d throws, average value of pi = %10.8f\n",
    (DARTS * (increment + 1)),avepi);
	increment++;

	if(dartsSent == DARTS){
		break;
	}
	MPI_Send(&dartsToSend,1,MPI_INT,i,1, childComm);

}


for(i = 0;i <numChildren;i++){
	MPI_Send(&kill,1,MPI_INT,i,1, childComm);
}

if (taskid == MASTER){
   printf ("\nReal value of PI: 3.1415926535897 \n");
}
endTime = MPI_Wtime();
printf("AVERAGE PI IS: %lf",avepi);
duration = endTime - startTime;

	
MPI_Finalize();
if(taskid == MASTER){
printf("\nRuntime = \t %f\n", duration);
	
} 


return 0;
}


