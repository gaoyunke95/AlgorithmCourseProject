#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;
class point{
public:
    int x;
    int y;
    int label;
    double distance ;
    void PrintPoint(point p){
        cout<<p.x<<" "<<p.y<<" "<<p.label<<" "<<p.distance<<endl;
	}
};

class Kmean{
	public:
    	int k;
    	struct xyCoord{
    	    int xcoor;
        	int ycoor;
        	int label;
        	int count;
        	int sumx;
        	int sumy;
   		 };
   		int *arrayX=new int [k];
        int *arrayY=new int [k];
        int *CountAry=new int [k]; 
   		xyCoord *Kcentroid;
    	point *pointSet;
    	int **imageArray;
    	int changeLabel;
    	
		Kmean(int a, int b, int c, int d){
        	Kcentroid= new xyCoord[a];
        	pointSet= new point[b];
        	imageArray= new int *[c];
        	for(int i=0;i<c;i++){
            	imageArray[i]= new int[d];
            
        	}
        	for(int i=0;i<c; i++){
            	for(int j=0;j<d;j++){
                	imageArray[i][j]=0;
            	} 
        	}

    	}
    
		void loadPointSet(int x, int y,int i){
        	pointSet[i].x=x;
        	pointSet[i].y=y;
    	}
    	
		void assignLabel(int k,int numpts){
        	for(int i=0;i<numpts;i++){
				pointSet[i].label=i%k+1;

        	}
    	}
    
    	void mapPoint2Image(int numpts){
        	for(int i=0;i<numpts;i++){
           	 imageArray[pointSet[i].x][pointSet[i].y]=pointSet[i].label;
        	}
    	}
    
   	 	void prettyPrint(int numrow, int numcol,ofstream &outFile2){
        	for(int i=0;i<numrow; i++){
            	for(int j=0;j<numcol;j++){
                	if(imageArray[i][j]>0){
                   	 	outFile2<<imageArray[i][j];
                	}
                	else{
                    	outFile2<<" ";
                	}
            	}
            	outFile2<<endl;
        	}
        
    	}
    
    	void KmeanClustering(int k,int numpts){
        	changeLabel=0;
   

        	for(int j=0;j<numpts;j++){
                
				int index=pointSet[j].label-1;
                
				arrayX[index]+=pointSet[j].x;
                arrayY[index]+=pointSet[j].y;
                CountAry[index]++;          	
        	}
        	
        	for(int i=0; i<k; i++){
				int label=i+1;
        		Kcentroid[i].xcoor=arrayX[i]/CountAry[i];
        		Kcentroid[i].ycoor=arrayY[i]/CountAry[i];
        		
				Kcentroid[i].label=label;

        	
        		if(i==0){
            		Kcentroid[i].xcoor=Kcentroid[i].xcoor+1;
            		Kcentroid[i].ycoor=Kcentroid[i].ycoor-1;
           		}
				
				arrayX[i]=0;        	
				arrayY[i]=0;
        		CountAry[i]=0;
        	}
        	

        	
        	
        	for(int index=0;index<numpts;index++){
            
            	int labelofShortestC=shortestCtoP(k,index);
            	if(labelofShortestC!=pointSet[index].label){
                	pointSet[index].label=labelofShortestC;
                	changeLabel++;
            	}

        	}
    	}
    
    	double calcDistance(int x1, int y1, int x2, int y2){
       		double distance;
       		distance =sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        
			return distance;
			
    	}
    

    	int shortestCtoP(int k, int j){
        	int minlabel=0;
        	double shortestd=999;
        	for(int i=0; i<k;i++){
    
            	pointSet[j].distance=calcDistance(Kcentroid[i].xcoor, Kcentroid[i].ycoor, pointSet[j].x, pointSet[j].y);
            	if(pointSet[j].distance<shortestd){
            		shortestd=pointSet[j].distance;
               		minlabel=Kcentroid[i].label;

            	}

        	}
        	return minlabel;
    	}
    
    

};

int main(int argc,const char *argv[]){
    ifstream inFile;
    ofstream outFile1;
    ofstream outFile2;
    
    inFile.open(argv[1]);
	outFile1.open(argv[2]);
	outFile2.open(argv[3]);
	
	int iteration=0;
    if(!inFile.is_open()){
        cout<<"no file find";
    }
    
	int k;
    int numpts;
    int numrow;
    int numcol;
    
    inFile>>k;
    inFile>>numpts;
    inFile>>numrow;
    inFile>>numcol;
	
    
    Kmean *a= new Kmean(k,numpts,numrow,numcol);

    int x;
    int y;
    int i=0;
    //step1
    while(!inFile.eof()){
        inFile>>x>>y;
        a->loadPointSet(x, y, i);
        i++;
    }
    //step2
    a->assignLabel(k, numpts);
     

    
    do{
        //step3
        a->mapPoint2Image( numpts);
        
        outFile2<<"iteration: "<<iteration<<endl;
		//step4
        a->prettyPrint(numrow, numcol,outFile2);

        //step5,6,7
        a->KmeanClustering(k, numpts);
        
        iteration++;
    }while(a->changeLabel>0);
    
	outFile1<<k<<"\n"<<numpts<<"\n" <<numrow<<" "<<numcol<<endl;
	
	for(int i=0;i<numpts;i++){
		outFile1<<a->pointSet[i].x<<" "<<a->pointSet[i].y<<" "<<a->pointSet[i].label<<endl;
	}
	
	inFile.close();
	outFile1.close();
	outFile2.close();
    return 0;
}
