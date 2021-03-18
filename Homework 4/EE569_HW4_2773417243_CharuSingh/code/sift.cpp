#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

Mat detectSIFTKeyPoints(Mat img, int minHessian) {
    // Declare required detector, vector and Matrix
    std::vector<KeyPoint> keypoints;
    Mat imgWithKeyPoints;
    Ptr<SIFT> detector = SIFT::create(minHessian);

    // Detect and Draw Key points
    detector->detect(img, keypoints);
    drawKeypoints(img, keypoints, imgWithKeyPoints, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    
    return imgWithKeyPoints;
}

Mat detectSURFKeyPoints(Mat img, int minHessian) {
    // Declare required detector, vector and Matrix
    std::vector<KeyPoint> keypoints;
    Mat imgWithKeyPoints;
    Ptr<SURF> detector = SURF::create(minHessian);
    
    // Detect and Draw Key points
    detector->detect(img, keypoints);
    drawKeypoints(img, keypoints, imgWithKeyPoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    
    return imgWithKeyPoints;
}

int main( int argc, char** argv )
{
    // if( argc != 13){
    //     cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
    //     cout << "program_name [input 1 image path] [input 2 image path] [input 3 image path] [input 4 image path] [output 1 image 1 path] [output 1 image 2 path] [output 1 image 3 path] [output 1 image 4 path] [output 2 image 1 path] [output 2 image 2 path] [output 2 image 3 path] [output 2 image 4 path]" << endl;
    //     return 0;}
    
    Mat img1 = imread("Husky_1.jpg", cv::IMREAD_COLOR);
    Mat img2 = imread( "Husky_2.jpg", cv::IMREAD_COLOR);
    Mat img3 = imread( "Husky_3.jpg", cv::IMREAD_COLOR);
    Mat img4 = imread("Puppy_1.jpg", cv::IMREAD_COLOR);

    if( !img1.data || !img2.data || !img3.data || !img4.data)
    { std::cout<< " --(!) Error reading images " << std::endl; return 0; }
    
    // Declare output Matrices
    Mat img1Sift, img2Sift, img3Sift, img4Sift, img1Surf, img2Surf, img3Surf, img4Surf;
    
    //Detect Sift and Surf features
    int minHessian = 20;
    img1Sift = detectSIFTKeyPoints(img1, minHessian);
    img2Sift = detectSIFTKeyPoints(img2, minHessian);
    img3Sift = detectSIFTKeyPoints(img3, minHessian);
    img4Sift = detectSIFTKeyPoints(img4, minHessian);
    
   

    // Write outputs
    imwrite("op_Husky_1.jpg",img1Sift);
    imwrite("op_Husky_2.jpg",img2Sift);
    imwrite("op_Husky_3.jpg",img3Sift);
    imwrite("op_puppy.jpg",img4Sift);
    
  
  
}
