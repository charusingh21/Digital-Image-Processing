#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include<vector>
#include<cmath>
using namespace std;


int color_decider(int i, int j)

{
    if((i%2!=0 && j%2!=0) ||(i%2==0 && j%2==0))
    {
      return -1;
    }   
    else if((i%2!=0 && j%2==0))
    {
      return 2;
    }
     else if((i%2==0 && j%2!=0))
    {
      return 0;
    }

}
void load_image(string filename)
{	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int X = 400;
    int Y = 560;
	

	
	// Check if image is grayscale or color

	
	// Allocate image data array
	unsigned char Imagedata[X][Y][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen("images/Toy.raw","rb"))) {
	//	cout << "Cannot open file: " << filename <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), X*Y*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen("trialimage.raw","wb"))) {
		
		exit(1);
	}

	fwrite(Imagedata, sizeof(unsigned char), X*Y*BytesPerPixel, file);
	fclose(file);

    int dimX =400;
    int dimY = 560;
    int r=0;
    int g=0;
    int b=0;

    unsigned char bufferImage[400*560];
    
    float array_r[256] = {};
    float array_g[256] = {};
    float array_b[256] = {}; 

    for(int i=0; i< 400; i++){
        for (int j=0; j< 560; j++){
            for(int k=0; k< 3; k++){
                if(k==0){
                    array_r[Imagedata[i][j][k]]++;
                } else if (k==1){
                    array_g[Imagedata[i][j][k]]++;
                } else {
                    array_b[Imagedata[i][j][k]]++;
                }
            }
        }
    }

    for(int i =0; i< 256; i++){
        cout << array_r[i] << "====";
    }
    cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";



    FILE * pFile;
    pFile = fopen("images/Toy.raw","r");
    cout<<"\n"<<"R::"<<r<<" G::"<<g<<" B::"<<b;

    ofstream outputFile;
    outputFile.open("outnew.csv");
     for(int i=0;i<256;i++)
    {
    outputFile<< array_r[i]<<"," << array_g[i] << "," <<array_b[i]   << "\n" ;

         
    }
    
  //  outputFile << r << ","<< g<< "," <<b;
    outputFile.close();


    FILE * pFile2;
  
}











int main()
{
    printf("hello world");
    string filename = "images/Toy.raw";
     load_image(filename);
    return 0;
}
