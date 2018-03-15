#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<sstream>

using namespace std;

class DijktraSSS{
	public:
		int numNodes;
		int sourceNode;
		int minNode;
		int currentNode;
		int newCost;
		int** costMatrix;
		int index=numNodes+1;
		int* fatherAry;
		int* toDoAry;
		int* bestCostAry;
		
		DijktraSSS(){
			
		}
		
		void loadCostMatrix(int x,int y,int c){
				costMatrix[x][y]=c;
		}
		void setBestCostAry(int x){
			bestCostAry= new int[index];
			for(int i=0;i<=numNodes;i++){
				bestCostAry[i]=costMatrix[x][i];
			}
		}
		
		void setFatherAry(int x){
			fatherAry=new int[index];
			for(int i=1; i<=numNodes;i++)
				fatherAry[i]=x;
		}
		
		void setToDoAry(int x){
			toDoAry= new int[index];
			for(int i=0;i<=numNodes;i++){
				toDoAry[i]=1;
				if(i==sourceNode||i==0){
					toDoAry[i]=0;
				}
			}
		}
		
		int findMinNode(){
			int temp=9999;
			for(int i=0;i<=numNodes;i++){
			
				if(toDoAry[i]==1&&bestCostAry[i]<temp){
						temp=bestCostAry[i];
						minNode=i;
				}
			}
			return minNode;
		}
		
		void markMinNode(int x){
			toDoAry[x]=0;
		}
		int checkToDoAry(){
			int v=0;
			for(int i=0;i<index;i++){
				if(toDoAry[i]==1){
					v=1;
				}
			}
			return v;
		}
		int computeCost(int x, int y){
			int cost;
			cost= bestCostAry[x]+costMatrix[x][y];
			return cost;
		}
		
		void changeCost(int x, int y){
			bestCostAry[x]= y;
			
		}
		
		void changeFather(int x, int y){
			fatherAry[x]=y;
		}
		void debugPrint(ofstream &outFile2)
		{
			outFile2 << "The soruceNode is: " << sourceNode<<endl;
			outFile2 << "The fatherAry is: ";
			for(int i=1; i<=numNodes; i++){
			
				outFile2 << fatherAry[i] << " ";
			}
			
			outFile2<<endl;
			outFile2 << "The bestCostAry is: ";
			for(int i=1; i<=numNodes; i++){	
				outFile2 << bestCostAry[i] << " ";
			}
			
			outFile2<<endl;
			outFile2 << "The toDoAry is: ";
			for(int i=1; i<=numNodes; i++){
			
				outFile2 << toDoAry[i] << " ";
			}
			outFile2 << endl << endl;
		}
		
		void printShortestPath(int x,ofstream &outFile1){

			printFather(x,outFile1);
			outFile1<<bestCostAry[x];
			outFile1<<endl;
			
		}
		
		void printFather(int index,ofstream &outFile1){
			if(index==sourceNode){
				outFile1<<sourceNode<<" :cost = ";
			}
			else{
				outFile1<<index<< "<- ";
				printFather(fatherAry[index],outFile1);
			}
		}
		
};

int main(int argc, char	**argv){
	ifstream inFile;
    ofstream outFile1;
    ofstream outFile2;
    
    inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	
	if(!inFile.is_open()){
        cout<<"no file find";
    }
   

	DijktraSSS	*x= new DijktraSSS();
    
    inFile>>x->numNodes;
	inFile>>x->sourceNode;
    int index= x->numNodes+1;
    
	x->costMatrix= new int*[index];
    for(int i=0; i<index; i++){
    	x->costMatrix[i]= new int[index];
    }
    for(int i=0;i<index; i++){
        for(int j=0;j<index;j++){
            x->costMatrix[i][j]=9999;
            if(i==j||i==0||j==0){
            	x->costMatrix[i][j]=0;
            }
        } 
    }
    
    int y, z,c;
    while(!inFile.eof()){
    	inFile>>z>>y>>c;
    	x->loadCostMatrix(z,y,c);
    }
	
    x->setBestCostAry(x->sourceNode);
    x->setFatherAry(x->sourceNode);
    x->setToDoAry(x->sourceNode);
    

	while(x->checkToDoAry()==1){
		x->minNode=x->findMinNode();
		x->markMinNode(x->minNode);
		x->debugPrint(outFile2);
		
		int currentNode=1;
		while(currentNode<index){
			if(x->toDoAry[currentNode]==1){
				x->newCost=x->computeCost(x->minNode,currentNode);
				if(x->newCost<x->bestCostAry[currentNode]){
					x->changeCost(currentNode,x->newCost);
					x->changeFather(currentNode,x->minNode);
					x->debugPrint(outFile2);
				}
			}
			currentNode++;
		}
	}
	
	outFile1<< "========================================"<<endl;
	outFile1<< "There are "<< x->numNodes <<" nodes in the input graph." << endl;
	outFile1<< "========================================"<<endl;
	outFile1<< "Source node = " << x->sourceNode << endl;
	outFile1<< "The shortest paths from node "<< x->sourceNode << " are: "<<endl<<endl;
			
			
	x->currentNode=1;
	while(x->currentNode<index){
		outFile1<<"The Path from " <<x->sourceNode << " to " <<x->currentNode<<": ";
		x->printShortestPath(x->currentNode,outFile1);
		x->currentNode++;
	}
	
	inFile.close();
	outFile1.close();
	outFile2.close();
}
