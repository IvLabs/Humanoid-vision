/*
*********************************************************
*							*
*	Author :  Aniket : IvLabs                       *
*                 Radha                                 *
*							*
*********************************************************
*/

#include "Thresholding.h"

Thresholding::Thresholding(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH)
       {
        setName(diff_blue,diff_green,diff_red,gray,value,rLowH,rHighH,gLowH, gHighH,bLowH,bHighH);
       }

void Thresholding::setName(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH)
     {
        flag = value;
              
     
       if(value==1)
        {
        threshold_blue=diff_blue > bLowH & diff_blue < bHighH & diff_green > gLowH & diff_green < gHighH &diff_red> rLowH & diff_red< rHighH ;
       
        //threshold_blue=(diff_blue)- gray ;
	GaussianBlur( threshold_blue, threshold_blue,Size(5,5),0) ;
	threshold(threshold_blue,threshold_blue,0,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
        // cv::adaptiveThreshold(threshold_blue,threshold_blue,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,7,7);
        
        imshow("thresh",threshold_blue);
        
	//threshold_blue=diff_blue > bLowH & diff_blue < bHighH & diff_green > gLowH & diff_green < gHighH &diff_red> rLowH & diff_red< rHighH ;
	}
       
       
     } 
Mat Thresholding::getName()
    {
     	if (flag ==1 )
          return threshold_blue;
        else if (flag ==2)
          return threshold_yellow;
        else if (flag ==3)
          return threshold_red;
    }
