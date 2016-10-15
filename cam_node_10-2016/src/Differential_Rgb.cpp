
#include "Differential_Rgb.h"

Differential_Rgb::Differential_Rgb(Mat src)
	{
  	    setName(src);
	}

void Differential_Rgb::setName(Mat src)
	{
          

		int lowThreshold=300;
   		int ratio=5;
  		int kernel_size=5;
//converting rgb to differtinal rgb
	
	    split(src, rgbChannels);

// splitting image
	
	    //g = Mat::ones(Size(src.cols, src.rows), CV_8UC1);
	    diff_red=(rgbChannels[2]-rgbChannels[1]);
	    diff_blue=(rgbChannels[0]-rgbChannels[2]); //algorithm implementing for differential rgb.
	    diff_green=(rgbChannels[1]-rgbChannels[0]);
	
	    channels.push_back(diff_blue);
	    channels.push_back(diff_green);
	    channels.push_back(diff_red);
	    merge(channels, new_rgb); // merging image
            
            cvtColor(new_rgb,gray,COLOR_BGR2GRAY);
            blue_channel=rgbChannels[0]-rgbChannels[2];
          
	    extract_blue=blue_channel - gray ;

             erode(extract_blue, extract_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
             dilate( extract_blue,extract_blue, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
            dilate( extract_blue,extract_blue, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
            erode(extract_blue, extract_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
          
            
            //blur(extract_blue,extract_blue, Size(3,3) );
            Canny(extract_blue,threshold_blue, lowThreshold, lowThreshold*ratio, kernel_size );
            //adaptiveThreshold(extract_blue,threshold_blue,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,7,7);	
   	    imshow("thresh",threshold_blue);
     
	}
Mat Differential_Rgb::getNameBlue()
        {
	    return threshold_blue;
        }  
Mat Differential_Rgb::getNameGray()
        {
        return extract_blue;
        }

