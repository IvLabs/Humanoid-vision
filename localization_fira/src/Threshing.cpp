
#include "Threshing.h"

Threshing::Threshing(Mat src)
       {
        setName(src);
       }

void Threshing::setName(Mat src)
     {
        
       cvtColor(src,grayscale,CV_BGR2GRAY);     
     
       cv::adaptiveThreshold(grayscale,threshold_blue,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,7,7);
       imshow("thresholded",threshold_blue);
       
     }
Mat Threshing::getName()
    {
     	
          return threshold_blue;
      
    }
