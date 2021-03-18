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

long double getConValue(unsigned char bufferImage[][128], int tensorSet[][5][5], int index){
    long double energySum = 0;
    for(int i=2; i<126; i++){
        for(int j=2; j<126;j++){
            float intermediateSum = (bufferImage[i-2][j-2]*tensorSet[index][0][0]) + (bufferImage[i-2][j-1]*tensorSet[index][0][1]) + (bufferImage[i-2][j]*tensorSet[index][0][2]) + (bufferImage[i-2][j+1]*tensorSet[index][0][3]) + (bufferImage[i-2][j+2]*tensorSet[index][0][4]) + (bufferImage[i-1][j-2]*tensorSet[index][1][0]) + (bufferImage[i-1][j-1]*tensorSet[index][1][1]) + (bufferImage[i-1][j]*tensorSet[index][1][2]) + (bufferImage[i-1][j+1]*tensorSet[index][1][3]) + (bufferImage[i-1][j+2]*tensorSet[index][1][4]) + (bufferImage[i][j-2]*tensorSet[index][2][0]) + (bufferImage[i][j-1]*tensorSet[index][2][1]) + (bufferImage[i][j]*tensorSet[index][2][2]) + (bufferImage[i][j+1]*tensorSet[index][2][3]) + (bufferImage[i][j+2]*tensorSet[index][2][4]) + (bufferImage[i+1][j-2]*tensorSet[index][3][0]) + (bufferImage[i+1][j-1]*tensorSet[index][3][1]) + (bufferImage[i+1][j]*tensorSet[index][3][2]) + (bufferImage[i+1][j+1]*tensorSet[index][3][3]) + (bufferImage[i+1][j+2]*tensorSet[index][3][4]) + (bufferImage[i+2][j-2]*tensorSet[index][4][0]) + (bufferImage[i+2][j-1]*tensorSet[index][4][1]) + (bufferImage[i+2][j]*tensorSet[index][4][2]) + (bufferImage[i+2][j+1]*tensorSet[index][4][3]) + (bufferImage[i+2][j+2]*tensorSet[index][4][4]);
            energySum = energySum + (abs(intermediateSum));
        }
    }

    energySum = energySum/(128*128);
    return energySum;
}

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

void load_image(string filename, int tensorSet[][5][5]){
    cout << filename << endl;
    int dimX =128;
    int dimY = 128;
    unsigned char bufferImage[128][128];
    FILE * pFile;
    pFile = fopen(filename.c_str(),"r");
    fread(&bufferImage[0][0], dimX,dimY , pFile);
    unsigned char newImage[128][128];
    long double pixelSum = 0;
    
    //calculating sum of all the pixels of the image and then average
    for(int i=0; i<128; i++){
        for(int j=0; j<128; j++) {
            pixelSum = pixelSum + (1*bufferImage[i][j]);
        }
    }
    double avgVal = pixelSum / (dimX*dimY);
    
    //getting new image pixels after (current pixel - average)
    for(int i=0; i<128; i++){
        for(int j=0; j< 128; j++){
            newImage[i][j] = ((1*bufferImage[i][j]) - avgVal);
        }
    }

    //finding convolution from the tensorSet
    long double myArr[25] = {0};
    for(int i=0; i< 25; i++){
        myArr[i] = getConValue(newImage,tensorSet,i);
    }
    long double* finalArr = reduceConValue(myArr);

    //Writing to a file
    ofstream myfile("result.txt", ios::app);
    for(int i=0; i< 15; i++){
        myfile << finalArr[i] << " ";
    }
    myfile << "\n";
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
    const char *files[36] = {"blanket1.raw" , "blanket2.raw" , "blanket3.raw" , "blanket4.raw" , "blanket5.raw" , "blanket6.raw" , "blanket7.raw" , "blanket8.raw" , "blanket9.raw" , "brick1.raw" , "brick2.raw" , "brick3.raw" , "brick4.raw" , "brick5.raw" , "brick6.raw" , "brick7.raw" , "brick8.raw" , "brick9.raw" , "grass1.raw" , "grass2.raw" , "grass3.raw" , "grass4.raw" , "grass5.raw" , "grass6.raw" , "grass7.raw" , "grass8.raw" , "grass9.raw" , "rice1.raw" , "rice2.raw" , "rice3.raw" , "rice4.raw" , "rice5.raw" , "rice6.raw" , "rice7.raw" , "rice8.raw" , "rice9.raw"};
    const string defaultPath = "/media/sf_SharedFolder/Charu/HW4/images/";
    ofstream myfile("result.txt");
    myfile.open("result.txt", ios::trunc);
    myfile.close();
    for(int i=0; i<36; i++){
        string s;
        s+=files[i];
        string myFile = defaultPath + s;
        load_image(myFile, tensorSet);
    }
}