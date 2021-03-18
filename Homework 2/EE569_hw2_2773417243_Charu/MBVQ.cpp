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


 string mbvq(unsigned char solutionImage[480][640][0],unsigned char solutionImage[480][640][1],unsigned char solutionImage[480][640][2],int i, int j)
 {
    
     if( (1* solutionImage[i][j][0]+ 1* solutionImage[i][j][1])>255){
         if ((1* solutionImage[i][j][1]+ 1* solutionImage[i][j][2]))>255{
              if ((1* solutionImage[i][j][1]+ 1* solutionImage[i][j][2]+1* solutionImage[i][j][0]))>510){
                    mbvq='CMYW'; 

              }

              else{
                   mbvq='MYGC'; 
             
         }
         }
         else{
              mbvq='RGMY';
     }
 }
 }
    
     else{
          if( (1* solutionImage[i][j][2]+ 1* solutionImage[i][j][1])!>255){
               if ((1* solutionImage[i][j][1]+ 1* solutionImage[i][j][2]+1* solutionImage[i][j][0]))!>255){
                    mbvq='KRGB';
               }
               else{
                     mbvq='RGBM';
               }
          }
         else{
             mbvq='CMGB';

         }

              

          }
     return mbvq;
     }

 string vertex(mbvq,unsigned char solutionImage[480][640][0],unsigned char solutionImage[480][640][1],unsigned char solutionImage[480][640][2]){
     solutionImage[480][640][0] = ((1* solutionImage[480][640][0]) / 255);
     solutionImage[480][640][1] = ((1* solutionImage[480][640][1]) / 255);
     solutionImage[480][640][2] = ((1* solutionImage[480][640][2]) / 255);
     if(mbvq =='CMYW'){
         vertex='white';
         if (1* solutionImage[i][j][2]<0.5){
              if (1* solutionImage[i][j][2]<=1* solutionImage[i][j][0]){
                  if (1* solutionImage[i][j][2]<=1* solutionImage[i][j][1]){
                      vertex='yellow';
                  }
              }
         }
         if(1* solutionImage[i][j][1]<0.5){
              if (1* solutionImage[i][j][1]<=1* solutionImage[i][j][2]){
                  if (1* solutionImage[i][j][1]<=1* solutionImage[i][j][0]){
                      vertex='magenta';
                  }
              }

         }
          if (1* solutionImage[i][j][0]<0.5){
              if (1* solutionImage[i][j][0]<=1* solutionImage[i][j][2]){
                  if (1* solutionImage[i][j][0]<=1* solutionImage[i][j][1]){
                      vertex='cyan';
                  }
              }
         }
     }
     
     // MYGC
      if(mbvq =='MYGC'){
         vertex='magenta';
         if (1* solutionImage[i][j][1]>=1* solutionImage[i][j][2]){
              if (1* solutionImage[i][j][0]>=1* solutionImage[i][j][2]){
                  if (1* solutionImage[i][j][0]>0.5){
                      vertex='yellow';
                  }
                  else{
                       vertex='green';
                  }
              }
         }
         if(1* solutionImage[i][j][1]>1* solutionImage[i][j][0]){
              if (1* solutionImage[i][j][2]>=1* solutionImage[i][j][0]){
                  if (1* solutionImage[i][j][1]>0.5){
                      vertex='cyan';
                  }
                  else{
                        vertex='green';

                  }
              }

         }
      }
      //RGMY 
     
      if(mbvq =='RGMY'){
         
         if (1* solutionImage[i][j][2]>0.5){
              if (1* solutionImage[i][j][0]>0.5){
                  if (1* solutionImage[i][j][2]>=1* solutionImage[i][j][1]){
                      vertex='magenta';
                  }
                  else{
                       vertex='yellow';
                  }
              }
              
               else{
                     if (1* solutionImage[i][j][1]>1* solutionImage[i][j][2]+solutionImage[i][j][0]){
                          vertex='green';

                     }
                     else{
                          vertex='magenta';
                     }

               }
              
              }
        else{
            if  (1* solutionImage[i][j][0]>0.5){
                if (1* solutionImage[i][j][1]>0.5){
                     vertex='yellow';
                }
                else{
                     vertex='red';
                }

                }
            else{
                if (1* solutionImage[i][j][0]>=1* solutionImage[i][j][1]){
                     vertex='red';

                }
                else{
                     vertex='green';
                }

            }

            }
            

                          
         }
        // KRGB
     if(mbvq =='KRGB'){
         vertex='black';

         
         
         if (1* solutionImage[i][j][2]>0.5){
              if (1* solutionImage[i][j][0]>0.5){
                  if (1* solutionImage[i][j][2]>=1* solutionImage[i][j][0]){
                       if (1* solutionImage[i][j][2]>=1* solutionImage[i][j][1]){
                             vertex='blue';
                  }
                  }
              }
               if (1* solutionImage[i][j][1]>0.5){
                    if (1* solutionImage[i][j][1]>=1* solutionImage[i][j][2]){
                         if (1* solutionImage[i][j][1]>=1* solutionImage[i][j][0]){
                             vertex='green';
                         }
                    }
               }
                if (1* solutionImage[i][j][0]>0.5){
                    if (1* solutionImage[i][j][0]>=1* solutionImage[i][j][2]){
                         if (1* solutionImage[i][j][0]>=1* solutionImage[i][j][1]){
                             vertex='red';
                         }
                    }
               }
         }
     }
         //RGBM
     if(mbvq =='RGBM'){
         vertex='green';

         
         
         if (1* solutionImage[i][j][0]>1* solutionImage[i][j][1]){
              if (1* solutionImage[i][j][0]>=1* solutionImage[i][j][2]){
                  if (1* solutionImage[i][j][2]<0.5){
                       vertex='red';
                  }
                  else{
                       vertex='magenta';
                      

                  }
                  }
              }
        if  (1* solutionImage[i][j][2]>1* solutionImage[i][j][1]){
                    if (1* solutionImage[i][j][2]>=1* solutionImage[i][j][0]){
                         if (1* solutionImage[i][j][0]<0.5]){
                             vertex='blue';
                         }
                         else{
                              vertex='magenta';

                         }
                    }
               }
     }

         //CMGB
     if(mbvq =='CMGB'){

        

         
         
         if (1* solutionImage[i][j][2]>0.5){
              if (1* solutionImage[i][j][0]>0.5){
                  if (1* solutionImage[i][j][1]>=1* solutionImage[i][j][0]){
                       vertex='cyan';
                  }
                  else{
                       vertex='magenta';
                      

                  }
              else{
                  if (1* solutionImage[i][j][1]>0.5){
                      vertex = 'cyan';
                  } else {
                      vertex = 'blue';
                  }
               }
            }
         } else {
             if (1* solutionImage[i][j][0]>0.5) {
                 if(((1* solutionImage[i][j][0]) - (1* solutionImage[i][j][1] ) + (1* solutionImage[i][j][2]))>=0.5) {
                     vertex = 'magenta';
                 } else {
                     vertex = 'green';
                 }
             } else {
                 if(1* solutionImage[i][j][1]>=1* solutionImage[i][j][2]) {
                     vertex = 'green';
                 } else {
                     vertex = 'blue';
                 }
             }
         }
     }
     
    return vertex;
 }


