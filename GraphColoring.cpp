#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

class Node{
	public:
		int colorId;
		Node *next;
		
		Node(){
			colorId=0;
			next=NULL;
		}
		
		Node(int i){
			colorId=i;
			next=NULL;
		}
};

class graphColoring{
	public:
		int **adjacencyMatrix;
		Node *usedColorTop;
		int newColor;
		int numNode;
		int size;
		
		graphColoring(int size){
			adjacencyMatrix=new int *[size];
			for(int i=0;i<size;i++){
				adjacencyMatrix[i]=new int[size];
			}
			for(int i=0;i<size;i++){
				for(int j=0; j<size;j++){
					adjacencyMatrix[i][j]=0;
				}
			}
			
			this->size=size;
			
			usedColorTop=new Node();
		}
		
		void loadMatrix(int a, int b){
			adjacencyMatrix[a][b]=1;
			adjacencyMatrix[b][a]=1;

		}
		
		void printMatrix(ofstream &outFile1){
			for(int i=1;i<size;i++){
				for(int j=1;j<size;j++){
					outFile1<<adjacencyMatrix[i][j]<<" ";	
				}
				outFile1<<endl;
			}
		}
		
		int checkAllcolored(){
			int v=0;
			for (int i=1;i<size;i++){
				if(adjacencyMatrix[i][i]==0){
					v=1;
				}
			}
			return v;
		}
		
		int findUsedColor(int currentNode){
            
            Node *walker=usedColorTop->next;
            
			while(walker!=NULL){
                int color=walker->colorId;
				if(checkAdjacent(currentNode, color)==1){
                    walker=walker->next;
                }
                else{
                	return color;
                }        
            }
            return 0;
			
		}
		
		int checkAdjacent(int id, int color){
			int v=0;
			for(int i=1;i<size;i++){
				if(adjacencyMatrix[id][i]==1){//check the where is the adjacentNode;
					if(adjacencyMatrix[i][i]==color){// check if the adjacentNode is using the color or not;
					v=1;}
				}	
			}
			return v;
		}
		
		void pushUsedColor(int newColor){
			Node *newNode= new Node(newColor);
			Node *walker=usedColorTop;
			
			while(walker->next!=NULL){
				walker=walker->next;
			}
			if(walker->next==NULL){
				walker->next=newNode;
				newNode->next=NULL;
			}
			
		}
};
int main(int argc, char **argv){

	 ifstream inFile;
	 ofstream outFile1;
	 
	 inFile.open(argv[1]);
	 outFile1.open(argv[2]);
	 
	 if(!inFile.is_open()){
	 	cout<<"file not find";
	 }
	 
	 int numNode;
	 inFile>>numNode;
	 
	 int size=numNode+1;
	 graphColoring *g=new graphColoring(size);
	 
	 int a;
	 int b;
	 while(inFile>>a>>b){
	 	g->loadMatrix(a,b);
		outFile1<<"there is an edge: <"<<a<<","<<b<<"> and <"<<b<<","<<a<<">"<<endl;
		
	 }
	 
	 outFile1<<"initial Matrix:"<<endl;
	 g->printMatrix(outFile1);
	
	 outFile1<<endl;
	
	 int currentNode=0;
	 int newColor=0;
	 
	 while(g->checkAllcolored()==1){
	 	currentNode++;
	 	outFile1<<"currentNode: "<<currentNode<<";the currentNode is not colored yet"<<endl;
	 	g->printMatrix(outFile1);
		
		outFile1<<endl;
		int usedColor;
	 	
	 	usedColor=g->findUsedColor(currentNode);
	 	
	 
	 	
	 	if(usedColor>0){
	 		g->adjacencyMatrix[currentNode][currentNode]=usedColor;
	 	}
	 	else{
	 		newColor++;
	 		g->adjacencyMatrix[currentNode][currentNode]=newColor;
	 		g->pushUsedColor(newColor);
	 	}
		
		
	 }
	 
	 outFile1<<"Final Matrix:"<<endl;
	 outFile1<<"the number of color used: "<<newColor<<endl;
	 g->printMatrix(outFile1);
	 
	 inFile.close();
	 outFile1.close();
	 return 0;
}
