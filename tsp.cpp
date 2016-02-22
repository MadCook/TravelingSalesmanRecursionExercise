#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

struct TSPHeader{
       int numCities;
       char startingCity[22];
       char endingCity[22];
       };
       
struct TSPDistances{
       char cityA[22];
       char cityB[22];
       int distance;
       };

void findNumInst();
int numOfInstructs;

TSPHeader theHeader;
TSPDistances *distances;
int **CityDistances;
string *CityNames;
int *path;
bool *used;
int *best;
int bestCost = 1000000000;
int  citiesFound;

	void arraySetUp();
	int cityExists(string City);
	void addACity(string City);	
	
	
	void permute(int i);
	void checkResult();
	void ReadInFile();
	void WriteOutFile();


int main(){
	findNumInst();
	ReadInFile();
    arraySetUp();
	permute(1);
	for (int i = 0; i < theHeader.numCities; i++)   // printing...
        cout << best[i] << ' ';
 		cout <<endl;
	WriteOutFile();
	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//Set up the information on routes
void arraySetUp(){

	  citiesFound =0;	
      CityNames = new string[theHeader.numCities];
      path = new int[theHeader.numCities];
      used = new bool[theHeader.numCities];
      best = new int[theHeader.numCities];
      
      //Initialize used cities to not used 
      for (int i = 0; i < theHeader.numCities; i++)   
        used[i] = false;
      
      
      //Initialize array
      CityDistances = new int*[theHeader.numCities];
      
    
      for(int i=0; i<theHeader.numCities; i++){
	  	CityDistances[i] = new int[theHeader.numCities];
	  }
	  
	  int numOfStructs = numOfInstructs;
	  
	  //Initialize the routes AB =BA = distance
	  for(int i=0; i<numOfStructs; i++){
	  	CityDistances[cityExists(distances[i].cityA)][cityExists(distances[i].cityB)] = CityDistances[cityExists(distances[i].cityB)][cityExists(distances[i].cityA)] = distances[i].distance; 
		}
		
	  //Set that each city to itself should not be a distance	
	  for(int i=0; i<theHeader.numCities; i++){
	    CityDistances[i][i] = 0;
	   }
	   
	   //Set up where your route is going to start and end
	   path[0] = cityExists(theHeader.startingCity);
	   path[theHeader.numCities-1] = cityExists(theHeader.endingCity);

	   
	   //Say that you use both the starting and ending city so you won't visit again
	   used[cityExists(theHeader.startingCity)] = true;
	   used[cityExists(theHeader.endingCity)] = true;
		
		
	  }

//Check to see if you already have this city and where	  
int cityExists(string City){
	
	//Find the city and return it's position in the array
	for(int i=0; i<citiesFound; i++){
	  if(CityNames[i]==City){
	  	return i;
	  }
	  }
	//If city wasn't found add it to the array
	  addACity(City);
	// Call function again to return where you just added the city to the array
	  return cityExists(City);
	}

//Adding a city to the array	
void addACity(string City){
	CityNames[citiesFound] = City;
	citiesFound++;
}

//Recursive function that will permute through all itterations of this traveling salesman problem
void permute(int i) {
    for (int k = 0; k < theHeader.numCities; k++) {
        if (used[k]==false) {
            path[i] = k;
            used[k] = true;
            if (i == theHeader.numCities-2){
               checkResult();
            }
            else{
                permute(i+1);
        	} 
            used[k] = false;
        
    }  
}

}

//Check if a complete path is cheaper than other known solutions. If so make it the best known solution
void checkResult() {

    int totalcost = 0;

    for (int i = 0; i <theHeader.numCities-1 ; i++) {
        totalcost += CityDistances[path[i]][path[i+1]];
    }
    
    if (bestCost > totalcost) {
        bestCost = totalcost;
        for (int i = 0; i < theHeader.numCities; i++)
            best[i] = path[i];
    }
}

//Read in the traveling salesman file. This should determine how many cities you are dealing with and read in the distance
//between cities into a general array.
void ReadInFile(){
	fstream tspFile;
	tspFile.open("tsp.in", ios::in | ios::binary);
	if (!tspFile){ 
     cout <<"cannot Open file" <<endl; 
    }
    tspFile.read((char*) &theHeader, sizeof(TSPHeader));
      cout <<"There are " << theHeader.numCities << " cities to travel to!" <<endl;
      int numOfStructs =numOfInstructs;
	distances = new TSPDistances[numOfStructs];
	for(int i=0; i<numOfStructs; i++){
	  tspFile.read((char*) (&distances[i]), sizeof(TSPDistances));
	}        
}


//Write out results for the traveling sales man problem into a new file
void WriteOutFile(){
		ofstream solutionFile;
	solutionFile.open("tsp.out", ios::binary |  ios::out );
	
	solutionFile.write( reinterpret_cast<char*>(&bestCost), sizeof(bestCost));
	solutionFile <<endl;
	for(int i=0; i<theHeader.numCities; i++){
	solutionFile << CityNames[best[i]] << endl;
	}
	
	solutionFile.close();
	
}

//Determine how many cities have distances between them
void findNumInst(){
  numOfInstructs = -1;
  ifstream tspFile("tsp.in", ios::binary | ios::in);
  string emptyString;

  while(true){
    getline(tspFile,emptyString);
    numOfInstructs++;
    if(tspFile.eof()) break;
    
  }
  tspFile.close();   
};


