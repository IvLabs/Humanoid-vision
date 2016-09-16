/*
*********************************************************
*							*
*	Author :  Aniket : IvLabs                       *
*                 Radha                                 *
*							*
*********************************************************
*/

#include "Thresholding.h"

Thresholding::Thresholding(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value)
       {
        setName(diff_blue,diff_green,diff_red,gray,value);
       }

void Thresholding::setName(Mat diff_blue,Mat diff_green,Mat diff_red,Mat gray,int value)
     {
        flag = value;
              
     
       if(value==1)
        {
        threshold_blue=(diff_blue)- gray ;
	GaussianBlur(threshold_blue,threshold_blue,Size(5,5),0) ;
	threshold(threshold_blue,threshold_blue,0,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
        }
       if(value==3)
        {
        threshold_red=(diff_red)- gray ;
	GaussianBlur(threshold_red,threshold_red,Size(5,5),0) ;
	threshold(threshold_red,threshold_red,0,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
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
