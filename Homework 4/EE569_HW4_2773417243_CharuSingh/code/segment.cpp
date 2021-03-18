#include<iostream>
#include<string>
#include<fstream>
#include<cstdint>
#include<cstring>
#include<vector>
#include<cmath>
#include <stdio.h>
#include <dirent.h>

using namespace std;

long double* reduceConValue(long double myArr[]){
    static long double finalArr[15];
    finalArr[0] = myArr[0];
    finalArr[1] = (myArr[1] + myArr[5])/2;
    finalArr[2] = (myArr[2] + myArr[10]) / 2;
    finalArr[3] = (myArr[3] + myArr[15]) / 2;
    finalArr[4] = (myArr[4] + myArr[20]) / 2;
    finalArr[5] = myArr[6];
    finalArr[6] = (myArr[7] + myArr[11]) / 2;
    finalArr[7] = (myArr[8] + myArr[16]) / 2;
    finalArr[8] = (myArr[9] + myArr[21]) / 2;
    finalArr[9] = myArr[12];
    finalArr[10] = (myArr[13] + myArr[17]) / 2;
    finalArr[11] = (myArr[14] + myArr[22]) / 2;
    finalArr[12] = myArr[18];
    finalArr[13] = (myArr[19] + myArr[23]) / 2;
    finalArr[14] = myArr[24];
    return finalArr;
}

long double* getConValue(unsigned char bufferImage[][128], int tensorSet[][5][5], int i, int j){
    long double myArr[25] = {0};
    for(int index=0; index< 25; index++){
        myArr[index] = (bufferImage[i-2][j-2]*tensorSet[index][0][0]) + (bufferImage[i-2][j-1]*tensorSet[index][0][1]) + (bufferImage[i-2][j]*tensorSet[index][0][2]) + (bufferImage[i-2][j+1]*tensorSet[index][0][3]) + (bufferImage[i-2][j+2]*tensorSet[index][0][4]) + (bufferImage[i-1][j-2]*tensorSet[index][1][0]) + (bufferImage[i-1][j-1]*tensorSet[index][1][1]) + (bufferImage[i-1][j]*tensorSet[index][1][2]) + (bufferImage[i-1][j+1]*tensorSet[index][1][3]) + (bufferImage[i-1][j+2]*tensorSet[index][1][4]) + (bufferImage[i][j-2]*tensorSet[index][2][0]) + (bufferImage[i][j-1]*tensorSet[index][2][1]) + (bufferImage[i][j]*tensorSet[index][2][2]) + (bufferImage[i][j+1]*tensorSet[index][2][3]) + (bufferImage[i][j+2]*tensorSet[index][2][4]) + (bufferImage[i+1][j-2]*tensorSet[index][3][0]) + (bufferImage[i+1][j-1]*tensorSet[index][3][1]) + (bufferImage[i+1][j]*tensorSet[index][3][2]) + (bufferImage[i+1][j+1]*tensorSet[index][3][3]) + (bufferImage[i+1][j+2]*tensorSet[index][3][4]) + (bufferImage[i+2][j-2]*tensorSet[index][4][0]) + (bufferImage[i+2][j-1]*tensorSet[index][4][1]) + (bufferImage[i+2][j]*tensorSet[index][4][2]) + (bufferImage[i+2][j+1]*tensorSet[index][4][3]) + (bufferImage[i+2][j+2]*tensorSet[index][4][4]);
    }

    static long double* finalArr = reduceConValue(myArr);
    return finalArr;
}

