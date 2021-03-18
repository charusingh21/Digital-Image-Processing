#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <typeinfo>
#include <time.h>
#include <unordered_map> 
using namespace std;

int labelCounter = 1;

void load_image(string filename)
{ // Define file pointer and variables
    cout << "here" << endl;

    FILE *file;
    //	int BytesPerPixel=3;
    int X = 239;
    int Y = 372;

    // Allocate image data array
    unsigned char bufferImage[X][Y];
    unsigned char Imagedata[X][Y];
     unsigned char Image[X][Y];
    int Imagedata_normalized[X][Y];
    int label[X][Y] = {0};

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen("images/PCB.raw", "rb")))
    {
        //	cout << "Cannot open file: " << filename <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), X * Y, file);

    if (!(file = fopen("PCB.raw", "wb")))
    {

        exit(1);
    }


     for(int i=0; i<239;i++){
         for(int j=0; j<372;j++){
             Image[i][j]= 255-Imagedata[i][j];
         }
      }
   if (!(file=fopen("inverted_pcb.raw","wb"))) {
		
		exit(1);
	}


	fwrite(Image, sizeof(unsigned char), X*Y, file);

    //normalizing image: 0 or 1
    for (int i = 0; i < 239; i++)
    {
        for (int j = 0; j < 372; j++)
        {
            if (Image[i][j] > 127)
            {
                Imagedata_normalized[i][j] = 1;
            }
            else
            {
                Imagedata_normalized[i][j] = 0;
            }
        }
    }
    //Raster scanning of image, first pass 
     cout << "here2222" << endl;     
   for (int i = 1; i < 238; i++)
    {
        for (int j = 1; j < 371; j++)
        {

            if (Imagedata_normalized[i][j] == 1)
            {
                if (label[i - 1][j - 1] == 0 && label[i - 1][j] == 0 && label[i - 1][j + 1] == 0 && label[i][j - 1] == 0)
                {
                    labelCounter++;
                    label[i][j] = labelCounter;
                }
                else
                {
                    int myArr[5] = {label[i - 1][j - 1], label[i - 1][j], label[i - 1][j + 1], label[i][j - 1]};
                    int min = label[i - 1][j - 1] + label[i - 1][j] + label[i - 1][j + 1] + label[i][j - 1];
                    for (int i = 0; i < 4; i++)
                    {
                        if (myArr[i] != 0 && min > myArr[i])
                        {
                            min = myArr[i];
                        }
                    }
                    label[i][j] = min;
                }
            }
        }
    }

    for (int i = 1; i < 238; i++)
    {
        for (int j = 1; j < 371; j++)
        {
            if (label[i][j] != 0)
            {
                int array[9] = {label[i - 1][j - 1], label[i - 1][j], label[i - 1][j + 1], label[i][j - 1], label[i][j], label[i][j + 1], label[i + 1][j - 1], label[i + 1][j], label[i + 1][j + 1]};
                int min = label[i - 1][j - 1] + label[i - 1][j] + label[i - 1][j + 1] + label[i][j - 1] + label[i][j] + label[i][j + 1] + label[i + 1][j - 1] + label[i + 1][j] + label[i + 1][j + 1];
                for (int i = 0; i < 9; i++)
                {
                    if (array[i] != 0 && min > array[i])
                    {
                        min = array[i];
                    }
                }
                label[i][j] = min;
                if (label[i - 1][j - 1] != 0) label[i - 1][j - 1] = min;
                if (label[i - 1][j] != 0) label[i - 1][j] = min;
                if (label[i - 1][j + 1] != 0) label[i - 1][j + 1] = min;
                if (label[i][j - 1] != 0) label[i][j - 1] = min;
                if (label[i][j + 1] != 0) label[i][j + 1] = min;
                if (label[i + 1][j - 1] != 0) label[i + 1][j - 1] = min;
                if (label[i + 1][j] != 0) label[i + 1][j] = min;
                if (label[i + 1][j + 1] != 0) label[i + 1][j + 1] = min;
            }
        }
    }

    unordered_map<int, int> myMap;
    for (int i = 1; i < 238; i++)
    {
        for (int j = 1; j < 371; j++)
        {
            if (label[i][j] != 0)
            {
                if (myMap[label[i][j]])
                {
                    myMap[label[i][j]] = myMap[label[i][j]] + 1;
                }
                else
                {
                    myMap[label[i][j]] = 1;
                }
            }
        }
    }
    int counter = 0;
    unordered_map<int, int> myMap2;
    for (auto x : myMap)
    {
        if (myMap2[x.second])
        {
            myMap2[x.second] = myMap2[x.second] + 1;
        }
        else
        {
            myMap2[x.second] = 1;
        }
         cout << x.first << " " << x.second << endl;
        counter++;
    }
    cout << "\n=====================================\n";
    cout << "Path Count:" << counter;
    cout << "\n=====================================\n";

    for (auto x : myMap2)
    {
          cout << x.first << " " << x.second << endl;
    }

}


int main()
{
    printf("hello world");
    string filename = "images/stars.raw";
    load_image(filename);
    return 0;
}
