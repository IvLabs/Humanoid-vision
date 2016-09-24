



#include "Pose.h"


Pose::Pose()
    {
        
        objectPoints.push_back(cv::Point3f(-90.0f,90.0f,0.0f));
	objectPoints.push_back(cv::Point3f(-90.0f,-90.0f,0.0f));
 	objectPoints.push_back(cv::Point3f(90.0f,-90.0f,0.0f));
  	objectPoints.push_back(cv::Point3f(90.0f,90.0f,0.0f));
  	

       
        cameraIntrinsicParams=Mat(Size(3,3),CV_32FC1);
      
   
        cameraIntrinsicParams.at<float>(0,0)= 694.507824f;
	cameraIntrinsicParams.at<float>(0,1)= 0 ;
	cameraIntrinsicParams.at<float>(0,2)= 329.707540f;
	cameraIntrinsicParams.at<float>(1,0)= 0 ;
	cameraIntrinsicParams.at<float>(1,1)= 694.579263f;
	cameraIntrinsicParams.at<float>(1,2)= 260.350615f;
	cameraIntrinsicParams.at<float>(2,0)= 0 ;
	cameraIntrinsicParams.at<float>(2,1)= 0 ;
	cameraIntrinsicParams.at<float>(2,2)= 1 ;

      
     //  distCoeffs=Mat::zeros(Size(5,1),CV_32FC1);
     distCoeffs=Mat(Size(1,5),CV_32FC1);
       distCoeffs.at<float>(0,0)=0.015950f;
       distCoeffs.at<float>(0,1)=-0.224494f;
       distCoeffs.at<float>(0,2)=0.002544f;
       distCoeffs.at<float>(0,3)=0.000194f;
       distCoeffs.at<float>(0,4)=0.0f;

    }

	


double* Pose::contour_detection(Mat threshold, Mat src)
{
   	int flag =0;
   	double largest_area=0.0;
   	int largest_contour_index=0;
   	int lowThreshold=5;
   	int ratio=3;
  	int kernel_size=3;
        int const max_lowThreshold = 100;//100
        static double *location;  
        static double check[]={0.0,0.0,0.0,0.0,0.0,0.0} ;
        int j=0;
        int index[100];
        double area_array[100];  //area array
             
        double d;//distance
        int y=0;//sort
   	vector<Point>Points ;
   	vector< vector<Point> > contours; // Vector for storing contour
   	vector<Vec4i> hierarchy;
   	Mat detected_edges;
   	blur(threshold, detected_edges, Size(3,3) );
       

  /// Canny detector
  	Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
        imshow("canny", detected_edges);
  	vector< vector<Point> > contours0;
        findContours( detected_edges, contours0, hierarchy,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image
	

	contours.resize(contours0.size());
 	std::vector<Point2f> imagePoints;
        std::vector<Point2f> preciseCorners(4);
        
       
        int k=0 ;   
        
        
    	for( k=0; k < contours0.size(); k++ )
        {    
               
                //double eps = contours0[k].size() * 0.07;
		approxPolyDP(contours0[k], contours[k],9, true);
           
                if (contours[k].size() != 4)
		continue;

                if (!cv::isContourConvex(contours[k]))
		continue;
                
                for(int m = 0; m < 4; m++) 
		{
                 d = (double)(contours[k][m].x - contours[k][(m + 1) % 4].x) *(double)(contours[k][m].x - contours[k][(m + 1) % 4].x) +
                       	   (double)(contours[k][m].y - contours[k][(m + 1) % 4].y) *(double)(contours[k][m].y - contours[k][(m + 1) % 4].y);
            
       		}
                if (d < 10)
                continue;
               
                if(contours[k].size()==4)
		{
		
		index[j]=k;
                j=j+1;
                 
		}
                
       }
     
		if (contours0.size()==0)
		{             
		return check;
		}
      
	if(j>1)
	{
                
		
		for( int i = 0; i<j; i++ )
		{           
                    area_array[i]=contourArea( contours[index[i]],false);
		}  
                
               
			 double ratio=area_array[j-1]/area_array[j-3];
			 cout<<"ratio"<<ratio<<endl;

                         	if((ratio> 3.7) && ratio < 4.2 )	
				{
				 
					
			
                                	for (int c=0;c<4;c++)
					{		
					preciseCorners[c] = contours[index[j-1]][c];
					}
         	
                			//cv::cornerSubPix(threshold,preciseCorners, cvSize(8,8),cvSize(-1,-1),  
					//TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
                                     
					cv::cornerSubPix(threshold, preciseCorners, cvSize(8,8),cvSize(-1,-1), 
					cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));
                						
				
                			for (int c=0;c<4;c++)
					{
					contours[index[j-1]][c] = preciseCorners[c];
					}
                         
      					imagePoints.push_back(Point2f(contours[index[j-1]][0].x,contours[index[j-1]][0].y));
    					imagePoints.push_back(Point2f(contours[index[j-1]][1].x,contours[index[j-1]][1].y));
    					imagePoints.push_back(Point2f(contours[index[j-1]][2].x,contours[index[j-1]][2].y));
    					imagePoints.push_back(Point2f(contours[index[j-1]][3].x,contours[index[j-1]][3].y));
		                       
                                        cout<<" X :"<< contours[index[j-1]][0].x <<  " Y : "<< contours[index[j-1]][0].y<<endl;
 					                                           
					 cout<<" X :"<< contours[index[j-1]][1].x <<  " Y : "<< contours[index[j-1]][1].y <<endl;			
					cout<<" X :"<< contours[index[j-1]][2].x <<  " Y : "<< contours[index[j-1]][2].y <<endl;
					cout<<" X :"<< contours[index[j-1]][3].x <<  " Y : "<< contours[index[j-1]][3].y <<endl;		
          				Point P1=contours[index[j-1]][0];
    					Point P2=contours[index[j-1]][1];
    					Point P3=contours[index[j-1]][2];
   					Point P4=contours[index[j-1]][3];

    					line(src,P1,P2, Scalar(0,0,255),2,CV_AA,0);
			    		line(src,P2,P3, Scalar(0,0,255),2,CV_AA,0);
    					line(src,P3,P4, Scalar(0,0,255),2,CV_AA,0);
    					line(src,P4,P1, Scalar(0,0,255),2,CV_AA,0);
                
               				location=pose_estimation(objectPoints,imagePoints);
                                        
					return location;  
                		}
                                           		              
        }   		

return check;		
	            
}

