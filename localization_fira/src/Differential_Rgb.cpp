
#include "Differential_Rgb.h"

Differential_Rgb::Differential_Rgb(Mat src,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH,double lastz)//constructor
	{
  	    setName(src,rLowH, rHighH, gLowH, gHighH, bLowH, bHighH,lastz);
	}

void Differential_Rgb::setName(Mat src,int rLowH,int rHighH,int gLowH,int gHighH,int bLowH,int bHighH,double lastz)
	{

		int lowThreshold=50;
   		int ratio=3;
  		int kernel_size=3;
                
	
//converting rgb to differtinal rgb
	
	    split(src, rgbChannels);

// splitting image
	
	    g = Mat::ones(Size(src.cols, src.rows), CV_8UC1);
	    diff_red=(rgbChannels[2]-rgbChannels[1])+g ;
	    diff_blue=(rgbChannels[0]-rgbChannels[2])+g; //algorithm implementing for differential rgb.
	    diff_green=(rgbChannels[1]-rgbChannels[0])+g ;
	
	    channels.push_back(diff_blue);
	    channels.push_back(diff_green);
	    channels.push_back(diff_red);
	    merge(channels, new_rgb); // merging image
            int low=170;
	   
           // cvtColor(new_rgb,gray,COLOR_BGR2GRAY);		          
            cvtColor(src,gray_src,COLOR_BGR2GRAY); 
             imshow("gray",gray_src);    
            gray_src=gray_src > low;  
           extract_blue_th=diff_blue >bLowH & diff_blue<bHighH & diff_green>gLowH & diff_green <gHighH & diff_red>rLowH & diff_red <rHighH;
           extract_blue= extract_blue_th-gray; 
           // imshow("extract_b",extract_blue);
           // blur(extract_blue, extract_blue, Size(3,3) );
	   threshold(extract_blue, extract_blue,0,255, CV_THRESH_BINARY | CV_THRESH_OTSU);
      
	    erode(extract_blue, extract_blue, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
            dilate(extract_blue,extract_blue, getStructuringElement(MORPH_ELLIPSE,Size(3, 3)) );
            dilate(extract_blue,extract_blue, getStructuringElement(MORPH_ELLIPSE,Size(3, 3)) );
            erode(extract_blue,extract_blue, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );                    
           
           imshow("extract",extract_blue);
           
	   threshold(gray_src, threshold_ostu,0,255, CV_THRESH_BINARY | CV_THRESH_OTSU);
            imshow("ostu",threshold_ostu);

         blur(gray_src,gray_src, Size(3,3) ); 

        if (lastz>1)
           {
        
         Canny(gray_src,threshold_canny, lowThreshold, lowThreshold*ratio, kernel_size );
           flag=1;
            }
        else 
           
           {
	 lowThreshold=300;
   	 ratio=5;
  	 kernel_size=5;
             
         Canny(extract_blue,threshold_canny, lowThreshold, lowThreshold*ratio, kernel_size );
            flag=2;
            }

         //cv::adaptiveThreshold(gray_src,threshold_blue,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,7,7);
   	 imshow("canny",threshold_canny);
     
	}
Mat Differential_Rgb::getNameCanny()
        {
	    return threshold_canny;
        }  
Mat Differential_Rgb::getNameOstu()
        {
              if (flag==1)
                 return threshold_ostu;
              else if (flag==2)
                 return extract_blue_th;
        }
Mat Differential_Rgb::getNameGraySrc()
	{
	return gray_src;	
	}
int Differential_Rgb::getflag()
       {
       return flag;
       }
 

