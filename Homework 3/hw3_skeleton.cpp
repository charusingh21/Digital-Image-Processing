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
using namespace std;

int counter = 0;

void load_image(string filename)
{ // Define file pointer and variables
    FILE *file;
    FILE *file2;
    FILE *file3;
    int X = 558;
    int Y = 558;

    // Allocate image data array
    unsigned char Imagedata[X][Y];
    unsigned char Image[X][Y];
    unsigned char M_shrinkImage[X][Y] = {0};
    ;
    unsigned char P_shrinkImage[X][Y] = {0};
    unsigned char P_shrinkImage_copy[X][Y] = {0};
    unsigned char Imagedata_normalized[X][Y];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen("images/fan.raw", "rb")))
    {
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), X * Y, file);

    if (!(file = fopen("fan.raw", "wb")))
    {

        exit(1);
    }

    fwrite(Imagedata, sizeof(unsigned char), X * Y, file);
    fclose(file);
    ofstream file77;
    file77.open("output.txt");
    for (int i = 0; i < 558; i++)
    {
        for (int j = 0; j < 558; j++)
        {
            if (Imagedata[i][j] > 127)
            {
                Imagedata_normalized[i][j] = 1;
            }
            else
            {
                Imagedata_normalized[i][j] = 0;
            }
        }
    }
    file77.close();
    bool equality = false;

    while (!equality)
    {
        counter++;
        //Making copy
        for (int i = 0; i < 558; i++)
        {
            for (int j = 0; j < 558; j++)
            {
                P_shrinkImage_copy[i][j] = P_shrinkImage[i][j];
            }
        }

        int S[66][9] = {{0, 0, 1, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 1, 0, 0, 0}, {0, 1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 1, 0}, {0, 0, 1, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 1, 0, 0, 0, 0}, {1, 1, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 1, 1, 0}, {0, 0, 0, 0, 1, 0, 0, 1, 1}, {0, 0, 0, 0, 1, 1, 0, 0, 1},{0,1,0,0,1,1,0,0,0},{0,1,0,1,1,0,0,0,0},{0,0,0,1,1,0,0,1,0},{0,0,0,0,1,1,0,1,0}, {0, 0, 1, 0, 1, 1, 0, 0, 1}, {1, 1, 1, 0, 1, 0, 0, 0, 0}, {1, 0, 0, 1, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 1, 1, 1}, {1, 1, 0, 0, 1, 1, 0, 0, 0}, {0, 1, 0, 0, 1, 1, 0, 0, 1}, {0, 1, 1, 1, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 1, 1, 0, 1, 0}, {0, 1, 1, 0, 1, 1, 0, 0, 0}, {1, 1, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0, 1, 1, 0}, {0, 0, 0, 0, 1, 1, 0, 1, 1}, {1, 1, 0, 0, 1, 1, 0, 0, 1}, {0, 1, 1, 1, 1, 0, 1, 0, 0}, {1, 1, 1, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 1, 1, 0, 0, 1}, {1, 1, 1, 1, 1, 0, 0, 0, 0}, {1, 1, 0, 1, 1, 0, 1, 0, 0}, {1, 0, 0, 1, 1, 0, 1, 1, 0}, {0, 0, 0, 1, 1, 0, 1, 1, 1}, {0, 0, 0, 0, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 1, 1, 0, 1, 1}, {1, 1, 1, 0, 1, 1, 0, 0, 1}, {1, 1, 1, 1, 1, 0, 1, 0, 0}, {1, 0, 0, 1, 1, 0, 1, 1, 1}, {0, 0, 1, 0, 1, 1, 1, 1, 1}, {0, 1, 1, 0, 1, 1, 0, 1, 1}, {1, 1, 1, 1, 1, 1, 0, 0, 0}, {1, 1, 0, 1, 1, 0, 1, 1, 0}, {0, 0, 0, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 1, 1, 0, 1, 1}, {0, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 0, 0, 1}, {1, 1, 1, 1, 1, 0, 1, 1, 0}, {1, 1, 0, 1, 1, 0, 1, 1, 1}, {1, 0, 0, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 0, 1}, {1, 1, 1, 1, 1, 0, 1, 1, 1}, {1, 0, 1, 1, 1, 1, 1, 1, 1},{1,1,1,1,1,1,0,1,1},{1,1,1,1,1,1,1,1,0},{1,1,0,1,1,1,1,1,1},{0,1,1,1,1,1,1,1,1}};
       

        for (int i = 1; i < 557; i++)
        {
            for (int j = 1; j < 557; j++)
            {
                bool flag = false;
                for (int k = 0; k < 66; k++)
                {
                    if (Imagedata_normalized[i - 1][j - 1] == S[k][0] && Imagedata_normalized[i - 1][j] == S[k][1] && Imagedata_normalized[i - 1][j + 1] == S[k][2] && Imagedata_normalized[i][j - 1] == S[k][3] && Imagedata_normalized[i][j] == S[k][4] && Imagedata_normalized[i][j + 1] == S[k][5] && Imagedata_normalized[i + 1][j - 1] == S[k][6] && Imagedata_normalized[i + 1][j] == S[k][7] && Imagedata_normalized[i + 1][j + 1] == S[k][8])
                    {
                        flag = flag || true;
                    }
                }
                if (flag)
                {
                    M_shrinkImage[i][j] = 1;
                }
            }
        }

        for (int i = 1; i < 557; i++)
        {
            for (int j = 1; j < 557; j++)
            {
                if (M_shrinkImage[i][j] == 1)
                {
                    // spur
                    if ((M_shrinkImage[i][j] == M_shrinkImage[i +1][j + 1]) && M_shrinkImage[i - 1][j - 1] == 0 && M_shrinkImage[i - 1][j] == 0 && M_shrinkImage[i-1][j +1] == 0 && M_shrinkImage[i][j - 1] == 0 && M_shrinkImage[i ][j + 1] == 0 && M_shrinkImage[i + 1][j] == 0 && M_shrinkImage[i + 1][j - 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if ((M_shrinkImage[i][j] == M_shrinkImage[i + 1][j - 1]) && M_shrinkImage[i - 1][j + 1] == 0 && M_shrinkImage[i - 1][j] == 0 && M_shrinkImage[i-1][j - 1] == 0 && M_shrinkImage[i][j + 1] == 0 && M_shrinkImage[i ][j - 1] == 0 && M_shrinkImage[i + 1][j] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                     if ((M_shrinkImage[i][j] == M_shrinkImage[i - 1][j - 1]) && M_shrinkImage[i - 1][j + 1] == 0 && M_shrinkImage[i - 1][j] == 0 && M_shrinkImage[i][j - 1] == 0 && M_shrinkImage[i][j + 1] == 0 && M_shrinkImage[i+1 ][j - 1] == 0 && M_shrinkImage[i + 1][j] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    // single 4 connection
                    if ((M_shrinkImage[i][j] == M_shrinkImage[i + 1][j]) && M_shrinkImage[i - 1][j -1] == 0 && M_shrinkImage[i - 1][j] == 0 && M_shrinkImage[i-1 ][j +1] == 0 && M_shrinkImage[i][j + 1] == 0 && M_shrinkImage[i][j - 1] == 0 && M_shrinkImage[i + 1][j-1 ] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if ((M_shrinkImage[i][j] == M_shrinkImage[i][j + 1]) && M_shrinkImage[i - 1][j + 1] == 0 && M_shrinkImage[i - 1][j] == 0 && M_shrinkImage[i - 1][j - 1] == 0 && M_shrinkImage[i][j - 1] == 0 && M_shrinkImage[i + 1][j ] == 0 && M_shrinkImage[i + 1][j-1] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                     if ((M_shrinkImage[i][j] == M_shrinkImage[i][j - 1]) && M_shrinkImage[i - 1][j + 1] == 0 && M_shrinkImage[i - 1][j] == 0 && M_shrinkImage[i - 1][j - 1] == 0 && M_shrinkImage[i][j + 1] == 0 && M_shrinkImage[i + 1][j ] == 0 && M_shrinkImage[i + 1][j-1] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                     if ((M_shrinkImage[i][j] == M_shrinkImage[i-1][j]) && M_shrinkImage[i - 1][j + 1] == 0 && M_shrinkImage[i][j-1] == 0 && M_shrinkImage[i - 1][j - 1] == 0 && M_shrinkImage[i][j - 1] == 0 && M_shrinkImage[i + 1][j ] == 0 && M_shrinkImage[i + 1][j-1] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    // L cluster
                    if (M_shrinkImage[i][j] == M_shrinkImage[i][j + 1] && M_shrinkImage[i][j + 1] == M_shrinkImage[i - 1][j] && M_shrinkImage[i - 1][j+1] == 0 && M_shrinkImage[i - 1][j - 1] == 0 && M_shrinkImage[i][j - 1] == 0 && M_shrinkImage[i + 1][j - 1] == 0 && M_shrinkImage[i + 1][j] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if (M_shrinkImage[i][j] == M_shrinkImage[i - 1][j] && M_shrinkImage[i - 1][j] == M_shrinkImage[i][j - 1] && M_shrinkImage[i - 1][j - 1] == 0 && M_shrinkImage[i-1][j + 1] == 0 && M_shrinkImage[i][j + 1] == 0 && M_shrinkImage[i + 1][j - 1] == 0 && M_shrinkImage[i + 1][j] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if (M_shrinkImage[i][j] == M_shrinkImage[i + 1][j] && M_shrinkImage[i + 1][j] == M_shrinkImage[i ][j + 1] && M_shrinkImage[i - 1][j + 1] == 0 && M_shrinkImage[i-1][j - 1] == 0 && M_shrinkImage[i-1][j ] == 0 && M_shrinkImage[i ][j + 1] == 0 && M_shrinkImage[i + 1][j-1] == 0 && M_shrinkImage[i + 1][j + 1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if (M_shrinkImage[i][j] == M_shrinkImage[i+1][j] && M_shrinkImage[i+1][j] == M_shrinkImage[i + 1][j ] && M_shrinkImage[i - 1][j] == 0 && M_shrinkImage[i - 1][j + 1] == 0 && M_shrinkImage[i-1][j - 1] == 0 && M_shrinkImage[i ][j + 1] == 0 && M_shrinkImage[i + 1][j+1] == 0 && M_shrinkImage[i + 1][j-1] == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                   


                    //corner cluster
                    if (M_shrinkImage[i][j] == 1 && M_shrinkImage[i][j - 1] == 1 && M_shrinkImage[i - 1][j - 1] == 1 && M_shrinkImage[i - 1][j] == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                     if (M_shrinkImage[i][j] == 1 && M_shrinkImage[i][j + 1] == 1 && M_shrinkImage[i + 1][j] == 1 && M_shrinkImage[i + 1][j+1] == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }

                    // Tee branch
                    if (M_shrinkImage[i][j] == 1 && M_shrinkImage[i][j + 1] == 1 && M_shrinkImage[i][j - 1] == 1 && M_shrinkImage[i - 1][j] == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                   
                    if (M_shrinkImage[i][j] == 1 && M_shrinkImage[i][j + 1] == 1 && M_shrinkImage[i][j - 1] == 1 && M_shrinkImage[i + 1][j] == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                  

                    if (M_shrinkImage[i][j] == 1 && M_shrinkImage[i][j - 1] == 1 && M_shrinkImage[i + 1][j] == 1 && M_shrinkImage[i - 1][j] == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }

                  

                    if (M_shrinkImage[i][j] == 1 && M_shrinkImage[i][j + 1] == 1 && M_shrinkImage[i + 1][j] == 1 && M_shrinkImage[i - 1][j] == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }

                    //vee branch
                    if ((M_shrinkImage[i][j] && M_shrinkImage[i - 1][j + 1] && M_shrinkImage[i - 1][j - 1]) == 1 && (M_shrinkImage[i + 1][j - 1] || M_shrinkImage[i + 1][j] || M_shrinkImage[i + 1][j + 1]) == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if ((M_shrinkImage[i][j] && M_shrinkImage[i + 1][j - 1] && M_shrinkImage[i - 1][j - 1]) == 1 && (M_shrinkImage[i + 1][j + 1] || M_shrinkImage[i][j + 1] || M_shrinkImage[i - 1][j + 1]) == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if ((M_shrinkImage[i][j] && M_shrinkImage[i + 1][j + 1] && M_shrinkImage[i + 1][j - 1]) == 1 && (M_shrinkImage[i - 1][j - 1] || M_shrinkImage[i - 1][j] || M_shrinkImage[i - 1][j + 1]) == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if ((M_shrinkImage[i][j] && M_shrinkImage[i - 1][j + 1] && M_shrinkImage[i + 1][j + 1]) == 1 && (M_shrinkImage[i - 1][j - 1] || M_shrinkImage[i][j - 1] || M_shrinkImage[i + 1][j - 1]) == 1)
                    {
                        P_shrinkImage[i][j] = 1;
                    }

                    // diagonal branch
                    if ((M_shrinkImage[i][j] && M_shrinkImage[i][j + 1] && M_shrinkImage[i - 1][j] && M_shrinkImage[i + 1][j - 1]) == 1 && (M_shrinkImage[i - 1][j + 1] && M_shrinkImage[i][j - 1] && M_shrinkImage[i + 1][j]) == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if ((M_shrinkImage[i][j] && M_shrinkImage[i][j - 1] && M_shrinkImage[i - 1][j] && M_shrinkImage[i + 1][j + 1]) == 1 && (M_shrinkImage[i - 1][j - 1] && M_shrinkImage[i][j + 1] && M_shrinkImage[i + 1][j]) == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if ((M_shrinkImage[i][j] && M_shrinkImage[i][j - 1] && M_shrinkImage[i - 1][j + 1] && M_shrinkImage[i + 1][j]) == 1 && (M_shrinkImage[i - 1][j] && M_shrinkImage[i][j + 1] && M_shrinkImage[i + 1][j - 1]) == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                    if ((M_shrinkImage[i][j] && M_shrinkImage[i][j + 1] && M_shrinkImage[i - 1][j - 1] && M_shrinkImage[i + 1][j]) == 1 && (M_shrinkImage[i - 1][j] && M_shrinkImage[i][j - 1] && M_shrinkImage[i + 1][j + 1]) == 0)
                    {
                        P_shrinkImage[i][j] = 1;
                    }
                }
            }
        }
        equality = true;
        for (int i = 0; i < 558; i++)
        {
            for (int j = 0; j < 558; j++)
            {
                if (P_shrinkImage_copy[i][j] != P_shrinkImage[i][j])
                {
                    equality = equality && false;
                }
            }
        }

        if (!equality)
        {
            for (int i = 0; i < 558; i++)
            {
                for (int j = 0; j < 558; j++)
                {
                    Imagedata_normalized[i][j] = P_shrinkImage[i][j];
                }
            }
            M_shrinkImage[558][558] = {0};
        }
    }

    for (int i = 0; i < 558; i++)
    {
        for (int j = 0; j < 558; j++)
        {
            P_shrinkImage[i][j] = P_shrinkImage[i][j]*255;
        }
    }

    if (!(file2 = fopen("skeleton_fan.raw", "wb")))
    {
        exit(1);
    }
    fwrite(P_shrinkImage, sizeof(unsigned char), X * Y, file2);
}

int main()
{
    printf("hello world");

    string filename = "images/fan.raw";
    load_image(filename);
    return 0;
}