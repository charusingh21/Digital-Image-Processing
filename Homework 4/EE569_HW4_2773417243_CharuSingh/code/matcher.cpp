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

Mat imageMatchingUsingSIFT(Mat img1, Mat img2, int minHessian) {
    Ptr<SIFT> detector = SIFT::create(minHessian);
    
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    
    detector->detectAndCompute( img1, Mat(), keypoints1, descriptors1);
    detector->detectAndCompute( img2, Mat(), keypoints2, descriptors2);
    
    // Match descriptors vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match( descriptors1, descriptors2, matches );
    
    //Calculate min and max distances between keypoints
    double maxDist = 0; double minDist = 100;
    for( int i = 0; i < descriptors1.rows; i++ )
    {
        double dist = matches[i].distance;
        if( dist < minDist )
            minDist = dist;
        if( dist > maxDist )
            maxDist = dist;
    }
    printf("Max distance : %f \n", maxDist );
    printf("Min distance : %f \n", minDist );
    
    // Find good matches
    std::vector< DMatch > goodMatches;
    for( int i = 0; i < descriptors1.rows; i++ ){
        if( matches[i].distance <= max(2*minDist, 0.2)){
            goodMatches.push_back( matches[i]);
        }
    }
    
    //Draw matched images
    Mat imgMatches;
    drawMatches( img1, keypoints1, img2, keypoints2,goodMatches, imgMatches, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    
    //Print Good Matching points
    for( int i = 0; i < (int)goodMatches.size(); i++ ){
        printf( "Best Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, goodMatches[i].queryIdx, goodMatches[i].trainIdx );
     }
    
    //Return matched image
    return imgMatches;
}

int main( int argc, char** argv )
{
    // if( argc != 11){
    //     cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
    //     cout << "program_name [input 1 image path] [input 2 image path] [input 3 image path] [input 4 image path] [output match 1] [output match 2] [output match 3] [output match 4] [output match 5] [output match 6]" << endl;
    //     return 0;}
    
    Mat img1 = imread("Husky_1.jpg", cv::IMREAD_COLOR);
    Mat img2 = imread( "Husky_2.jpg", cv::IMREAD_COLOR );
    Mat img3 = imread( "Husky_3.jpg", cv::IMREAD_COLOR );
    Mat img4 = imread("Puppy_1.jpg", cv::IMREAD_COLOR );
    
    if( !img1.data || !img2.data || !img3.data || !img4.data)
    { std::cout<< " --(!) Error reading images " << std::endl; return 0; }
    
    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
    int minHessian = 600;
    
    //Ptr<SURF> detector = SURF::create(minHessian);
    Mat imgMatches1, imgMatches2, imgMatches3, imgMatches4, imgMatches5, imgMatches6;
    
    imgMatches1 = imageMatchingUsingSIFT(img2, img3, minHessian);
    
    imgMatches2 = imageMatchingUsingSIFT(img3, img4, minHessian);
    
    imgMatches3 = imageMatchingUsingSIFT(img1, img4, minHessian);

    imgMatches4 = imageMatchingUsingSIFT(img1, img3, minHessian);
    imgMatches5 = imageMatchingUsingSIFT(img1, img3, 400);

    imwrite("op1_600.jpg", imgMatches1);
    imwrite("op2_600.jpg", imgMatches2);
    imwrite("op3_600.jpg", imgMatches3);
    imwrite("op4_600.jpg", imgMatches4);
    imwrite("op4_400.jpg", imgMatches5);

}
