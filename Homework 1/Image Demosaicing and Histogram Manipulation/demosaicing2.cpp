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

vector<float> calculate_g(float a, float b,float e, float c, float d,float f,float g,float h,float h1, float i,float j,float a1, float b1)
{
   vector<float> ret(2);//array of size two
   float deltaG;
    deltaG=(e-((c+d+f+g+h+h1+i+j)/6));
    ret[0]=((a+b)/2)+((5/8)*deltaG);
    ret[1]=((a1+b1)/2)+((5/8)*deltaG);

    if (ret[1]<0)
    {
        ret[1]=0;
    }
    else if (ret[1]>255)
    {
        ret[1]=255;
    }
       else if (ret[0]>255)
    {
        ret[0]=255;
    }
       else if (ret[0]<0)
    {
        ret[0]=0;
    }
   return ret;
}

vector<float> calculate_r_b(float a, float b, float c, float d,float e, float a2, float b2, float c2, float d2,float a1,float b1,float c1,float d1)
{
   vector<float> ret(2);
   float deltaR;
    deltaR=(e-((a1+b1+c1+d1)/4));
    ret[0]=((a+b+c+d)/4)+((0.5)*deltaR);//G AT R
    ret[1]=((a2+b2+c2+d2)/4)+((3/4)*deltaR);//B at R

    if (ret[1]<0)
    {
        ret[1]=0;
    }
    else if (ret[1]>255)
    {
        ret[1]=255;
    }
       else if (ret[0]>255)
    {
        ret[0]=255;
    }
       else if (ret[0]<0)
    {
        ret[0]=0;
    }
   return ret;
}
vector<float> calculate_atb(float a, float b, float c, float d,float e, float a2, float b2, float c2, float d2,float a1,float b1,float c1,float d1)
{
   vector<float> ret(2);
  //  float w=1/8;
   float deltaB;
 
    deltaB=(e-((a1+b1+c1+d1)/4));
    ret[0]=((a+b+c+d)/4)+((1/2)*deltaB);//G AT B
    ret[1]=((a2+b2+c2+d2)/4)+((3/4)*deltaB);//R at B

    if (ret[1]<0)
    {
        ret[1]=0;
    }
    else if (ret[1]>255)
    {
        ret[1]=255;
    }
       else if (ret[0]>255)
    {
        ret[0]=255;
    }
       else if (ret[0]<0)
    {
        ret[0]=0;
    }
   return ret;
}

void load_image(string filename)
{
    int dimX =532;
    int dimY = 600;

    unsigned char bufferImage[532][600];
    FILE * pFile;
    pFile = fopen("images/Dog.raw","r");
    fread(&bufferImage[0][0], dimX,dimY , pFile);
   // unsigned char solutionImage[532][600][3];
    unsigned char solutionImage[532][600][3];

   for(int i=2;i<532-2;i++)
    {
        for(int j=2;j<600-2;j++)
        {
            int color = color_decider(i,j);
            //r-0 g-1 b-2
            if(color==-1)
            {
                solutionImage[i][j][1]=bufferImage[i][j];
              vector<float> ret = calculate_g(bufferImage[i][j+1], bufferImage[i][j-1],bufferImage[i][j], bufferImage[i+1][j+1], bufferImage[i-1][j+1], bufferImage[i+1][j-1], bufferImage[i-1][j-1],bufferImage[i][j+2],bufferImage[i][j-2],bufferImage[i-2][j],bufferImage[i+2][j],bufferImage[i+1][j], bufferImage[i-1][j]);

                 solutionImage[i][j][0]=ret[1];
                 solutionImage[i][j][2]=ret[0];
            }
            else if(color==0)
            {
                solutionImage[i][j][0]=bufferImage[i][j];
                vector<float> ret = calculate_r_b(bufferImage[i][j+1], bufferImage[i][j-1], bufferImage[i+1][j], bufferImage[i-1][j],bufferImage[i][j], bufferImage[i+1][j+1], bufferImage[i+1][j-1], bufferImage[i-1][j-1], bufferImage[i-1][j+1],bufferImage[i+2][j],bufferImage[i-2][j],bufferImage[i][j+2],bufferImage[i][j-2]);
                solutionImage[i][j][1]=ret[0];
                solutionImage[i][j][2]=ret[1];
            }
            else if(color==1)
            {
                solutionImage[i][j][1]=bufferImage[i][j];
                  vector<float> ret = calculate_g(bufferImage[i][j+1], bufferImage[i][j-1],bufferImage[i][j], bufferImage[i+1][j+1], bufferImage[i-1][j+1], bufferImage[i+1][j-1], bufferImage[i-1][j-1],bufferImage[i][j+2],bufferImage[i][j-2],bufferImage[i-2][j],bufferImage[i+2][j],bufferImage[i+1][j], bufferImage[i-1][j]);
    
                solutionImage[i][j][2]=ret[1];
                solutionImage[i][j][0]=ret[0];   
            }
            else if(color==2)
            {
                solutionImage[i][j][2]=bufferImage[i][j];
               vector<float> ret = calculate_atb(bufferImage[i][j+1], bufferImage[i][j-1], bufferImage[i+1][j], bufferImage[i-1][j],bufferImage[i][j], bufferImage[i+1][j+1], bufferImage[i+1][j-1], bufferImage[i-1][j-1], bufferImage[i-1][j+1],bufferImage[i+2][j],bufferImage[i-2][j],bufferImage[i][j+2],bufferImage[i][j-2]);
                solutionImage[i][j][1]=ret[0];
                solutionImage[i][j][0]=ret[1];
            }
        }
    }



    FILE * pFile2;
   // pFile2 = fopen("newImageFile.raw","wb");
   // fwrite(&bufferImage[0][0], dimX, dimY, pFile2);
     pFile2 = fopen("demoFile.raw","wb");
    // fwrite(&solutionImage, dimX, dimY, pFile2);
    // fwrite(solutionImage, sizeof(unsigned char), 600*532*3, pFile2);
    fwrite(solutionImage, sizeof(unsigned char), sizeof(solutionImage), pFile2);
     fclose(pFile2);
}

int main()
{
    string filename = "images/Dog.raw";
     load_image(filename);
    return 0;
}