void load_image(string filename, int tensorSet[][5][5]){
    int dimX =128;
    int dimY = 128;
    unsigned char bufferImage[128][128];
    FILE * pFile;
    pFile = fopen(filename.c_str(),"r");
    fread(&bufferImage[0][0], dimX,dimY , pFile);
    unsigned char newImage[128][128] = {0};
    long double newImage2[128][128][15] = {0};
    float newImage3[128][128][15] = {0};
    int mask_row = 5;
    int mask_col = 5;
    
    //calculating sum of all the pixels under mask_row*mask_col mask, then average of it and substituting in original image to get new Image
    for(int i=2; i<126; i++){
        for(int j=2; j<126; j++) {
            double pixelSum = 0;
            for(int k=-2;k< mask_row-2;k++){
                for(int l=-2;l< mask_col-2;l++){
                    pixelSum = pixelSum + (1.0*bufferImage[i+k][j+l]);
                }
            }
            //cout << "PixelSum:" <<  pixelSum<< endl;
            newImage[i][j] = pixelSum/(mask_row * mask_col);
        }
    }

    //finding convolution from the tensorSet
    int count = 0;
    long double myArr[126*126] = {0};
    for(int i=0; i<128; i++){
        for(int j=0; j<128; j++){
            if(i==0 || i==1 || i==126|| i==127 || j==0 || j==1 || j==126|| j==127){
                long double tenseArr[15] = {0};
                for(int k=0; k<15;k++){
                newImage2[i][j][k] = tenseArr[k];
                }
            } else {
                long double* tenseArr = getConValue(newImage, tensorSet, i,j);
                for(int k=0; k<15;k++){
                newImage2[i][j][k] = tenseArr[k];
                }
            }
        }
    }
    float sum;
    int startPoint = mask_row/2;
    for(int i=0; i<15; i++){
        for(int j=startPoint; j<(128-startPoint); j++){
            for(int k=startPoint; k<(128-startPoint); k++){
                sum = abs(newImage2[j-2][k-2][i]) + abs(newImage2[j-2][k-1][i]) + abs(newImage2[j-2][k][i]) + abs(newImage2[j-2][k+1][i]) + abs(newImage2[j-2][k+2][i]) + abs(newImage2[j-1][k-2][i]) + abs(newImage2[j-1][k-1][i]) + abs(newImage2[j-1][k][i]) + abs(newImage2[j-1][k+1][i]) + abs(newImage2[j-1][k+2][i]) + abs(newImage2[j][k-2][i]) + abs(newImage2[j][k-1][i]) + abs(newImage2[j][k][i]) + abs(newImage2[j][k+1][i]) + abs(newImage2[j][k+2][i]) + abs(newImage2[j+1][k-2][i]) + abs(newImage2[j+1][k-1][i]) + abs(newImage2[j+1][k][i]) + abs(newImage2[j+1][k+1][i]) + abs(newImage2[j+1][k+2][i]) + abs(newImage2[j+2][k-2][i]) + abs(newImage2[j+2][k-1][i]) + abs(newImage2[j+2][k][i]) + abs(newImage2[j+2][k+1][i]) + abs(newImage2[j+2][k+2][i]);
                sum = sum/(5*5);
                //cout << sum << " ";
                newImage3[j][k][i] = sum;
            }
        }
    }
    ofstream myfile1("result_segmentation.txt");
    myfile1.open("result_segmentation.txt", ios::trunc);
    myfile1.close();
    ofstream myfile("result_segmentation.txt", ios::app);
    for(int i= startPoint; i< (128-startPoint); i++){
        for(int j=startPoint; j<(128-startPoint); j++){
            for(int k=0; k<15; k++){
                myfile << (newImage3[i][j][k]/newImage3[i][j][0]) << " ";
            }
            myfile << "\n";
        }
    }
    myfile.close();
}

main(){
    int kernelList[5][5] = {{1,4,6,4,1}, {-1,-2,0,2,1}, {-1,0,2,0,-1}, {-1,2,0,-2,1}, {1,-4,6,-4,1}};
    int tensorSet[25][5][5] = {0};
    int count =0;
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            for(int k=0; k< 5; k++){
                for(int l=0; l<5; l++){
                    tensorSet[count][k][l] = kernelList[i][k] * kernelList[j][l];
                }
            }
            count++;
        }
    }
    
    //iterate through all the files
    const string defaultPath = "/media/sf_SharedFolder/Charu/HW4/images/comp.raw";
    load_image(defaultPath, tensorSet);
}