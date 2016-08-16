

#include "Differential_Rgb.h"

Differential_Rgb::Differential_Rgb(Mat src)
	{
  	    setName(src);
	}

void Differential_Rgb::setName(Mat src)
	{
          
//converting rgb to differtinal rgb
	
	    split(src, rgbChannels);

// splitting image
	
	    g = Mat::ones(Size(src.cols, src.rows), CV_8UC1);
	    diff_red=(rgbChannels[2]-rgbChannels[1])+g;
	    diff_blue=(rgbChannels[0]-rgbChannels[2])+g; //algorithm implementing for differential rgb.
	    diff_green=(rgbChannels[1]-rgbChannels[0])+g;
	
	    channels.push_back(diff_blue);
	    channels.push_back(diff_green);
	    channels.push_back(diff_red);
	    merge(channels, new_rgb); // merging image
            
            cvtColor(new_rgb,gray,COLOR_BGR2GRAY);
	}
Mat Differential_Rgb::getNameBlue()
        {
	    return diff_blue;
        }
Mat Differential_Rgb::getNameGreen()
        {
	    return diff_green;
        }
Mat Differential_Rgb::getNameRed()
        {
	    return diff_red;
        }
Mat Differential_Rgb::getNameGray()
        {
        return gray;
        }