double* Pose::pose_estimation(const std::vector<cv::Point3f> &objectPoints,const std::vector<cv::Point2f> &imagePoints)
{
       
        static double position[6];
	 
        Mat rvec,tvec,inliers;
       //rvec=Mat::zeros(3,1,CV_64FC1);
       //tvec=Mat::zeros(3,1,CV_64FC1);
    
            
 	bool useExtrinsicGuess =false; 
 	
        int method = CV_ITERATIVE ;
	
       cv::solvePnP(objectPoints,imagePoints, cameraIntrinsicParams,distCoeffs,rvec, tvec,useExtrinsicGuess,method);
       /*int iterationsCount = 500;        // number of Ransac iterations.
    	float reprojectionError = 2.0;    // maximum allowed distance to consider it an inlier.
    	float confidence = 0.95;          // ransac successful confidence.
    	int flags=0;
	cv::solvePnPRansac( objectPoints, imagePoints,cameraIntrinsicParams,distCoeffs,rvec,tvec,
                            useExtrinsicGuess, iterationsCount, reprojectionError, confidence,
                        inliers, flags );
  */
        Mat distant=Mat(Size(3,3),CV_64FC1);
     	Mat jacobian=Mat(Size(3,1),CV_32FC1);

	Rodrigues(rvec,distant,jacobian);
      
        Mat J;
	vector<Point2f> p(4);
	projectPoints(objectPoints,rvec,tvec, cameraIntrinsicParams, distCoeffs, p, J);

        float sum = 0.;
  	for (size_t i = 0; i <p.size(); i++)
         {
          sum += sqrt((p[i].x - imagePoints[i].x)* (p[i].x - imagePoints[i].x)+(p[i].y - imagePoints[i].y)* (p[i].y - imagePoints[i].y));
         }
       
        

        Mat R= distant.t(); 
    	
     	
               Mat T = -R * tvec ;
               
               
               cout << "error =" << sum << endl;
              
               position[0] =T.at<double>(0,0);
               position[1]=T.at<double>(1,0);
               position[2]=T.at<double>(2,0);
               position[3] = ((atan2(-R.at<double>(2,1), R.at<double>(2,2)))*180)/3.142;  //roll
	       position[4] = ((asin(R.at<double>(2,0)))*180)/3.142;                       //pitch
	       position[5] = ((atan2(-R.at<double>(1,0), R.at<double>(0,0)))*180)/3.142;   //yaw
	       return position;
                        
        
}






