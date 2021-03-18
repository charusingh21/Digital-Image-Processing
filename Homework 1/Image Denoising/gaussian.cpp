#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include<vector>
#include<cmath>

using namespace std;
//r-0 g-1/-1 b-2
//void 

   float getNormalisation(vector<vector<double>>& mask){                   // get normaization factor for each gaussian filter
       float sum=0.0;
       for( int i=0;i<5;i++){
           for (int j=0;j<5;j++)
           {
               sum=sum+mask[i][j];

           }
       }
       return 1/sum;
   }

float maskedElement(unsigned char bufferImage[][320], vector<vector<double>>& maskMatrix, int i,int j,float a)  //get convolution result
{
    float sum=0.0;
    for(int k=0;k<5;k++)
    {
        for(int l=0;l<5;l++)
        {
         sum=sum+(bufferImage[k+i-2][l+j-2]*maskMatrix[k][l]*a);
        }
    }
    return sum;
}
long double calculatepsnr(unsigned char solutionImage[][320],unsigned char bufferImage[][320])  // psnr 
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

vector<vector<double>>  getMaskedMatrix(unsigned char bufferImage[][320],int i,int j){   //get gaussian kernel
    float sigma = 0.83;
    float W,A;
    vector<vector<double>> maskMatrix(5,vector<double>(5));
     for(int k=i-2 ; k< i+3; k++){
            for(int l = j-2; l< j+3 ; l++){
                W = exp(-(pow((k-i),2) + pow((l-j), 2))/(2*sigma*sigma));
                A = (sqrt(2)*sqrt(M_PI)*sigma);
               maskMatrix[k-i+2][l-j+2] = W/A;  
            }
     }
     return maskMatrix;
}

void load_image(string filename)
{
    int dimX =320;
    int dimY = 320;

    unsigned char bufferImage[320][320];
    FILE * pFile;
    pFile = fopen("images/Corn_noisy.raw","r");
    fread(&bufferImage[0][0], dimX,dimY , pFile);
    unsigned char solutionImage[320][320];
    vector<vector<double>>  maskMatrix;
    float maskedResult;
   
   for(int i=2;i<320-2;i++)
    {
        for(int j=2;j<320-2;j++)
        {
          maskMatrix = getMaskedMatrix(bufferImage, i, j);
          float a= getNormalisation(maskMatrix);
          maskedResult = maskedElement(bufferImage, maskMatrix,i,j,a);
         // cout<<maskedResult;
           solutionImage[i][j]=maskedResult;     // final output image after gaussian filtering
         }

    }

     float psnr = calculatepsnr(solutionImage,bufferImage);
     cout<<psnr<<"==========";

    FILE * pFile2;
    FILE * pFile3;
   pFile2 = fopen("newImageFil_org.raw","wb");
    fwrite(&bufferImage[0][0], dimX, dimY, pFile2);
     pFile3 = fopen("GaussianFilenoise_2.raw","wb");
     fwrite(&solutionImage, dimX, dimY, pFile3);
     fclose(pFile2);
}

int main()
{
    printf("hello world");
    string filename = "images/Corn_noisy.raw";
    
     load_image(filename);
    return 0;
}