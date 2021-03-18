#include <stdio.h>
#include <string>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

class bagOfWords{
public:
    Mat img1,img2,img3,img4;
    int minHessian;
    Mat descriptors1, descriptors2, descriptors3, descriptors4;
    Mat vocabularyCentroids;
    int * img1HistVocab;
    int * img2HistVocab;
    int * img3HistVocab;
    int * img4HistVocab;
    
    bagOfWords(Mat inpImg1, Mat inpImg2, Mat inpImg3, Mat inpImg4, int inpMinHessian){
        img1 = inpImg1;
        img2 = inpImg2;
        img3 = inpImg3;
        img4 = inpImg4;
        minHessian = inpMinHessian;
    }
    
    //Detect SIFT Descriptors for an image
    Mat detectSIFTDescriptors(Mat img) {
        Ptr<SIFT> detector = SIFT::create(minHessian);
        std::vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute( img, Mat(), keypoints, descriptors);
        return descriptors;
    }
    
    // Compute descriptors for all images
    void detectAllImageSIFTDescriptors(){
        descriptors1 = detectSIFTDescriptors(img1);
        descriptors2 = detectSIFTDescriptors(img2);
        descriptors3 = detectSIFTDescriptors(img3);
        descriptors4 = detectSIFTDescriptors(img4);
        cout << "" << endl;
        cout << "Des1 R " << descriptors1.rows << endl;
        cout << "Des1 C: " << descriptors1.cols << endl;
        cout << "" << endl;
        cout << "Des2 R: " << descriptors2.rows << endl;
        cout << "Des2  C: " << descriptors2.cols << endl;
        cout << "" << endl;
        cout << "Des3 R: " << descriptors3.rows << endl;
        cout << "Des3 C: " << descriptors3.cols << endl;
        cout << "" << endl;
        cout << "Des4 R: " << descriptors4.rows << endl;
        cout << "Des4 C: " << descriptors4.cols << endl;
    }
    
    // Training to find cluster centroids based on img1, img2 and img3
    void trainBagOfWords(Mat trainDescriptor1, Mat trainDescriptor2, Mat trainDescriptor3, int nClusters){
        BOWKMeansTrainer BGOWORDS(nClusters);
        BGOWORDS.add(trainDescriptor1);
        BGOWORDS.add(trainDescriptor2);
        BGOWORDS.add(trainDescriptor3);
        vocabularyCentroids = BGOWORDS.cluster();
        cout << "" << endl;
        cout << "Vocab R: " << vocabularyCentroids.rows << endl;
        cout << "Vocab C: " << vocabularyCentroids.cols << endl;
    }
    
    //Find Histogram of Vocabulary for an image
    int * findVocabHistogram(Mat descriptors){
        int * histVocab = new int [vocabularyCentroids.rows]();
        
        //Using L2 Distance to find the closest Centroid to every feature
        for(int featureNo=0; featureNo<descriptors.rows; featureNo++){
            
            //Find distance from all centroids
            long double * tempArray = new long double [vocabularyCentroids.rows]();
            for(int centroidNo=0; centroidNo<vocabularyCentroids.rows; centroidNo++){
                long double tempSum=0;
                for(int dimNo=0; dimNo<vocabularyCentroids.cols; dimNo++){
                    long double tempDiff = descriptors.at<float>(featureNo,dimNo) - vocabularyCentroids.at<float>(centroidNo,dimNo);
                    tempSum = tempSum + pow(tempDiff,2);
                }
                tempSum = sqrt(tempSum);
                tempArray[centroidNo] = tempSum;
            }
            
            //Find centroid with minimum distance
            long double minDist = tempArray[0];
            int minDistIndex = 0;
            for(int i=1; i<vocabularyCentroids.rows; i++) {
                if(tempArray[i] < minDist){
                    minDist = tempArray[i];
                    minDistIndex = i;
                }
            }
            
            //Add Count to the Histogram of minimum centroid
            histVocab[minDistIndex] ++;
        }
        return histVocab;
    }
    
