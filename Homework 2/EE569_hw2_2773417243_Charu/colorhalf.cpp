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





void load_image(string filename)
{	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int X = 480;
    int Y = 640;


	
	// Allocate image data array
	unsigned char Imagedata[X][Y][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen("images/Rose.raw","rb"))) {
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
   

     for(int i=0; i< 480; i++){
         for(int j=0; j < 640; j++){
             Imagedata[i][j][0]= 255-  Imagedata[i][j][0];
             Imagedata[i][j][1]= 255-  Imagedata[i][j][1];
             Imagedata[i][j][2]= 255-  Imagedata[i][j][2];
         }
     }
  //   cout<<Imagedata<<"....";
     if (!(file=fopen("colorhalf1.raw","wb"))) {
                
                exit(1);
            }

            fwrite(Imagedata, sizeof(unsigned char), X*Y*BytesPerPixel, file);
            fclose(file);
        unsigned char solutionImage[480][640][BytesPerPixel];
        unsigned char solutionImage1[480][640][BytesPerPixel];
        int a=128;
        float diff, sum;
        // cout<<"charu"<<"\n";
            for (int i=1;i<479;i++){
                if (i%2!=0){
                //  cout<<"charu"<<"\n"; L 2 R
                    for (int j=1;j<639;j++)
                    {
                        for (int k=0;k<3;k++){
                            // cout << "i:::" << i << ",j:::" << j << endl;
                            if (Imagedata[i][j][k]<a){
                            diff= Imagedata[i][j][k]-0;
                            //cout<< "LessThanA" <<diff<<"\n";
                            Imagedata[i][j][k]=0;
                            
                        }    else {
                            diff= Imagedata[i][j][k]-255;
                        //  cout<< "GreaterThanA" <<diff<<"\n";
                            Imagedata[i][j][k]=255;
                        }
                        //cout<<diff<<"\n";
                        
                    //  cout<<Imagedata<<"\n";

                        // sum = getsum(i,j);
                            sum=16;
                        //if(sum != 16) {
                        //    cout<<sum << ":::" << ((3/sum)*diff)<<"\n";
                        //}
                        
                                // cout << "~~~~~" << 1 * Imagedata[i+1][j-1];
                            Imagedata[i+1][j-1][k]= (Imagedata[i+1][j-1][k] +((3/sum)*diff) );
                            Imagedata[i][j+1][k]=Imagedata[i][j+1][k] +((7/sum)*diff);
                            Imagedata[i+1][j][k]=Imagedata[i+1][j][k] +((5/sum)*diff);
                            Imagedata[i+1][j+1][k]=Imagedata[i+1][j+1][k] +((1/sum)*diff);
                            solutionImage[i][j][k] = Imagedata[i][j][k];
                        // cout << "====" << 1 * Imagedata[i+1][j-1];
                        }
                    }
                    //  cout<<diff<<"\n"<<"......";
                }
                else{
                    for (int j=639-1;j>0;j--)
                    {
                        for (int k=0;k<3;k++){
                            // cout << "i:::" << i << ",j:::" << j << endl;
                            if (Imagedata[i][j][k]<a){
                            diff= Imagedata[i][j][k]-0;
                            //cout<< "LessThanA" <<diff<<"\n";
                            Imagedata[i][j][k]=0;
                            
                        }    else {
                            diff= Imagedata[i][j][k]-255;
                        //  cout<< "GreaterThanA" <<diff<<"\n";
                            Imagedata[i][j][k]=255;
                        }
                        //cout<<diff<<"\n";
                        
                    //  cout<<Imagedata<<"\n";

                        // sum = getsum(i,j);
                            sum=16;
                        //if(sum != 16) {
                        //    cout<<sum << ":::" << ((3/sum)*diff)<<"\n";
                        //}
                        
                                // cout << "~~~~~" << 1 * Imagedata[i+1][j-1];
                            Imagedata[i+1][j-1][k]= (Imagedata[i+1][j-1][k] +((1/sum)*diff) );
                            Imagedata[i][j-1][k]=Imagedata[i][j-1][k] +((7/sum)*diff);
                            Imagedata[i+1][j][k]=Imagedata[i+1][j][k] +((5/sum)*diff);
                            Imagedata[i+1][j+1][k]=Imagedata[i+1][j+1][k] +((3/sum)*diff);
                            solutionImage[i][j][k] = Imagedata[i][j][k];
                        // cout << "====" << 1 * Imagedata[i+1][j-1];
                        }
                    }
                    //  cout<<diff<<"\n"<<"......";
                }
            }
                    for(int i=1; i< 479; i++){
                        for(int j=1; j < 639; j++){
                            solutionImage1[i][j][0]= 255-  solutionImage[i][j][0];
                            solutionImage1[i][j][1]= 255-  solutionImage[i][j][1];
                            solutionImage1[i][j][2]= 255-  solutionImage[i][j][2];
                }
                    }
                

            if (!(file=fopen("colorhalf.raw","wb"))) {
                
                exit(1);
            }

            fwrite(solutionImage1, sizeof(unsigned char), X*Y*BytesPerPixel, file);
            fclose(file);


}

    int main()
{
    printf("hello world");
    string filename = "images/Rose.raw";
     load_image(filename);
    return 0;
}
