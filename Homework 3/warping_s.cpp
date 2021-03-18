#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include<vector>
#include<cmath>

using namespace std;



void load_image(string filename)
{
   FILE *file;
	int BytesPerPixel=3;
	int X = 512;
    int Y = 512;


	
	// Allocate image data array
	unsigned char bufferImage[X][Y][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen("images/raccoon.raw","rb"))) {
	//	cout << "Cannot open file: " << filename <<endl;
		exit(1);
	}
	fread(bufferImage, sizeof(unsigned char), X*Y*BytesPerPixel, file);
	fclose(file);
    if (!(file=fopen("trialimage.raw","wb"))) {
		
		exit(1);
	}

    int pixelR;
	fwrite(bufferImage, sizeof(unsigned char), X*Y*BytesPerPixel, file);
	fclose(file);
    unsigned char desolutionImage[512][512][3];
     for(unsigned int i=0;i<512;i++) {
         for(int j=0;j<512;j++) {
             for(int k=0;k<3;k++){
               //  cout << "1111111111111";
                 
                  float xk=1+j-0.5;
                  float yk= Y+0.5-i;
                  float xk_norm= (xk-255.5)/255.5;
                  float yk_norm= (yk-255.5)/255.5;
                  float p_norm = (xk_norm/(sqrt(1- (pow(yk_norm,2)/2))))*255.5;
                  float q_norm = (yk_norm/(sqrt(1- (pow(yk_norm,2)/2))))*255.5;
                  float p= (p_norm+255.5);
                  float q=(q_norm+255.5);
                  float r=Y +0.5-q;
                  float c= p+ 0.5-1;
                  int m =floor(r);
                  int n=floor(c);
                 if(m<0||n<0){
                     desolutionImage[i][j][k]=0;

                  }
                  else if (m>511 ||n>511){
                    desolutionImage[i][j][k]=0;
                  }
                   else{
                   //
                   // int pixelR= (bufferImage[m][n][k]+bufferImage[m][n+1][k]+bufferImage[m+1][n][k]+bufferImage[m][n-1][k]+bufferImage[m][n][0)
                  //  pixelR = bufferImage[m][n][k];
                  pixelR= (bufferImage[m][n][k]+bufferImage[m][n+1][k]+bufferImage[m+1][n+1][k]+bufferImage[m][n-1][k]+bufferImage[m+1][n][k])/4;

                  //  pixelR = bufferImage[m][n][k];
                   }

              
                 
                  desolutionImage[i][j][k]= pixelR;
                  }
                  }
              }
         
     
    if (!(file=fopen("unwarped_raccoon.raw","wb"))) {
		
		exit(1);
	}


	fwrite(desolutionImage, sizeof(unsigned char), X*Y*BytesPerPixel, file);


         }

    int main()
    {
      string filename="images/raccoon.raw";
        load_image(filename);
        return 0;
    }
