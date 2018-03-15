#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>


using namespace std;


class ListNode{
	public:
		string data;
		ListNode *next;
	
		ListNode(){
			data="dummy";
			next=NULL;
		}
		
		ListNode(string a){
			data=a;
			next=NULL;
		}
	
};

class LinkedList{
	public:
		ListNode *ListHead;
		ListNode *walker;
		int count=0;
		int size=0;
		
		LinkedList(){
			ListHead= new ListNode();
		}
		
		bool isEmpty(){
			return(size==0);
		}
		
		void listInsert(string b){
		
			ListNode *newNode= new ListNode(b);
			walker=ListHead;
			
			while(walker->next!=NULL&&walker->next->data.compare(b)<0){
				walker=walker->next;
			}
			if(walker->next==NULL){
				walker->next= newNode;
				newNode->next=NULL;
				size++;
			}
			else{
				newNode->next=walker->next;
				walker->next=newNode;
				size++;
			}
		}
		
		void printList (const char *argv){
			
			ofstream outFile;
			outFile.open(argv,ios::app);
			ListNode *printlist=ListHead;
			
			
			outFile<<"listHead-->";
			if(printlist->next==NULL){
				outFile<<"("<<printlist->data<<",NULL)"<<endl;
			}
			else{
			
				while(printlist->next!=NULL&& count<=15){
				
					outFile<<"("<<printlist->data<<","<<printlist->next->data<<")-->";
					printlist=printlist->next;
					count++;	
				}
				if(printlist->next==NULL){
					outFile<<"("<<printlist->data<<",NULL)";
				}
				outFile<<endl;
				count=0;
			}
			outFile.close();
		}
};

int main(int argc, char **argv){

	 ifstream inFile;
	 inFile.open(argv[1]);
	 LinkedList link;
	 string word;
	 
	 if(!inFile.is_open()){
	 	cout<<"file not find";
	 }
	 
	 while(!inFile.eof()){
	 	
		link.printList(argv[2]);
	 	inFile>>word;
	 	link.listInsert(word);
	 }	

	 inFile.close();
	 return 0;
}

