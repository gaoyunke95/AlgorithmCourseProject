#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class undirectedEdge{
	public:
		int Ni;
		int Nj;
		int edgeCost;
		undirectedEdge *next;
	
		
		undirectedEdge(){
			Ni=0;
			Nj=0;
			edgeCost=0;
			next=NULL;
		}
		undirectedEdge(int a, int b, int c){
			Ni=a;
			Nj=b;
			edgeCost=c;
			next=NULL;
		}
			
};

class KruskalMST{
	public:
		int numNodes;
		int *inWhichSet;
		int numSets;
		int totalMSTCost;

		undirectedEdge *MSTofG= new undirectedEdge();
		undirectedEdge *edgeListHead= new undirectedEdge();
		KruskalMST(int size){
			inWhichSet= new int[size];
			for(int i=0;i<size;i++){
				inWhichSet[i]=i;
			}
		}

		void insertEdge(undirectedEdge *edge, undirectedEdge *edgeHead){
			undirectedEdge *walker=edgeHead;
			while(walker->next!=NULL && edge->edgeCost>walker->next->edgeCost){
				walker=walker->next;
			}
			if(walker->next==NULL){
				walker->next=edge;
				edge->next=NULL;
			}
			else{
				edge->next=walker->next;
				walker->next=edge;
			}
			
		}		
		
		void printList(undirectedEdge *edgeListHead,ofstream &outFile2){

			
			outFile2<<"ListHead-->";
			
	
			outFile2<<"("<<edgeListHead->Ni<<" , "<<edgeListHead->Nj<<" , "<<edgeListHead->edgeCost<<")-->";

			while(edgeListHead->next!=NULL){
				outFile2<<"("<<edgeListHead->next->Ni<<" , "<<edgeListHead->next->Nj<<" , "<<edgeListHead->next->edgeCost<<")-->";
				edgeListHead=edgeListHead->next;
			}
			if(edgeListHead->next==NULL){
				outFile2<<"NULL";
			}
			outFile2<<endl;

		}
		
		undirectedEdge *removedEdge(undirectedEdge *listHead){
			undirectedEdge *removedEdge= listHead->next;

			if(inWhichSet[removedEdge->Ni]==inWhichSet[removedEdge->Nj]&&removedEdge->next!=NULL){
				removedEdge= removedEdge->next;

			}
				
			if(listHead->next->next!=NULL){
				listHead->next=listHead->next->next;
			}
			return removedEdge;
		}


		
		void pushEdge(undirectedEdge *nextEdge, undirectedEdge *MSTofG){
			undirectedEdge *walker=MSTofG;
			while(walker->next!=NULL){
				walker=walker->next;
			}
			walker->next=nextEdge;
			nextEdge->next=NULL;
		}

		
		void merge2Sets(int Ni, int Nj){
			int inSet;//the index in the set; 
			int changeVinSet;// value it needs change to 
			if(inWhichSet[Ni]<inWhichSet[Nj]){
				inWhichSet[Nj]=inWhichSet[Ni];
				changeVinSet=inWhichSet[Ni];
				inSet=Nj;
			}
			else{
				inWhichSet[Ni]=inWhichSet[Nj];
				changeVinSet=inWhichSet[Nj];
				inSet=Ni;
			}
			
			checkList(changeVinSet,inSet);

		}
		void checkList(int changeVinSet,int inSet){
			for(int i=0;i<=numNodes;i++){
				if(inWhichSet[i]==inSet){
					inWhichSet[i]=changeVinSet;
				}
			}
		}
		void printSet(ofstream &outFile2){
			outFile2<<endl;
			outFile2<<"inWhichSet is:";
			for(int i=0;i<=numNodes;i++){
				outFile2<<inWhichSet[i];
			}
			outFile2<<endl;
		}
		void printMSTofG(ofstream &outFile1){
			outFile1<<"***A Kruskal's MST of the input graph is given below:***"<<endl;
			outFile1<<numNodes<<endl;
			undirectedEdge *walker=MSTofG->next;
			while(walker->next!=NULL){
				
				outFile1<<walker->Ni<<" "<<walker->Nj<<" "<<walker->edgeCost<<endl;
				walker=walker->next;
			}
			outFile1<<walker->Ni<<" "<<walker->Nj<<" "<<walker->edgeCost<<endl;
			outFile1<<"*** The total cost of a Kruskal's MST is:"<< totalMSTCost;
		}
};

int main(int argc, const char *argv[]){
	ifstream inFile;
	ofstream outFile1;
	ofstream outFile2;
	
	inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	
	if(!inFile.is_open()){
		cout<<"no file find";
	}
	
	
	int numNodes;
	inFile>>numNodes;
	int size=numNodes+1;

	int a;
	int b;
	int c;
	
	undirectedEdge *x= new undirectedEdge();
	KruskalMST *k= new KruskalMST(size);	
	k->numNodes=numNodes;
	
	while(inFile>>a>>b>>c){

		undirectedEdge *newEdge= new undirectedEdge(a,b,c);
		k->insertEdge(newEdge,k->edgeListHead);
		k->printList(k->edgeListHead,outFile2);
		
	}
	
	k->numSets=numNodes;
	
	while(k->numSets!=1){
	
		undirectedEdge *nextEdge= k->removedEdge(k->edgeListHead);
		k->pushEdge(nextEdge,k->MSTofG);
		k->totalMSTCost+= nextEdge->edgeCost;
		k->merge2Sets(nextEdge->Ni,nextEdge->Nj);
		k->numSets--;
		
		k->printSet(outFile2);
		k->printList(k->MSTofG,outFile2);
	}

	k->printMSTofG(outFile1);
	inFile.close();
	outFile1.close();
	outFile2.close();
	return 0;

}
