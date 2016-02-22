#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;


//Create a new file type [.in] that will be a binary file type This should create a file that can be 
//read in by tsp.cpp to solve the traveling salesman problem. 

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

TSPHeader theHeader;
TSPDistances *distances;

class TSPFileCreator{
      
     int linesToRead; 
     public:
     TSPFileCreator();
     void readInDistances();
     void writeToTSP();       
      };

int main(){   
    TSPFileCreator creator;
    system("pause");
    return 0;
    }
    
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TSPFileCreator::TSPFileCreator(){
     readInDistances();
     writeToTSP();
};

void TSPFileCreator::readInDistances(){
     linesToRead = 90;
     string file = "city.txt";
     ifstream tspFile(file.c_str());
     char* temp;
     temp = new char[22];
     
     //Set up the header
     tspFile.getline(temp, 22, ',' );
     theHeader.numCities = atoi(temp);
     tspFile.getline(temp, 22, ',');
     strcpy(theHeader.startingCity, temp);
     tspFile.getline(temp, 22);
     strcpy(theHeader.endingCity, temp);
     
     cout << theHeader.numCities << " /  " << theHeader.startingCity << " / " << theHeader.endingCity <<endl;
     
     //Set up the direction structs
     distances = new TSPDistances [linesToRead];
     
     for ( int i = 0; i<linesToRead ; i++){
         tspFile.getline(temp, 22, ',');
         strcpy(distances[i].cityA, temp);
         tspFile.getline(temp, 22, ',');
         strcpy(distances[i].cityB, temp);
         tspFile.getline(temp, 22);
         distances[i].distance = atoi(temp);
         cout << i << " : " << distances[i].cityA << " / " <<distances[i].cityB << " / " << distances[i].distance <<endl;
         }  
};

void TSPFileCreator::writeToTSP(){
     ofstream INFile;
     INFile.open("tsp.in" , ios::binary);
     
     INFile.write( reinterpret_cast<char*>(&theHeader), sizeof(TSPHeader));
     
     for( int i = 0; i<linesToRead; i++)
     {
     INFile.write( reinterpret_cast<char*>(&distances[i]), sizeof(TSPDistances));
     }
     
     
     
     INFile.close();
     }


