#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<sstream>

using namespace std;

int charCount[256];
string printAry();

int main(int argc, char **argv){
	 ifstream inFile;
	 ofstream outFile;
	 inFile.open(argv[1]);
	 outFile.open(argv[2]);
	 char charIn;
	 int index;
	 string outPutString;
	 
	 if(!inFile.is_open()){
	 	cout<<"file not find";
	 }
	 
	 while(inFile>>charIn){

	 	index=(int) charIn;
	 	
	 	if(index>256||index<0){
	 		inFile>>charIn;
	 	}
	 	index=(int) charIn;
	 	charCount[index]=charCount[index]+1;
	 	if(index==9||index==10||index==13||index==32){
	 		charCount[index]=0;
	 	}
	 }	
	 inFile.close();
	 outPutString=printAry();
	 outFile<<outPutString;
	 
	 outFile.close();

return 0;
}

string printAry(){
	int index=0;
	stringstream output;
	string output2;
	char symbol;
	while(index<256){
		if(charCount[index]>0){
			symbol=(char)index;
			output<<symbol<<" :"<<charCount[index]<<"\n";
			output2=output.str();	
		}
		index++;
	}
	return output2;
}
