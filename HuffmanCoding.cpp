#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<sstream>

using namespace std;

class listBinTreeNode{
	public:
		string chStr;
		int prob;
		string code;
		listBinTreeNode *next;
		listBinTreeNode *left;
		listBinTreeNode *right;
		
		listBinTreeNode(){
			chStr="dummy";
			prob=0;
			code="";
			next=NULL;
			left=NULL;
			right=NULL;
		}
		listBinTreeNode(string input,int p){
			chStr=input;
			prob=p;
			code="";
			next=NULL;
			left=NULL;
			right=NULL;
		}
		
		void printNode(listBinTreeNode *newNode,ofstream &outFile5){
			
			
				outFile5<<"newNode is: " <<newNode->chStr;
				outFile5<<"  the prob of the newNode:" <<newNode->prob<<endl;
				if(newNode->next!=NULL){
					outFile5<<"next node is:"<<newNode->next->chStr<<endl;
				}
				if(newNode->next==NULL){
					outFile5<<"there has no next Node"<<endl;;
				}
				if(newNode->left!=NULL){
				
					outFile5<<"left node is:"<<newNode->left->chStr<<endl;
				}
				if(newNode->right!=NULL){
				
				outFile5<<"right node is:"<<newNode->right->chStr<<endl;
				}
		}
		
};



class HuffmanLinkedList{
	public:
	 	int size=0;
		listBinTreeNode *listHead;
		listBinTreeNode *spot;
	
	
		HuffmanLinkedList(){
			listHead= new listBinTreeNode();
		}
	 
	 	listBinTreeNode *findSpot(int prob){
			listBinTreeNode *walker;
			listBinTreeNode *spot=NULL;
			walker=listHead;
		
			while(walker->next!=NULL){
				if(walker->next->prob>=prob){
					spot=walker;
					return spot;
				}
				else{
					walker=walker->next;
				}
			}

			if(walker->next==NULL){
				spot=walker;
			}
			return spot;
		}
	
		void listInsert(listBinTreeNode *spot, listBinTreeNode *newNode ){
	
			if(spot->prob>=newNode->prob){
				newNode->next=spot;
				listHead=newNode;
			}
			newNode->next=spot->next;
			spot->next=newNode;
		}
		
		bool isEmpty(){
			return(size==0);
		}
		
		string printList(){
			string word="";
			stringstream output;
			
			int count=0;
			listBinTreeNode *printList= listHead;
	
			if(printList->chStr=="dummy"&&printList->next==NULL){
				output<<"ListHead-->("<<printList->chStr<<printList->prob<<",null)";
				count=1;
				word=output.str();
			}
	
				
			else{
				output<<"ListHead";
				while(printList->next!=NULL&&count<15){
	
					output<<"-->("+printList->chStr<<" ,"<<printList->prob<<","<<printList->next->chStr<<")";
					printList=printList->next;
					count++;
					word=output.str();
				}
				if(printList->next==NULL){
					output<<"-->("<<printList->chStr<<","<<printList->prob<<" ,null)";
				}
			
			}
			output<<"\n";
			word=output.str();
			count=0;
		
			return word;
		}
		
};



class HuffmanBinaryTree {
	public:
		HuffmanLinkedList *a= new HuffmanLinkedList();

 		listBinTreeNode *root;
 
 		listBinTreeNode *printN= new listBinTreeNode();
		
		HuffmanBinaryTree(listBinTreeNode *listHead,ofstream &outFile1,ofstream &outFile5){
			listBinTreeNode *oldListHead= new listBinTreeNode();
			
			oldListHead->next=listHead->next;
			
			listBinTreeNode *newNode = new listBinTreeNode();
		
		
	  		while(oldListHead->next->next!=NULL){

				a->listHead=oldListHead;
				newNode= new listBinTreeNode();

				newNode->prob=oldListHead->next->prob+oldListHead->next->next->prob;
				newNode->chStr= oldListHead->next->chStr+oldListHead->next->next->chStr;
				
				newNode->left=oldListHead->next;
				newNode->right=oldListHead->next->next;
				
				
				oldListHead->next=oldListHead->next->next->next;

				
				listBinTreeNode *spot=a->findSpot(newNode->prob);
				a->listInsert(spot, newNode);
				
				printN->printNode(newNode,outFile5);
				outFile5<<a->printList()<<endl;

			}
			root=newNode;
			

		}
	 	void CharCode(listBinTreeNode *node, string code,ofstream &outFile1){
			
			if(node==NULL){
				cout<<"this is empty tree"<<endl;

			}
			else if (isLeaf(node)){
				outFile1<<node->chStr;
				node->code=code;
				outFile1<<" code is :"<<node->code<<endl;
			}
			else{
				CharCode(node->left,code+"0",outFile1);
				CharCode(node->right,code+"1",outFile1);
		
			}
		}
		
		void preOrderTraveral(listBinTreeNode *newRoot,ofstream &outFile2){
			if(newRoot==NULL){	
			}
			else{
			
				outFile2<<newRoot->chStr<<" "<<newRoot->prob<<endl;
				preOrderTraveral(newRoot->left,outFile2);	
				preOrderTraveral(newRoot->right,outFile2);
			}
		}
		void inOrderTraveral(listBinTreeNode *newRoot,ofstream &outFile3){
			if(newRoot==NULL){
			}
			else{
				inOrderTraveral(newRoot->left,outFile3);
				outFile3<<newRoot->chStr<<" "<<newRoot->prob<<endl;	
				inOrderTraveral(newRoot->right,outFile3);
			}
		}
		
		void postOrderTraveral(listBinTreeNode *newRoot,ofstream &outFile4){
			if(newRoot==NULL){
			}
			else{
				postOrderTraveral(newRoot->left,outFile4);	
				postOrderTraveral(newRoot->right,outFile4);
				outFile4<<newRoot->chStr<<" "<<newRoot->prob<<endl;
			}
		}
		bool isLeaf(listBinTreeNode *node){
			if(node->left==NULL&&node->right==NULL){
				return true;
			}
			return false;
		}
};



int main(int argc, char **argv){
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile1;
	ofstream outFile2;
	ofstream outFile3;
	ofstream outFile4;
	ofstream outFile5;
	
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	outFile3.open(argv[4]);
	outFile4.open(argv[5]);
	outFile5.open(argv[6]);
	
	HuffmanLinkedList link;

	string word;
	int prob;
	
	if(!inFile.is_open()){
	 	cout<<"file not find";
	 }
	 
	while(inFile>>word){
	 	
	
		listBinTreeNode *spot;
	 	inFile>>prob;
	 	listBinTreeNode *newNode= new listBinTreeNode(word,prob);
	 	
		spot=link.findSpot(prob);
	 	link.listInsert(spot,newNode);
	 	
	 	outFile5<<link.printList();
	 	
	}	
	 listBinTreeNode *root;
	 HuffmanBinaryTree *tree= new HuffmanBinaryTree(link.listHead,outFile1,outFile5);

	 root=tree->root;

	 tree->CharCode(root,"",outFile1);
	 tree->preOrderTraveral(root,outFile2);
	 tree->inOrderTraveral(root,outFile3);
	 tree->postOrderTraveral(root,outFile4);
	 
	
	 
	 inFile.close(); 
	 outFile1.close();
	 outFile2.close();
	 outFile3.close();
	 outFile4.close();
	 outFile5.close();
	 return 0;
}