    //Find Histogram of Vocabulary for all images
    void findAllImagesVocabHistogram(){
        img1HistVocab = findVocabHistogram(descriptors1);
        img2HistVocab = findVocabHistogram(descriptors2);
        img3HistVocab = findVocabHistogram(descriptors3);
        img4HistVocab = findVocabHistogram(descriptors4);
    }
    
    //Histogram Matching Value
    long double returnHistogramMatchingValue(int *outHist, int * inpHist, int histLen) {
        long double matchValue = 0;
        for(int i=0; i< histLen; i++){
            matchValue = matchValue + (abs(outHist[i] - inpHist[i]));
        }
        matchValue = matchValue/((long double) histLen);
        return matchValue;
    }
    
    //Match All Training images histogram with test image and find best matched one
    void matchTestImageHistogram(){
        long double * tempMatchArray = new long double [3]();
        cout << "-----------------" << endl;
        tempMatchArray[0] = returnHistogramMatchingValue(img4HistVocab, img1HistVocab, vocabularyCentroids.rows);
        cout << "Error Matching with Image 1 - Husky_1: " << tempMatchArray[0] << endl;
        tempMatchArray[1] = returnHistogramMatchingValue(img4HistVocab, img2HistVocab, vocabularyCentroids.rows);
        cout << "Error Matching with Image 2: Husky_2" << tempMatchArray[1] << endl;
        tempMatchArray[2] = returnHistogramMatchingValue(img4HistVocab, img3HistVocab, vocabularyCentroids.rows);
        cout << "Error Matching with Image 3: Puppy_1" << tempMatchArray[2] << endl;
        
        //Find good match
        long double minValue = tempMatchArray[0];
        int minIndex = 0;
        for(int i=1; i< 3; i++) {
            if(tempMatchArray[i] < minValue){
                minValue = tempMatchArray[i];
                minIndex = i;
            }
        }
        
        // print good match
        cout << "-----------------" << endl;
        cout << "-----------------" << endl;
        cout << "Best Match of Image 4 is with Image " << minIndex+1 << endl;
        cout << "-----------------" << endl;
    }
};

void fileWriteHist(char* fileName, int *histData, int DATALEN) {
    FILE *file;
    file = fopen(fileName, "w");
    if (file != NULL)
    {
        for (int i = 0; i < DATALEN;  i++)
        {
            fprintf(file, "%d\t%d\n", i, histData[i]);
        }
        fclose(file);
        //cout << "File " << fileName << " written successfully !!!" << endl;
    }
    else
    {
        cout << "Cannot open file " << fileName << endl;
    }
}

int main()
{   
    Mat img1 = imread("Husky_1.jpg", cv::IMREAD_COLOR);
    Mat img2 = imread( "Husky_2.jpg", cv::IMREAD_COLOR );
    Mat img3 = imread( "Puppy_1.jpg", cv::IMREAD_COLOR );
    Mat img4 = imread("Husky_3.jpg", cv::IMREAD_COLOR );
    
    int noClusts = 8;
    bagOfWords bowObj = bagOfWords(img1, img2, img3, img4, 400);
    bowObj.detectAllImageSIFTDescriptors();
    bowObj.trainBagOfWords(bowObj.descriptors1, bowObj.descriptors2, bowObj.descriptors3, noClusts);
    bowObj.findAllImagesVocabHistogram();
    bowObj.matchTestImageHistogram();
 
    fileWriteHist("op1.txt", bowObj.img1HistVocab, noClusts);
    fileWriteHist("op2.txt", bowObj.img2HistVocab, noClusts);
    fileWriteHist("op3.txt", bowObj.img3HistVocab, noClusts);
    fileWriteHist("op4.txt", bowObj.img4HistVocab, noClusts);
}