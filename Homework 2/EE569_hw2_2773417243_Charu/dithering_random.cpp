#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include<vector>
#include<cmath>
#include <stdlib.h> 
#include <typeinfo>
#include <time.h>
using namespace std;




int randomNumGen(int lower, int upper){
    int a = (rand() % (upper - lower + 1)) + lower;
    return (a); 
}

void load_image(string filename)
{	// Define file pointer and variables
	FILE *file;
//	int BytesPerPixel=3;
	int X = 500;
    int Y = 750;


	
	// Allocate image data array
	unsigned char Imagedata[X][Y];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen("images/LightHouse.raw","rb"))) {
	//	cout << "Cannot open file: " << filename <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), X*Y, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen("trialimage.raw","wb"))) {
		
		exit(1);
	}


	fwrite(Imagedata, sizeof(unsigned char), X*Y, file);
	fclose(file);
    unsigned char solutionImage[500][750];

     for(int i=0; i< 500; i++){
         for(int j=0; j < 750; j++){
             //cout << 1*(Imagedata[i][j][0]) << "\n";
           //  int a = 128;
           int a = randomNumGen(0,255);
          // cout << "EEEEEEEEEEEEEEE:::::" << a;
           if (Imagedata[i][j] <a){
               Imagedata[i][j]=0;
           }
           else {
               Imagedata[i][j]=255;
           }
          //  a = ((0.2989*(Imagedata[i][j][0]))+(0.5870*(Imagedata[i][j][1]))+ (0.1140*(Imagedata[i][j][2])));
            // cout <<  typeid(a).name() <<  "\n";
            solutionImage[i][j] = Imagedata[i][j];
         
         }
     }

      if (!(file=fopen("random.raw","wb"))) {
		
		exit(1);
	}

	fwrite(solutionImage, sizeof(unsigned char), X*Y, file);
	fclose(file);
     
    
   
}

    int main()
{
    printf("hello world");
    srand(time(0));
    string filename = "images/LightHouse.raw";
     load_image(filename);
    return 0;
}
