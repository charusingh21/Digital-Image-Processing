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
fwrite(bufferImage, sizeof(unsigned char), X*Y*BytesPerPixel, file);
	fclose(file);
    unsigned char desolutionImage[512][512][3];
     for(int i=0;i<512;i++) {
         for(int j=0;j<512;j++) {
             for(int k=0;k<3;k++){
                 cout << "1111111111111";
                 float r= sqrt((i*i)+(j*j));
                 float theta =