/*
float error(vertex,unsigned char solutionImage[480][640][0],unsigned char solutionImage[480][640][1],unsigned char solutionImage[480][640][2]) {
    switch(vertex) {
        case 'white' : {
            solutionImage[480][640][0] = 255;
            solutionImage[480][640][1] = 255;
            solutionImage[480][640][2] = 255;
            break;
        }
        case 'yellow' : {
            solutionImage[480][640][0] = 255;
            solutionImage[480][640][1] = 255;
            solutionImage[480][640][2] = 0;
            break;
        }
        case 'cyan' : {
            solutionImage[480][640][0] = 0;
            solutionImage[480][640][1] = 255;
            solutionImage[480][640][2] = 255;
            break;
        }
        case 'green' : {
            solutionImage[480][640][0] = 0;
            solutionImage[480][640][1] = 255;
            solutionImage[480][640][2] = 0;
            break;
        }
        case 'red' : {
            solutionImage[480][640][0] = 255;
            solutionImage[480][640][1] = 0;
            solutionImage[480][640][2] = 0;
            break;
        }
        case 'blue' : {
            solutionImage[480][640][0] = 0;
            solutionImage[480][640][1] = 0;
            solutionImage[480][640][2] = 255;
            break;
        }
        case 'magenta' : {
            solutionImage[480][640][0] = 255;
            solutionImage[480][640][1] = 0;
            solutionImage[480][640][2] = 255;
            break;
        }
        default : {
            solutionImage[480][640][0] = 0;
            solutionImage[480][640][1] = 0;
            solutionImage[480][640][2] = 0;
            break;
        }
    }
}
*/        
                 
              
  
 



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
   

     /*for(int i=0; i< 480; i++){
         for(int j=0; j < 640; j++){
             Imagedata[i][j][0]= 255-  Imagedata[i][j][0];
             Imagedata[i][j][1]= 255-  Imagedata[i][j][1];
             Imagedata[i][j][2]= 255-  Imagedata[i][j][2];
         }
     }*/
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
            for (int i=1;i<479-1;i++){
                if (i%2!=0){
                //  cout<<"charu"<<"\n"; L 2 R
                    for (int j=1;j<639;j++)
                    {
                        string mbvq = mbvq(Imagedata[480][640][0],Imagedata[480][640][1],Imagedata[480][640][2],i,j);
                        string vertex = vertex(mbvq,Imagedata[480][640][0],Imagedata[480][640][1],Imagedata[480][640][2]);
                        if(strcmp('white', vertex) == 0) {
                                solutionImage[480][640][0] = 255;
                                solutionImage[480][640][1] = 255;
                                solutionImage[480][640][2] = 255;
                                
                            }
                            else if(strcmp('yellow', vertex) == 0) {
                                solutionImage[480][640][0] = 255;
                                solutionImage[480][640][1] = 255;
                                solutionImage[480][640][2] = 0;
                                
                            }
                            else if(strcmp('cyan', vertex) == 0) {
                                solutionImage[480][640][0] = 0;
                                solutionImage[480][640][1] = 255;
                                solutionImage[480][640][2] = 255;
                                
                            }
                            else if(strcmp('green', vertex) == 0) {
                                solutionImage[480][640][0] = 0;
                                solutionImage[480][640][1] = 255;
                                solutionImage[480][640][2] = 0;
                                
                            }
                            else if(strcmp('red', vertex) == 0) {
                                solutionImage[480][640][0] = 255;
                                solutionImage[480][640][1] = 0;
                                solutionImage[480][640][2] = 0;
                                
                            }
                            else if(strcmp('blue', vertex) == 0) {
                                solutionImage[480][640][0] = 0;
                                solutionImage[480][640][1] = 0;
                                solutionImage[480][640][2] = 255;
                                
                            }
                            else if(strcmp('magenta', vertex) == 0) {
                                solutionImage[480][640][0] = 255;
                                solutionImage[480][640][1] = 0;
                                solutionImage[480][640][2] = 255;
                                
                            } else {
                                solutionImage[480][640][0] = 0;
                                solutionImage[480][640][1] = 0;
                                solutionImage[480][640][2] = 0;
                            }
                        for (int k=0;k<3;k++){
                            diff = Imagedata[i][j][k]- solutionImage[480][640][k];
                            // cout << "i:::" << i << ",j:::" << j << endl;
                            
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
                        string mbvq = mbvq(Imagedata[480][640][0],Imagedata[480][640][1],Imagedata[480][640][2],i,j);
                        string vertex = vertex(mbvq,Imagedata[480][640][0],Imagedata[480][640][1],Imagedata[480][640][2]);
                            if(strcmp('white', vertex) == 0) {
                                solutionImage[480][640][0] = 255;
                                solutionImage[480][640][1] = 255;
                                solutionImage[480][640][2] = 255;
                                
                            }
                            else if(strcmp('yellow', vertex) == 0) {
                                solutionImage[480][640][0] = 255;
                                solutionImage[480][640][1] = 255;
                                solutionImage[480][640][2] = 0;
                                
                            }
                            else if(strcmp('cyan', vertex) == 0) {
                                solutionImage[480][640][0] = 0;
                                solutionImage[480][640][1] = 255;
                                solutionImage[480][640][2] = 255;
                                
                            }
                            else if(strcmp('green', vertex) == 0) {
                                solutionImage[480][640][0] = 0;
                                solutionImage[480][640][1] = 255;
                                solutionImage[480][640][2] = 0;
                                
                            }
                            else if(strcmp('red', vertex) == 0) {
                                solutionImage[480][640][0] = 255;
                                solutionImage[480][640][1] = 0;
                                solutionImage[480][640][2] = 0;
                                
                            }
                            else if(strcmp('blue', vertex) == 0) {
                                solutionImage[480][640][0] = 0;
                                solutionImage[480][640][1] = 0;
                                solutionImage[480][640][2] = 255;
                                
                            }
                            else if(strcmp('magenta', vertex) == 0) {
                                solutionImage[480][640][0] = 255;
                                solutionImage[480][640][1] = 0;
                                solutionImage[480][640][2] = 255;
                                
                            } else {
                                solutionImage[480][640][0] = 0;
                                solutionImage[480][640][1] = 0;
                                solutionImage[480][640][2] = 0;
                            }
                        
                        for (int k=0;k<3;k++){
                            // cout << "i:::" << i << ",j:::" << j << endl;
                            diff = Imagedata[i][j][k]- solutionImage[480][640][k];
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
