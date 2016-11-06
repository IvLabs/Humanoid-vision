
#include "Image_Processing.h"

Mat Image_Processing::denoising(Mat thresh)
{
	
	dilate( thresh,thresh, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
        erode(thresh, thresh, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
         
	
        //imshow("morphing",thresh);
return thresh;
}

int* Image_Processing::centroid(Mat thresholded,Mat src,int A)
{
	static int coordinates1[2];static int coordinates2[2];
	static int coordinates3[2];
	Moments oMoments = moments(thresholded);
	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	double dArea = oMoments.m00;
        
// if the area <= 10000, I consider that the there are no object in the image and it's because of the

if (dArea > 10000)
{
	//calculate the position
	int posX= dM10 / dArea;
	int posY= dM01 / dArea;
if (posX >= 0 && posY >= 0)
{
//Draw a red line from the previous point to the current point
     	circle(thresholded, Point(posX,posY),2,Scalar(0,255,0),2);
	if (A==1)
        {
	   coordinates1[0]=posX;
	   coordinates1[1]=posY;
           
	  // imshow(" thresholded ",thresholded);
	}
	else if (A==2)
	{
	   coordinates2[0]=posX;
	   coordinates2[1]=posY;
	   //imshow(" thresholded ",thresholded);
	}
	else if(A==3)
	{
           coordinates3[0]=posX;
	   coordinates3[1]=posY;
           
	  // imshow(" thresholded ",thresholded);
	}
}
}
if(A==1)
    	return coordinates1;
else if(A==2)
    	return coordinates2;
else if(A==3)
    	return coordinates3;
}


