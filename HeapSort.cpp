
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
class HeapSort{
public:
    int rootIndex=1;
    int fatherIndex;
    int leftKidIndex;
    int rightKidIndex;
    int minKidIndex;
    int *heapAry;
    
    HeapSort(int count){
        heapAry = new int[count];
		heapAry[0]=0;
        
    }
    void buildHeap(ifstream &inFile2,ofstream &outFile1){
        int data;
        while(inFile2>>data){
			
            insertOneDataItem(data);
            int kidIndex=heapAry[0];
            bubbleUp(kidIndex);
            printHeap(outFile1);
        }
            
    }
    void insertOneDataItem(int data){
        heapAry[0]++;
        heapAry[heapAry[0]]=data;
    }
    void bubbleUp(int kidIndex){
        if(isRoot(kidIndex)){
            return;
        }
        else{
            fatherIndex=kidIndex/2;
            if(heapAry[kidIndex]<heapAry[fatherIndex]){
                int temp= heapAry[kidIndex];
                heapAry[kidIndex]=heapAry[fatherIndex];
                heapAry[fatherIndex]=temp;
                bubbleUp(fatherIndex);
            }
        }
    }
    
    bool isRoot(int index){
        if(index==1){
            return true;
        }
        return false;
    }
    
    void deleteHeap(ofstream &outFile2,ofstream &outFile1){
        
        while(heapAry[0]!=0){
            int data= getRoot();
            outFile2<<data<<endl;
            deleteRoot();
            fatherIndex=rootIndex;
            bubbleDown(fatherIndex);
            printHeap(outFile1);
            
        }
        
    }
    
    int getRoot(){
        return heapAry[1];
    }
    void deleteRoot(){
        heapAry[1]=heapAry[heapAry[0]];
        heapAry[0]--;
        
    }
    void bubbleDown(int fatherIndex){
        if(isLeaf(fatherIndex)){
            return;
        }
        else{
            int MinIndex=findMinKidIndex(fatherIndex);
            
            if(heapAry[fatherIndex]>heapAry[MinIndex]){
                int temp=heapAry[fatherIndex];
                heapAry[fatherIndex]=heapAry[MinIndex];
                heapAry[MinIndex]=temp;
                bubbleDown(MinIndex);
            }
        }
    }
    int findMinKidIndex(int fatherIndex){
        leftKidIndex=fatherIndex*2;
        rightKidIndex=fatherIndex*2+1;
        
        if(heapAry[leftKidIndex]>heapAry[rightKidIndex]){
            return rightKidIndex;
        }
        else{
            return leftKidIndex;
        }
    }
    void printHeap(ofstream &outFile1){
        for(int a=0;a<= heapAry[0];a++){
            outFile1<<heapAry[a]<<" ";
        }
        outFile1<<endl;
    }
    
    
    bool isHeapEmpty(){
        if(heapAry[0]==0)
            return true;
        return false;
    }
    bool isLeaf(int fatherIndex){
        leftKidIndex= fatherIndex*2;
        rightKidIndex=fatherIndex*2+1;
        if(leftKidIndex>heapAry[0]&&rightKidIndex>heapAry[0]){
            return true;
        }
        return false;
    }
    
};

int main(int argc, const char * argv[]) {
    ifstream inFile;
    ifstream inFile2;
    ofstream outFile1;
    ofstream outFile2;
    int count=0;
    inFile.open(argv[1]);
    inFile2.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    
    if(!inFile.is_open()){
        cout<<"no file find";
    }
    int data;
    
    while(inFile>>data){
		count++;
    }

    HeapSort *a= new HeapSort(count+1);
    a->buildHeap(inFile2,outFile1);
    a->deleteHeap(outFile2,outFile1);
    inFile.close();
    inFile2.close();
    outFile1.close();
    outFile2.close();
    return 0;
}

