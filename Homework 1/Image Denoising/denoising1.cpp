#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include<vector>
#include<cmath>

using namespace std;

   float getNormalisation(float mask[][3]){                   // get the normalized value
       float sum=0.0;
       for( int i=0;i<3;i++){
           for (int j=0;j<3;j++)
           {
               sum=sum+mask[i][j];

           }
       }
       return 1/sum;
   }

float maskedElement(unsigned char bufferImage[][320],int i,int j,float a)     //get the Kernel matrix after element multiplication and summation
{
    float sum=0.0;
    for(int k=i;k<3+i;k++)
    {
        for(int l=j;l<3+j;l++)
        {
         sum=sum+bufferImage[k][l]* a;
        }
    }
    return sum;                                           // get new pixel values in output image
}
long double calculatepsnr(unsigned char solutionImage[][320],unsigned char bufferImage[][320])  // calculate psnr
{
    long double r=0;
    long double mse,psnr;
//calculate MSE
for(int i=0;i<318;i++){
    for(int j=0;j<=318;j++){
       // cout << pow((solutionImage[i][j]-bufferImage[i][j]),2)<<"????????";
        r=r+pow((solutionImage[i][j]-bufferImage[i][j]),2);       
    }
}
mse=(r/(320*320));
psnr=10*log10((255*255)/mse);
return psnr;
}

void load_image(string filename)  
{
    int dimX =320;
    int dimY = 320;

    unsigned char bufferImage[320][320];
    FILE * pFile;
    pFile = fopen("images/Corn_noisy.raw","r");                    //open the raw fileof input image
    fread(&bufferImage[0][0], dimX,dimY , pFile);
    unsigned char solutionImage[320][320];
    float mask[3][3]={                                        //initialize Kernel matrix
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };
   float a= getNormalisation(mask);
   for(int i=0;i<320-2;i++)
    {
        for(int j=0;j<320-2;j++)
        {
          float maskedResult = maskedElement(bufferImage,i,j,a);
         // cout<<maskedResult;
           solutionImage[i][j]=maskedResult;                 // get output image after filtering

         }

    }

     float psnr = calculatepsnr(solutionImage,bufferImage);
     cout<<psnr<<"==========";

    FILE * pFile2;
    FILE * pFile3;
   pFile2 = fopen("images/Corn_noisy.raw","wb");
    fwrite(&bufferImage[0][0], dimX, dimY, pFile2);
     pFile3 = fopen("AverageFilenoise_2.raw","wb");
     fwrite(&solutionImage, dimX, dimY, pFile3);
     fclose(pFile2);
}


int main()
{
    string filename = "images/Corn_noisy.raw";
     load_image(filename);
    return 0;
}