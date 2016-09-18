#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<opencv2/core/core.hpp>
#include <stdlib.h>
#include <stdio.h>
#include<iostream>

using namespace cv;
using namespace std;

/** @function main */
int main( int argc, char* argv[] )
{

  Mat src, src_gray;
  Mat grad;
  
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  int c;
  

vector<Mat> regions;
Mat region_frame;


 VideoCapture cap(1);
   if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the video file" << endl;
         return -1;
    }


  /// Load an image
 
     

while(1)
{
Mat src;
int width = src.cols * 0.05;
int heigth = src.rows * 0.05;
int count=0;

        bool bSuccess = cap.read(src); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        break;

  GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

for(int y=0; y<=(src.rows - heigth); y+=heigth)
{
    for(int x=0; x<=(src.cols - width); x+=width)
    {
        Rect region = Rect(x, y, width, heigth);
        region_frame = src(region);
        regions.push_back(region_frame);
        count++;            
    }
}
for(int i=0;i<count;i++)
{
imshow("crop",regions[i]);
waitKey(0);
}

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create window
 
  /// Generate grad_x and grad_y
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  /// Gradient X
  //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );

  /// Gradient Y
  //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_y, abs_grad_y );

  /// Total Gradient (approximate)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

  imshow( "img1", grad );
  
  waitKey(0);
}
  return 0;
  }
