#include <mpi.h>
#include <stdio.h>
#include <math.h>       /* log2 */
#include <stdlib.h>
#include <sys/time.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

using namespace std;


void swap(vector<int>& v, int x, int y);

void quicksort(vector<int> &vec, int L, int R) {
    int i, j, mid, piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid];

    while (i<R || j>L) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j); //error=swap function doesnt take 3 arguments
            i++;
            j--;
        }
        else {
            if (i < R)
                quicksort(vec, i, R);
            if (j > L)
                quicksort(vec, L, j);
            return;
        }
    }
}

void swap(vector<int>& v, int x, int y) {
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;

}



int main(int argc, char * argv[]){
    int id;
    int numProcessors; 

    int pivot;
    int dimensions;
    
    int s = 160000;
    int mainArray[s];
    srand((int)time(0));
    // Print the values in the vector
    for (int i = 0; i < s; i++) {
        mainArray[i] = rand() % 300;
        
    }

    double startTime, endTime, duration;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numProcessors);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    dimensions = log2(numProcessors);   

    startTime = MPI_Wtime();
   
    int count = s / numProcessors;
    int recvArr[count];
    int sendArr[count];
    MPI_Scatter(mainArray,count,MPI_INT,recvArr,count,MPI_INT,0, MPI_COMM_WORLD);

     if(id == 0){
        pivot = recvArr[0];
    }
    
    MPI_Bcast(&pivot,1,MPI_INT, 0, MPI_COMM_WORLD);
    int groupSize = numProcessors;

    MPI_Comm x = MPI_COMM_WORLD;
    vector<int> mergedVector;

    int arraySize = (sizeof(recvArr)/sizeof(*recvArr));
        
    mergedVector.insert(mergedVector.end(), recvArr, recvArr + arraySize);
    int sendSize;
    for(int i = (dimensions-1); i >= 0; i--){

       

        if(i != (dimensions-1)){
            if((id % groupSize) == 0){
                int index = mergedVector.size() / 2;
                pivot = mergedVector[index];
            }

            MPI_Bcast(&pivot,1,MPI_INT, 0, x);

          
        }
        int nId = id ^ (1 << i);
        vector<int> high;
        vector<int> low;


        for(int j = 0;j < mergedVector.size(); j++){
        if(mergedVector[j] > pivot){
            high.push_back(mergedVector[j]);
        }else{
            low.push_back(mergedVector[j]);
        }
        }


        // for(int c = 0; c < high.size(); c++){
        //     cout << "--" << id << "--" << high[c];
        // }
        

        int highSize = high.size();
        int lowSize = low.size();
        int recSize;
        vector<int> recVector;
        
       
       if(nId > id){
            MPI_Send(&highSize, 1, MPI_INT, nId,1, MPI_COMM_WORLD);
            MPI_Send(high.data(), highSize, MPI_INT, nId, 1, MPI_COMM_WORLD);

            MPI_Recv(&recSize, 1 , MPI_INT, nId, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            recVector.resize(recSize);
            MPI_Recv(recVector.data(),recSize, MPI_INT, nId, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            mergedVector.clear();
            mergedVector.insert(mergedVector.end(),low.begin(),low.end());
            mergedVector.insert(mergedVector.end(),recVector.begin(),recVector.end());

       }else{
          
            MPI_Recv(&recSize, 1 , MPI_INT, nId, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            recVector.resize(recSize);
            MPI_Recv(recVector.data(),recSize, MPI_INT, nId, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          
            MPI_Send(&lowSize, 1, MPI_INT, nId,1, MPI_COMM_WORLD);
            MPI_Send(low.data(), lowSize, MPI_INT, nId, 1, MPI_COMM_WORLD);
            mergedVector.clear();
            mergedVector.insert(mergedVector.end(),high.begin(),high.end());
            mergedVector.insert(mergedVector.end(),recVector.begin(),recVector.end());
       }
        //  if(id == 1){
        //     cout << "HIGH LENGTH " << highSize << endl;
        //     cout << "LOW LENGTH " << lowSize << endl;
        //     cout << "TOTAL LENGTH " << mergedVector.size() << endl;
        //     for(int c = 0; c < high.size();c++){
        //         cout << "HIGH: " << high[c] << endl;
        //     }
        //      for(int c = 0; c < low.size();c++){
        //         cout << "LOW: " << low[c] << endl;
        //     }
        // }
    //  if(id == 1){
    //         cout << mergedVector.size() << endl;
    //     }

        groupSize /= 2;


        MPI_Comm_split(x, id / groupSize,id, &x);
        high.clear();
        low.clear();
        sendSize = mergedVector.size();

    //    cout << "ME: " << id << " recieved: " << recVector[0] << endl;
        
       
        }
        
        
        
        // if(id == 1){
        //     cout << "WHAAAAT";
        //     cout << mergedVector.size();
        //     // for(int i = 0; i < mergedVector.size();i++){
        //     //     cout << mergedVector[i] << endl;
        //     // }
        // }

        // if(id == 0 || id == 3){
        //     cout << "ID: " << id << endl;
        //     for(int i = 0; i < mergedVector.size(); i++){
        //         cout << "THIS: " << id << "ELEMENT: " << mergedVector[i] << endl;
        // }
        // }
        

        // cout << "ID : " << id << "EL: " << mergedVector[1] <<endl;

        quicksort(mergedVector,0, mergedVector.size() -1);
        // if(id == 2 ){
        //     for(int i = 0; i < mergedVector.size(); i++){
        //         cout << "---------- ID: " << id << "-----------  " << "Element: " << mergedVector[i] << endl;
        //     }
        // }
        // if(id == 3){
        //     for(int i = 0; i < mergedVector.size(); i++){
        //         cout << "---------- ID: " << id << "-----------   " << "Element: " << mergedVector[i] << endl;
        //     }
        // }
        // cout << "THIS ID: " << id << " ELEMENT 2: " << mergedVector[5] << endl;

        // for(int i = 0;i < mergedVector.size(); i++){
           
        //         cout << "THIS ID IS: " << id << "\t VALUE: " << mergedVector[i] << endl;
            
        // }

       
   
        int finalArray[s];
        int sizeArray[numProcessors];
        int displacement[numProcessors];
        sizeArray[0] = mergedVector.size();
        
        if(id == 0){
            for(int i = 1; i < numProcessors; i++){
                int recSize;
                MPI_Recv(&recSize,1,MPI_INT,i,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                sizeArray[i] = recSize;
                
            }
        }else{
            MPI_Send(&sendSize,1,MPI_INT,0,1,MPI_COMM_WORLD);
        }
        displacement[0] = 0;

        if(id == 0){
            for(int i = 1; i < numProcessors; i++){
                displacement[i] = displacement[i-1] + sizeArray[i-1];
                
            }
        }

        
        
        
        
        MPI_Gatherv(mergedVector.data(),mergedVector.size(),MPI_INT,finalArray,sizeArray,displacement,MPI_INT, 0, MPI_COMM_WORLD);

        // MPI_Gatherv(mergedVector.data(),mergedVector.size(),MPI_INT,NULL,NULL,NULL,MPI_INT, 0, MPI_COMM_WORLD);

       
       

        endTime = MPI_Wtime();
        
        // if(id == 0){
        //        for(int i = 0;i < s; i++){
        //     cout << finalArray[i] << endl;
        // }
        // }
        
        duration = endTime - startTime;
        if(id==0){
            printf("TIME IS: %lf", duration);
        }
        
        MPI_Finalize();

    return 0;   

}