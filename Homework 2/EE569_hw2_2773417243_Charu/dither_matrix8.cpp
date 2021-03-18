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


void load_image(string filename)
{	// Define file pointer and variables
	FILE *file;
//	int BytesPerPixel=3;
	int X = 500;
    int Y = 750;


	
	// Allocate image data array
	unsigned char Imagedata[X][Y];
    	unsigned char Image[X][Y];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen("images/LightHouse.raw","rb"))) {
	//	cout << "Cannot open file: " << filename <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), X*Y, file);
	fclose(file);
    	if (!(file=fopen("images/LightHouse.raw","rb"))) {
	//	cout << "Cannot open file: " << filename <<endl;
		exit(1);
	}
	
	fread(Image, sizeof(unsigned char), X*Y, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen("trialimage.raw","wb"))) {
		
		exit(1);
	}


	fwrite(Imagedata, sizeof(unsigned char), X*Y, file);
	fclose(file);
    unsigned char solutionImage[500][750];
    int N=8;
    float threshold[N][N];
    //Reading 8*8 matrix
    float index[8][8] = {};
    ifstream file1;
    file1.open("8_8matrix.txt");
    for(int i=0; i< 8; i++){
        for(int j=0; j< 8; j++){
            file1 >> index[i][j];
        }
    }


    file1.close();
    for (int i=0; i<N;i++){
        for (int j=0; j<N;j++){
            threshold[i][j]=((index[i][j]+0.5)/( N*N))*255;
            cout << 1*(threshold[i][j])<< "\n";
        }
    }
    
     for(int i=0; i< 500; i++){
         for(int j=0; j < 750; j++){
             if(Imagedata[i][j]< threshold[i%N][j%N]){
               Imagedata[i][j]=0;
             }
             else{
                  Imagedata[i][j]=255;

             }
         
             solutionImage[i][j] = Imagedata[i][j];
         }
     }
      double r=0;
     double mse,psnr;
//calculate MSE
for(int i=0;i<500;i++){
    for(int j=0;j<=750;j++){
       // cout << pow((solutionImage[i][j]-bufferImage[i][j]),2)<<"????????";
        r=r+pow((solutionImage[i][j]-Image[i][j]),2);       
    }
}
 mse=sqrt((r/(500*750)));

// double mse = calculatepsnr(solutionImage,Image);
     cout<<mse<<"==========";

    //  for(int i=0; i< 500; i++){
    //      for(int j=0; j < 750; j++){
    //          solutionImage[i][j] = solutionImage[i][j] + threshold[0][0];
    //          solutionImage[i][j+1] =  solutionImage[i][j+1] + threshold[0][1];
    //          solutionImage[i+1][j] = solutionImage[i+1][j] + threshold[1][0];
    //          solutionImage[i+1][j+1] = solutionImage[i+1][j+1] + threshold[1][1];
    //          j = j+2;
    //      }
    //     i=i+2;
    //  }

    /* for(int i=0; i< 500; i++){
         for(int j=0; j < 750; j++){
             
         }
     }*/

      if (!(file=fopen("dither_8.raw","wb"))) {
		
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
