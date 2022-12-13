#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <iostream>

#define INF 99999
#define N 36
#define MAIN 0

using namespace std;

int main(int argc, char *argv[])
{

	int matrix[36][36] = {{0, 1, INF, INF, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, 0, 2, INF, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, 0, 3, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, 0, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, 0, 5, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 20, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {6, INF, INF, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, 0, 1, INF, INF, INF, INF, 6, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, 0, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, 0, 3, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, 6, INF, 3, INF, INF, 0, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 2, INF, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 4, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 5, INF, INF, INF, INF, INF, 10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 6, INF, INF, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, 2, INF, INF, 6, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 5, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 0, INF, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 3, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 14},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 1, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {25, INF, INF, 10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 1, 2, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, 3, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 3, INF, INF, 0, INF, INF, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF, INF, INF, 6, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 5, 0, INF, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, 0, INF, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 3, 0, INF, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2, 0, INF, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 3, INF, 1, 0, INF},
						  {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 1, 0}};

	int nProc, tId, procCol, procRow;
	double start_time, elapsed_time;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &tId);
	MPI_Status status;
	start_time = MPI_Wtime();

	int rootP = sqrt(nProc);
	int block = N / rootP;

	procCol = tId % rootP;
	procRow = tId / rootP;

	int startRow, endRow, startCol, endCol;

	int procC, procR, sRow, sCol, eRow, eCol;

	int localMatrix[block][block];
	// if(tId == MAIN){
	// 	std::copy(&matrix[0][0],
	//       &matrix[0][0] + block*block,
	//       &localMatrix[0][0]);
	// }

	if (tId == MAIN)
	{
		for (int p = 0; p < nProc; p++)
		{
			// procC = p / rootP;
			// procR = p % rootP;

			// sRow = (procR * N) / rootP;
			// sCol = (procC * N) / rootP;
			// eRow = (((procR + 1) * N) / rootP) - 1;
			// eCol = (((procC + 1) * N) / rootP) - 1;
			sRow = (p / rootP) * block;
			eRow = (((p / rootP) + 1) * block) - 1;
			sCol = (p % rootP) * block;

			for (int i = sRow; i <= eRow; i++)
			{

				MPI_Send(&(matrix[i][sCol]), block, MPI_INT, p, 0, MPI_COMM_WORLD);
			}
		}
	}

	for (int i = 0; i < block; i++)
	{
		MPI_Recv(&(localMatrix[i][0]), block, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	// cout << "PROCESSOR: " << tId << "\tDATA: " << localMatrix[0][0] << endl;
	// if(tId == 0){
	// 	for(int i = 0; i < block; i++){
	// 	for(int j = 0; j < block; j++){
	// 		cout << localMatrix[i][j] << "\t";
	// 	}
	// 	cout << endl;
	// }
	// }

	// if(tId == 3){
	// 	for(int i = 0; i< block;i++){
	// 		for(int j = 0; j < block; j++){
	// 				cout << localMatrix[i][j] << "\t";
	// 		}
	// 		cout << endl;

	// }
	// }

	MPI_Comm rowComm, colComm = MPI_COMM_WORLD;
	int rowId, colId;

	MPI_Comm_split(MPI_COMM_WORLD, procRow, tId, &rowComm);
	MPI_Comm_split(MPI_COMM_WORLD, procCol, tId, &colComm);

	MPI_Comm_rank(rowComm, &rowId);
	MPI_Comm_rank(colComm, &colId);

	// cout << tId << " " << rowId << " " << colId << endl;

	sRow = (tId / rootP) * block;
	eRow = (((tId / rootP) + 1) * block) - 1;
	sCol = (tId % rootP) * block;
	eCol = (((tId % rootP) + 1) * block) - 1;

	for (int k = 0; k < N; k++)
	{

		int root = k / block;
		int rowBuff[block], colBuff[block];
		// row wise send
		if (sRow <= k && k <= eRow)
		{

			for (int val = 0; val < block; val++)
			{
				rowBuff[val] = localMatrix[k % block][val];
			}

			if (procRow < rootP - 1)
			{
				// cout << tId << " " << procRow << "sending to " << procRow + 1 << endl;
				MPI_Send((rowBuff), block, MPI_INT, procRow + 1, 0, colComm);
			}

			if (procRow < rootP && procRow != 0)
			{
				// cout << tId << " " << procRow << "sending to " << procRow - 1 << "part2" << endl;
				MPI_Send((rowBuff), block, MPI_INT, procRow - 1, 0, colComm);
			}
		}
		else
		{
			if (sRow > k)
			{
				MPI_Recv(&(rowBuff), block, MPI_INT, procRow - 1, 0, colComm, &status);
				// cout << tId << " received from " << procRow - 1 << endl;

				if (procRow < rootP - 1)
				{
					// cout << tId << " " << procRow << "sending to " << procRow + 1 << "part4" << endl;
					MPI_Send(rowBuff, block, MPI_INT, procRow + 1, 0, colComm);
				}
			}
			else if (sRow < k && procRow != rootP - 1)
			{
				// cout << taskid << " receiveing from "<< rowid+1 << endl;
				MPI_Recv(&rowBuff, block, MPI_INT, procRow + 1, 0, colComm, &status);
				// cout << rowid << " IN HERE2" << endl;
				if (procRow > 0)
				{
					// cout << taskid << " " << rowid << "sending to " << rowid+1 <<"part3" <<endl;
					MPI_Send(rowBuff, block, MPI_INT, procRow - 1, 0, colComm);
				}
			}
		}

		// cout << "PAST ROWS \n";

		if(sCol <= k && k <= eCol){
			for (int val = 0; val < block; val++)
			{
				colBuff[val] = localMatrix[val][ k % block];
			}

			if (procCol < rootP - 1)
			{
				// cout << tId << " " << procCol<< "sending to " << procCol + 1 << endl;
				MPI_Send((colBuff), block, MPI_INT, procCol + 1, 0, rowComm);
			}

			if (procCol < rootP && procCol != 0)
			{
				// cout << tId << " " << procCol << " sending to " << procCol- 1 << " K is : " << k << endl;
				// if(k == 35){
				// 	cout << "task ID: " << tId << "  column ID: " << procCol << endl;
				// }
				MPI_Send((colBuff), block, MPI_INT, procCol - 1, 0, rowComm);
				// if(k == 35){
				// 	cout << "task ID: " << tId << " SENT TO  " << procCol - 1 << endl;
				// }
			}
			
		}else{

			if(sCol > k){
				MPI_Recv(&colBuff, block, MPI_INT, procCol - 1, 0, rowComm, &status);
				// cout << tId << " received from " << procCol - 1 << endl;

				if (procCol < rootP - 1)
				{
					// cout << tId << " " << procRow << "sending to " << procRow + 1 << "part4" << endl;
					// if(k == 35){
					// 	cout << "HEREEEEEE";
					// }
					MPI_Send(colBuff, block, MPI_INT, procCol+ 1, 0, rowComm);
				}

			}else if (sCol < k && sCol != rootP - 1)
			{
				// cout << taskid << " receiveing from "<< rowid+1 << endl;
				MPI_Recv(&colBuff, block, MPI_INT, procCol+ 1, 0, rowComm, &status);
				// cout << rowid << " IN HERE2" << endl;
				if (procCol > 0)
				{
					// cout << tId << " " << procCol << "sending to " << procCol +1 <<"part3" <<endl;
					// if(k == 35){
					// 	cout << "HEREEEEEE";
					// }
					MPI_Send(colBuff, block, MPI_INT, procCol - 1, 0, rowComm);
				}
			}

		}



		for (int r = 0; r < block; r++)
		{

			// cout << rowBuff[r];
			for (int c = 0; c < block; c++)
			{

				localMatrix[r][c] = min((localMatrix[r][c]), rowBuff[c] + colBuff[r]);
			}
		}

		// if(tId == MAIN){
		// 	cout << k << endl;
		// }
	}
	// if(tId == 1){

	// 	 for(int i = 0; i < block; i++){

	// 	 for(int j=0; j < block; j++){
	// 		cout << localMatrix[i][j] << "\t";
	// 	 }
	// 	 cout << endl;

	//  }
	// }
	int finalArray[N][N];

	// if(tId == 0){
	// 	MPI_Gather( &(localMatrix[0]) , block*block , MPI_INT , finalArray, block * block , MPI_INT , 0 , MPI_COMM_WORLD);

	// }else{
	// 	MPI_Gather( &(localMatrix[0]) , block*block , MPI_INT ,NULL , 0 , MPI_INT , 0 , MPI_COMM_WORLD);

	// }

	for(int d=0;d<nProc;d++){
        for(int i=0;i<block;i++){
        {
            MPI_Send(&localMatrix[i][0],block,MPI_INT,0,d,MPI_COMM_WORLD);
        }  
    }
    }

    if(tId==0){
        for (int j=0;j<nProc;j++){
            int startRow=(j/rootP)*(block);
            int endRow=(((j/rootP)+1)*(block)-1);
            int startCol=(j%rootP)*(block);
            for (int i=startRow;i<=endRow;i++){
                
                MPI_Recv(&(finalArray[i][startCol]),block,MPI_INT,j,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            }
        }
    }

    if(tId==0){
        for (int i = 0; i < 36; i++){
        // loop for each column in a processors matrix 
            for (int j = 0; j < 36; j++){    
                cout <<finalArray[i][j] << ", ";
            }
        cout << endl;}
    }

	// if (tId == 0)
	// {
	// 	for (int i = 0; i < N; i++)
	// 	{

	// 		for (int j = 0; j < N; j++)
	// 		{

	// 			cout << finalArray[i][j] << " ";
	// 		}
	// 		cout << endl;
	// 	}
	// }
	elapsed_time = MPI_Wtime() - start_time;
	if(tId==0){
		cout << "TIME TAKEN: \t" << elapsed_time;

	}
	MPI_Finalize();
}
