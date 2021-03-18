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
    unsigned char solutionImage[500][750];
    int a=128;
    float diff, sum;
   // cout<<"charu"<<"\n";
    for (int i=1;i<499-1;i++){
        if (i%2!=0){
           //  cout<<"charu"<<"\n"; L 2 R
             for (int j=1;j<749;j++)
             {
                // cout << "i:::" << i << ",j:::" << j << endl;
                 if (Imagedata[i][j]<a){
                     diff= Imagedata[i][j]-0;
                     //cout<< "LessThanA" <<diff<<"\n";
                     Imagedata[i][j]=0;
                     
                 } else {
                     diff= Imagedata[i][j]-255;
                   //  cout<< "GreaterThanA" <<diff<<"\n";
                      Imagedata[i][j]=255;
                 }
                 //cout<<diff<<"\n";
                
               //  cout<<Imagedata<<"\n";

                 // sum = getsum(i,j);
                 sum=16;
                 //if(sum != 16) {
                 //    cout<<sum << ":::" << ((3/sum)*diff)<<"\n";
                 //}
                 
                // cout << "~~~~~" << 1 * Imagedata[i+1][j-1];
                 Imagedata[i+1][j-1]= (Imagedata[i+1][j-1] +((3/sum)*diff) );
                 Imagedata[i][j+1]=Imagedata[i][j+1] +((7/sum)*diff);
                 Imagedata[i+1][j]=Imagedata[i+1][j] +((5/sum)*diff);
                 Imagedata[i+1][j+1]=Imagedata[i+1][j+1] +((1/sum)*diff);
                 solutionImage[i][j] = Imagedata[i][j];
                // cout << "====" << 1 * Imagedata[i+1][j-1];
             }
            //  cout<<diff<<"\n"<<"......";
        }
        else{
           // int j=749-1;
           //  cout<<"singh"<<"\n";
             for (int j=749-1;j>0;j--)
             {
                // cout << "i:::" << i << ",j:::" << j << endl;
                 if (Imagedata[i][j]<a){
                     diff= Imagedata[i][j]-0;
                     //cout<< "LessThanA" <<diff<<"\n";
                     Imagedata[i][j]=0;
                     
                 } else {
                     diff= Imagedata[i][j]-255;
                   //  cout<< "GreaterThanA" <<diff<<"\n";
                      Imagedata[i][j]=255;
                 }
                 //cout<<diff<<"\n";
                
               //  cout<<Imagedata<<"\n";

                // sum = getsum(i,j);
                 sum=16;
                // cout<<diff<<"\n";
                 Imagedata[i+1][j-1]=Imagedata[i+1][j-1] +((1/sum)*diff);
                 Imagedata[i][j-1]=Imagedata[i][j-1] +((7/sum)*diff);
                 Imagedata[i+1][j]=Imagedata[i+1][j] +((5/sum)*diff);
                 Imagedata[i+1][j+1]=Imagedata[i+1][j+1] +((3/sum)*diff);
                 solutionImage[i][j] = Imagedata[i][j];

             }
        
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
 mse=(r/(500*750));
  cout<<mse<<"==========";

      if (!(file=fopen("err.raw","wb"))) {
		
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
