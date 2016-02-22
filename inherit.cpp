#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

int *best;
double perfectAvg;

string *inheritanceItems;
double *inheritanceWorth;
double totalInheritance;
double leastDifference;
int numOfItems;
int *binary;

void readInItems();

void checkResult() {
	int sum =0;
    for (int i = 0; i < numOfItems; i++){
    	if(binary[i]==1)
    		sum += inheritanceWorth[i];
	}
	
	if(abs(perfectAvg -sum) < leastDifference){
		leastDifference = abs(perfectAvg-sum);
		for(int i=0; i<numOfItems; i++){
			best[i] = binary[i];

		}

	}

}
 
void generate(int i ) {
    for (int k = 0; k <= 1; k++) {
        binary[i] = k;
        if (i == numOfItems-1)
            checkResult();
        else
            generate(i+1);
    }
}

void printOutItems();


int main(){
	readInItems();
	generate(0);
	printOutItems();
	
	return 0;
}

void readInItems(){
	fstream inheritanceFile;
	inheritanceFile.open("item.txt");
		if (!inheritanceFile){ 
          cout <<"cannot Open file" <<endl; 
        }
    inheritanceFile >> numOfItems;
    cout << numOfItems <<endl;
    
    
    inheritanceItems = new string[numOfItems];
	inheritanceWorth = new double[numOfItems];
	best = new int[numOfItems];
    totalInheritance = 0;
    
    for(int i=0; i<numOfItems; i++){
    	inheritanceFile >> inheritanceItems[i];
    	inheritanceFile >> inheritanceWorth[i];
    	totalInheritance += inheritanceWorth[i];
 	}
 	leastDifference = totalInheritance;
 	perfectAvg = totalInheritance/2;
 	
 	binary = new int[numOfItems];
 	for(int i=0; i<numOfItems; i++)
 		binary[i] =0;
 	
 	inheritanceFile.close();
}




void printOutItems(){
	ofstream solutionFile;
	solutionFile.open("divide.txt");
	double person1Sum =0;
	
	for(int i=0; i<numOfItems; i++){
		if(best[i]==1){
			person1Sum += inheritanceWorth[i];
		}	
	}
 	solutionFile << person1Sum << "  " << totalInheritance-person1Sum << "  " << leastDifference << endl;
 	
 	
 	for(int i=0; i<numOfItems; i++){
 		if(best[i]==1)
 		solutionFile << inheritanceItems[i] << "  ";
	 }
 	  solutionFile << endl;
 	
	 for(int i=0; i<numOfItems; i++){
 		if(best[i]==0)
 		solutionFile << inheritanceItems[i] << "  ";
	 }
	
	solutionFile.close();
	
}
