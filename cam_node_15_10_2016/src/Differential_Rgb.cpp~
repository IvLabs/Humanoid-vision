
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
                int rLowH = 0;
	int rHighH = 25;
	int gLowH = 0;
	int gHighH = 25;
	int bLowH = 45;
	int bHighH = 150;
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
            
	    blur(new_rgb,new_rgb, Size(3,3) );
            cvtColor(new_rgb,gray,COLOR_BGR2GRAY);  
            cvtColor(src,gray_src,COLOR_BGR2GRAY); 
          // imshow("gray_src",gray_src);        
            extract_blue=diff_blue >bLowH & diff_blue<bHighH & diff_green>gLowH & diff_green <gHighH & diff_red>rLowH & diff_red <rHighH;
	    extract_blue=diff_blue -gray ;

            erode(extract_blue, extract_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            dilate(extract_blue,extract_blue, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
            dilate(extract_blue,extract_blue, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
            erode(extract_blue,extract_blue, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
           //imshow("extract",extract_blue);
           
            blur(extract_blue,extract_blue, Size(3,3) );
  
           Canny(extract_blue,threshold_blue, lowThreshold, lowThreshold*ratio, kernel_size );
          
   	    imshow("canny",threshold_blue);
     
	}
Mat Differential_Rgb::getNameBlue()
        {
	    return threshold_blue;
        }  
Mat Differential_Rgb::getNameGray()
        {
        return extract_blue;
        }
Mat Differential_Rgb::getNameGraySrc()
	{
	return gray_src;	
	}
