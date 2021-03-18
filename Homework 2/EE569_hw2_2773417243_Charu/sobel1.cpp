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
using namespace std;





vector<float> maskedElement(unsigned char solutionImage[321][481], float mask[][3],float mask1[][3], int i,int j)  //get convolution result
{

   vector<float> sum(2);
  
    for(int k=0;k<3;k++)
    {
        for(int l=0;l<3;l++)
        {
        sum[0]=sum[0]+(solutionImage[k+i-1][l+j-1]*mask[k][l]);
      
        sum[1]=sum[1]+(solutionImage[k+i-1][l+j-1]*mask1[k][l]);
        }
        
    }
    //cout << "========================" << "\n";
    return sum;
   
}



void load_image(string filename)
{	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int X = 321;
    int Y = 481;


	
	// Allocate image data array
	unsigned char Imagedata[X][Y][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen("images/Gallery.raw","rb"))) {
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
    unsigned char solutionImage[321][481];
    float solutionImage1[321][481];
  //  float solutionImage2[321][481];
    unsigned char solutionImage2[321][481];
    float solutionImage3[321][481];
    unsigned char solutionImage4[321][481];
    unsigned char solutionImage5[321][481];
     unsigned char solutionImage6[321][481];
      unsigned char solutionImage7[321][481];
      float mask1[3][3]={                                        //initialize Kernel matrix
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };
      float mask[3][3]={                                        //initialize Kernel matrix
        {1,2,1},
        {0,0,0},
        {-1,-2,-1}
    };
   

     for(int i=0; i< 321; i++){
         for(int j=0; j < 481; j++){
             //cout << 1*(Imagedata[i][j][0]) << "\n";
             float a;
           
            a = ((0.2989*(Imagedata[i][j][0]))+(0.5870*(Imagedata[i][j][1]))+ (0.1140*(Imagedata[i][j][2])));
            // cout <<  typeid(a).name() <<  "\n";
            solutionImage[i][j] = a;
            
         
         }
     }

      if (!(file=fopen("sobel1.raw","wb"))) {
		
		exit(1);
	}

	fwrite(solutionImage, sizeof(unsigned char), X*Y, file);
	fclose(file);

     float max_1 = 0;
     float max_2 = 0;
     float min_1 =0;
     float min_2=0;
      for(int i=0;i<321;i++)
        {
        for(int j=0;j<481;j++)
            {
                vector <float> ret = maskedElement(solutionImage,mask,mask1,i,j);
                if(ret[0] > max_1) {
                    max_1 = ret[0];
                }
                if(ret[1] > max_2) {
                    max_2 = ret[1];
                }
                if(ret[0] < min_1) {
                    min_1 = ret[0];
                }
                if(ret[1] < min_2) {
                    min_2 = ret[1];
                }
            }
    }

    cout << "minimum" << 1*min_1 << "  " << 1*min_2  << "\n";
    cout << "maximum" << 1*max_1 << "  " << 1*max_2  << "\n";
      for(int i=1;i<321-1;i++)
    {
        for(int j=1;j<481-1;j++)
        {
      //    float maskedResult = maskedElement(solutionImage,mask,i,j);

         vector <float> ret = maskedElement(solutionImage,mask,mask1,i,j);
         
       //  cout << "=========" << "\n";
       //  cout << ret[0] << "   " << ret[1] << "\n";
    
       
       solutionImage1[i][j]= (255*((ret[0]-min_1)/(max_1-min_1)));
     //  solutionImage1[i][j]= ret[0]*(255*((solutionImage[i][j]-min_1)/(max_1-min_1)));
       solutionImage2[i][j]= solutionImage1[i][j];
       solutionImage3[i][j]= (255*((ret[1]-min_1)/(max_1-min_1)));
       solutionImage4[i][j]= solutionImage3[i][j];

    
  //   cout <<  solutionImage1[i][j] << "=====================";


 
        float final1 =sqrt(pow(ret[0],2)+pow(ret[1],2));

         solutionImage6[i][j]= final1;
        
            int a = 85;
           if (final1 <a){
               final1=0;
           }
           else {
               final1=255;
           }





        solutionImage5[i][j]= final1;

      
          
         
 
         }
    }
    
         
 float array_r[256] = {};
 for(int i=0; i< 321; i++){
        for (int j=0; j< 481; j++){
             array_r[solutionImage6[i][j]]++;
        }
 }

 for(int i=0; i< 256; i++){
        array_r[i] = array_r[i]/(154401);
      
    }
    // calulated cdf
    for(int i=1; i< 256; i++){
        array_r[i] = (array_r[i-1] + array_r[i]);
     
    }
// rounding off to floor value
    for(int i=0; i< 256; i++){
        array_r[i] = floor(array_r[i]*255);
      
    }

     for(int i=0; i< 321; i++){
         for(int j=0; j < 481; j++){
            // cout <<  array_r[Imagedata[i][j][0]] << "\n";
             solutionImage7[i][j] = array_r[solutionImage6[i][j]];
         }
     }
       ofstream outputFile;
    outputFile.open("out2.csv");
     for(int i=0;i<256;i++)
    {
    outputFile<< array_r[i]   << "\n" ;

         
    }
    
  //  outputFile << r << ","<< g<< "," <<b;
    outputFile.close();








       if (!(file=fopen("sobel1.raw","wb"))) {

		
	 	exit(1);
	 }

  //   cout <<  1*solutionImage1[i][j] << "=====================";

     fwrite(solutionImage2, sizeof(unsigned char), X*Y, file);
	 fclose(file);

      if (!(file=fopen("sobel2.raw","wb"))) {
		
		exit(1);
	}

    // cout <<  1*solutionImage1[1][1] << "=====================";

	fwrite(solutionImage4, sizeof(unsigned char), X*Y, file);
	fclose(file);
     if (!(file=fopen("sobel3_160.raw","wb"))) {

		
	 	exit(1);
	 }

  //   cout <<  1*solutionImage1[i][j] << "=====================";

     fwrite(solutionImage5, sizeof(unsigned char), X*Y, file);
	 fclose(file);
      if (!(file=fopen("sobel4.raw","wb"))) {

		
	 	exit(1);
	 }

  //   cout <<  1*solutionImage1[i][j] << "=====================";

     fwrite(solutionImage6, sizeof(unsigned char), X*Y, file);
	 fclose(file);
   
}

    int main()
{
    printf("hello world");
    string filename = "images/Gallery.raw";
     load_image(filename);
    return 0;
}
