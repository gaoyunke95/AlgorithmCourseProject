#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class BucketSort{
public:

    int *BucketAry;
    int size;
    BucketSort(int size){
        BucketAry= new int[size];
        
		for(int i=0;i<size;i++){
            BucketAry[i]=0;
	    }
        this->size=size;
    }
    
    int HashFunction(int x){
    	int index;
    	index=x;
    	return index;
    }
};


int main(int argc,char *argv[]) {
    ifstream inFile;
    ofstream outFile1;
    
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    
    if(!inFile.is_open()){
        cout<<"no file find";
    }
   
    int a;
    int max=0;
    while(inFile>>a){       		
		if(a>=max){
            max=a;
        }
    }
   
    int size= max+1;
    
	BucketSort *x= new BucketSort(size);
	
	inFile.clear();
	inFile.seekg(0, inFile.beg);
    
	int num;
    
	while(inFile>>num){
    	int z;
		z=x->HashFunction(num);
        x->BucketAry[num]++;
    }
    

    int index=0;
    while(index<size){
    	while(x->BucketAry[index]>0){
			outFile1<<index<<" ";
    		x->BucketAry[index]--;
    	}
    	
    	index++;
    }
    
    inFile.close();
    outFile1.close();
    return 0;
}
