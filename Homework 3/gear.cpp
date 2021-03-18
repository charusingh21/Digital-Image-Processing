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
    cout << "=====================";
	FILE *file;
//	int BytesPerPixel=3;
	int X = 250;
    int Y = 250;


	
	// Allocate image data array
	unsigned char Imagedata[X][Y];
    unsigned char Image[X][Y];
     unsigned char Imagedata_normalized[X][Y];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen("images/gearoutputshrink.raw","rb"))) {
        cout << "ooopsie!!!!";
	//	cout << "Cannot open file: " << filename <<endl;
		exit(1);
	}
    cout << "++++++++++++++";
	fread(Imagedata, sizeof(unsigned char), X*Y, file);
	
     if (!(file=fopen("gearshrink.raw","wb"))) {
		cout << "ooopsie!!!!";
		exit(1);
	}
    

	fwrite(Imagedata, sizeof(unsigned char), X*Y, file);
	fclose(file);
      for (int i = 1; i < 249; i++)
    {
        for (int j = 1; j < 249; j++)
        {
            if (Imagedata[i][j] > 127)
            {
                Imagedata_normalized[i][j] = 1;
            }
            else
            {
                Imagedata_normalized[i][j] = 0;
            }
        }
    }
   // int  count=0;
     for (int i = 1; i < 249; i++)
    {
        for (int j = 1; j < 249; j++)
        {
            if (  Imagedata_normalized[i][j]==1){
                 if ( Imagedata_normalized[i-1][j]==1 &&   Imagedata_normalized[i][j-1]==1  &&  Imagedata_normalized[i][j+1]==1 &&  Imagedata_normalized[i+1][j]==1){
               cout<<i<<j<<endl;
            }
        }
       //  cout<<i<<j<<endl;
    }
    }

     for(int i=1; i<250;i++){
         for(int j=1; j<250;j++){
             Image[i][j]= 255-Imagedata[i][j];
         }
      }
   if (!(file=fopen("inverted_gear.raw","wb"))) {
		
		exit(1);
	}


	fwrite(Image, sizeof(unsigned char), X*Y, file);
   

   










    //  for(int i=0; i<239;i++){
    //      for(int j=0; j<372;j++){
    //          Image[i][j]= 255-Imagedata[i][j];
    //      }
    // //  }
    //  FILE * pFile2;
    //  cout << "ooooooooooooooooooo";
    //  pFile2 = fopen("inverted_PCB.raw","wb");
    //  fwrite(Image, sizeof(unsigned char), sizeof(Image), pFile2);
    //  fclose(pFile2);
      FILE * pFile2;
     cout << "ooooooooooooooooooo";
     pFile2 = fopen("gears.raw","wb");
     fwrite(Image, sizeof(unsigned char), sizeof(Image), pFile2);
     fclose(pFile2);
}


  int main()
{
    printf("hello world");
   
    string filename = "images/PCB.raw";
     load_image(filename);
    return 0;
}