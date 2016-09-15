



#include "Pose.h"


Pose::Pose()
    {
       
	objectPoints.push_back(cv::Point3f(240.f,680.f,715.f));
 	objectPoints.push_back(cv::Point3f(240.f,680.f,215.f));
  	objectPoints.push_back(cv::Point3f(615.f,680.f,215.f));
  	objectPoints.push_back(cv::Point3f(615.f,680.f,715.f));

       
        cameraIntrinsicParams=Mat(Size(3,3),CV_32FC1);
      
   
        cameraIntrinsicParams.at<float>(0,0)=  727.957294f;
	cameraIntrinsicParams.at<float>(0,1)= 0 ;
	cameraIntrinsicParams.at<float>(0,2)= 320.f;//304.729528f;
	cameraIntrinsicParams.at<float>(1,0)= 0 ;
	cameraIntrinsicParams.at<float>(1,1)=  726.232798f;
	cameraIntrinsicParams.at<float>(1,2)= 240.f;//235.217420f;
	cameraIntrinsicParams.at<float>(2,0)= 0 ;
	cameraIntrinsicParams.at<float>(2,1)= 0 ;
	cameraIntrinsicParams.at<float>(2,2)= 1 ;

      
       distCoeffs=Mat::zeros(Size(4,1),CV_64FC1);
    
       	         
    }

double* Pose::contour_detection(Mat threshold, Mat src)
{
   	int flag =0;
   	double largest_area=0.0;
   	int largest_contour_index=0;
   	int lowThreshold;
   	int ratio=3;
  	int kernel_size=3;
        int const max_lowThreshold = 100;
        double *location;
        static double *ptr=NULL;
       static double check[3]={0.0,0.0,0.0};
        //double *condition;
   	Mat dst(src.rows,src.cols,CV_8UC1,Scalar::all(0));
   	Rect bounding_rect;
   	RotatedRect box;
   	vector<Point>Points ;
   	vector< vector<Point> > contours; // Vector for storing contour
   	vector<Vec4i> hierarchy;
   	Mat detected_edges;
   	blur(threshold, detected_edges, Size(3,3) );

  /// Canny detector
  	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
  	vector< vector<Point> > contours0;
        findContours( detected_edges, contours0, hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image
	

	contours.resize(contours0.size());
 	std::vector<Point2f> imagePoints;
        std::vector<Point2f> preciseCorners(4);
        int k=0 ;
      
    	for( ; k < contours0.size(); k++ )
        {
      
          double a=contourArea( contours0[k],false); // Find the area of contour
		if(a>largest_area)
	        {
 		largest_area=a;
    		largest_contour_index=k ;
                
		}	
        }

		if (contours0.size()==0)
		{
		return check;
		}
       
    
        	approxPolyDP(contours0[largest_contour_index], contours[largest_contour_index],9, true);
                
                if(contours[largest_contour_index].size()==4)
                {
                 
 		  
                for (int c=0;c<4;c++)
		{		
		preciseCorners[c] = contours[largest_contour_index][c];
		}
         	
                 cv::cornerSubPix(threshold, preciseCorners, cvSize(5,5),cvSize(-1,-1),  TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
              //  cv::cornerSubPix(threshold, preciseCorners, cvSize(5,5),cvSize(-1,-1), cvTermCriteria(CV_TERMCRIT_ITER,30,0.1));
                
                for (int c=0;c<4;c++)
		{
		contours[largest_contour_index][c] = preciseCorners[c];
		}

                imagePoints.push_back(Point2f(contours[largest_contour_index][0].x,contours[largest_contour_index][0].y));
    		imagePoints.push_back(Point2f(contours[largest_contour_index][1].x,contours[largest_contour_index][1].y));
    		imagePoints.push_back(Point2f(contours[largest_contour_index][2].x,contours[largest_contour_index][2].y));
    		imagePoints.push_back(Point2f(contours[largest_contour_index][3].x,contours[largest_contour_index][3].y));

             	Point P1=contours[largest_contour_index][0];
    		Point P2=contours[largest_contour_index][1];
    		Point P3=contours[largest_contour_index][2];
    		Point P4=contours[largest_contour_index][3];


    		line(src,P1,P2, Scalar(0,255,0),1,CV_AA,0);
    		line(src,P2,P3, Scalar(0,255,0),1,CV_AA,0);
    		line(src,P3,P4, Scalar(0,255,0),1,CV_AA,0);
    		line(src,P4,P1, Scalar(0,255,0),1,CV_AA,0);
                location=pose_estimation(objectPoints,imagePoints);
                
          	}

		else
		{
		return check;
		}
   
        	
      
	// Pose estimation. 

		
return location;		
	        
	        

	        

}

double* Pose::pose_estimation(const std::vector<cv::Point3f> &objectPoints,const std::vector<cv::Point2f> &imagePoints)
{
       
        static double position[4];
	
        Mat rvec,tvec;
        rvec=Mat::zeros(3,1,CV_64FC1);
        tvec=Mat::zeros(3,1,CV_64FC1);
      
            
 	bool useExtrinsicGuess = true; 
 	
        int method =CV_ITERATIVE;
        cv::solvePnP(objectPoints,imagePoints, cameraIntrinsicParams, distCoeffs,rvec, tvec,useExtrinsicGuess,method);
       
        Mat distant=Mat(Size(3,3),CV_64FC1);
     	Mat jacobian=Mat(Size(3,1),CV_32FC1);
	Rodrigues(rvec,distant,jacobian);
      
        Mat J;
	vector<Point2f> p(4);
	projectPoints(objectPoints,rvec,tvec, cameraIntrinsicParams,  distCoeffs, p, J);

        float sum = 0.;
  	for (size_t i = 0; i <p.size(); i++)
         {
          sum += sqrt((p[i].x - imagePoints[i].x)* (p[i].x - imagePoints[i].x)+(p[i].y - imagePoints[i].y)* (p[i].y - imagePoints[i].y));
         }
       
        

        Mat R= distant.t(); 
    	
     	cout<<""<<endl;

               if (sum < 30)
               {
               cout << "sum=" << sum << endl;
               Mat T = -R * tvec ;
               position[0] =T.at<double>(0,0);
               position[1]=T.at<double>(1,0);
               position[2]=T.at<double>(2,0);
               }         
        return position;
}

	







