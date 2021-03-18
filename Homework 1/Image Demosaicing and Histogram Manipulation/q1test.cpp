#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include<vector>

using namespace std;
//r-0 g-1/-1 b-2
//void 
int color_decider(int i, int j)
{
    if(i%2!=0 && j%2!=0)
    {
        return -1;
    }
    else if(i%2==0 && j%2==0)
    {
        return 1;
    }
    else if(i%2!=0 && j%2==0)
    {
       return 2;
    //  return 0; //mod
    }
    else if(i%2==0 && j%2!=0)
    {
       return 0;
      // return 2; //
    }

}

vector<float> calculate_g(float a, float b, float c, float d)
{
   vector<float> ret(2);//array of size two
   ret[0]=(a+b)/(float)2;
   ret[1]=(c+d)/(float)2;
   return ret;
}

vector<float> calculate_r_b(float a, float b, float c, float d, float a1, float b1, float c1, float d1)
{
   vector<float> ret(2);
   ret[0]=(a+b+c+d)/(float)4;
   ret[1]=(a1+b1+c1+d1)/(float)4;
   return ret;
}

void load_image(string filename)
{
    int dimX =532;
    int dimY = 600;

    unsigned char initialMatrix[532][600];
    FILE * pFile;
    pFile = fopen("images/Dog.raw","r");
    fread(&initialMatrix[0][0], dimX,dimY , pFile);
    unsigned char solutionImage[532][600][3];
     unsigned char bufferImage[534][602];
    memset(bufferImage,0,sizeof(bufferImage));
// padding is done for border correction
    for(int i=0; i< 531; i++)
    {
        bufferImage[i+1][0] = initialMatrix[i][0];
        bufferImage[i+1][601] = initialMatrix[i][599];
    }

    for(int i=0; i< 531; i++){
       for(int j=0; j< 600 ; j++){
           bufferImage[i+1][j+1] = initialMatrix[i][j];
        }
   }

    for(int j=0; j<602; j++){
        //int i=0;
        bufferImage[531][j] = bufferImage[530][j];
          bufferImage[0][j] = bufferImage[1][j];
       
    }
    


   for(int i=1;i<532-1;i++)
    {
        for(int j=1;j<600-1;j++)
        {
            int color = color_decider(i,j);
            //r-0 g-1 b-2
            if(color==-1)
            {
                solutionImage[i][j][1]=bufferImage[i][j];
                vector<float> ret = calculate_g(bufferImage[i][j+1], bufferImage[i][j-1], bufferImage[i+1][j], bufferImage[i-1][j]);
            
                 solutionImage[i][j][0]=ret[1];
                 solutionImage[i][j][2]=ret[0];
            }
            else if(color==0)
            {
                solutionImage[i][j][0]=bufferImage[i][j];
                vector<float> ret = calculate_r_b(bufferImage[i][j+1], bufferImage[i][j-1], bufferImage[i+1][j], bufferImage[i-1][j], bufferImage[i+1][j+1], bufferImage[i+1][j-1], bufferImage[i-1][j-1], bufferImage[i-1][j+1]);
                solutionImage[i][j][1]=ret[0];
                solutionImage[i][j][2]=ret[1];
            }
            else if(color==1)
            {
                solutionImage[i][j][1]=bufferImage[i][j];
                vector<float> ret = calculate_g(bufferImage[i][j+1], bufferImage[i][j-1], bufferImage[i+1][j], bufferImage[i-1][j]);
                solutionImage[i][j][2]=ret[1];
                solutionImage[i][j][0]=ret[0];   
            }
            else if(color==2)
            {
                solutionImage[i][j][2]=bufferImage[i][j];
                vector<float> ret = calculate_r_b(bufferImage[i][j+1], bufferImage[i][j-1], bufferImage[i+1][j], bufferImage[i-1][j], bufferImage[i+1][j+1], bufferImage[i+1][j-1], bufferImage[i-1][j-1], bufferImage[i-1][j+1]);
                solutionImage[i][j][1]=ret[0];
                solutionImage[i][j][0]=ret[1];
            }
        }
    }

    FILE * pFile2;
     pFile2 = fopen("DogFile_2.raw","wb");
    fwrite(solutionImage, sizeof(unsigned char), sizeof(solutionImage), pFile2);
     fclose(pFile2);
}

int main()
{
    string filename = "images/Dog.raw";
     load_image(filename);
    return 0;
}