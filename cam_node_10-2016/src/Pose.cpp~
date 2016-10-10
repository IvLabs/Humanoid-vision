



#include "Pose.h"


Pose::Pose()
    {
        
        objectPoints.push_back(cv::Point3f( 0.0f,98.9949f,0.0f));
	objectPoints.push_back(cv::Point3f(-98.9949f,0.0f,0.0f));
 	objectPoints.push_back(cv::Point3f(0.0f,-98.9949f,0.0f));
  	objectPoints.push_back(cv::Point3f(98.9949f,0.0f,0.0f));
  

       
        cameraIntrinsicParams=Mat(Size(3,3),CV_32FC1);
      
   
        cameraIntrinsicParams.at<float>(0,0)=753.260710;
	cameraIntrinsicParams.at<float>(0,1)= 0.0;
	cameraIntrinsicParams.at<float>(0,2)= 315.638910;
	cameraIntrinsicParams.at<float>(1,0)= 0 ;
	cameraIntrinsicParams.at<float>(1,1)= 755.173740;
	cameraIntrinsicParams.at<float>(1,2)= 268.190620;
	cameraIntrinsicParams.at<float>(2,0)= 0.0 ;
	cameraIntrinsicParams.at<float>(2,1)= 0.0 ;
	cameraIntrinsicParams.at<float>(2,2)= 1.0 ;

      
    //distCoeffs=Mat::zeros(Size(1,5),CV_32FC1);
      distCoeffs=Mat(Size(1,5),CV_32FC1);
       distCoeffs.at<float>(0,0)=0.030688;
       distCoeffs.at<float>(0,1)=-0.214494;
       distCoeffs.at<float>(0,2)=0.003791;
       distCoeffs.at<float>(0,3)=-0.004887;
       distCoeffs.at<float>(0,4)=0.000000;

    }



double* Pose::contour_detection(Mat threshold,Mat threshold_id , Mat src)
{
   	int flag =0;
   	double largest_area=0.0;
   	int largest_contour_index=0;
        static double *location;  
        static double check[]={0.0,0.0,0.0,0.0,0.0,0.0} ;
        int j=0;
        int index[100];
        double area_array[100];  //area array
        int sum = 0;    
        double d;//distance
        int y=0;//sort
       int q=0;
   	vector<Point>Points ;
   	vector< vector<Point> > contours; // Vector for storing contour
   	vector<Vec4i> hierarchy;
  	vector< vector<Point> > contours0;
        findContours( threshold, contours0, hierarchy,CV_RETR_LIST,CV_CHAIN_APPROX_NONE); // Find the contours in the image
	

	contours.resize(contours0.size());
 	std::vector<Point2f> imagePoints;
        std::vector<Point2f> preciseCorners(4);
      
        
      
        int k=0 ;   
        
        cout<<" size :"<<contours0.size()<<endl;
    	for( k=0; k < contours0.size(); k++ )
        {    
               
              //  double eps = contours0[k].size() * 0.05; 
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

		
    	/*	for (unsigned int i = 0; i < contours[index[k]].size(); i++) 
		{

       		 int i2 = (i + 1) % contours[index[k]].size();
		 sum += sqrt((contours[index[k]][i].x - contours[index[k]][i2].x) * (contours[index[k]][i].x - contours[index[k]][i2].x) +(contours[index[k]][i].y - contours[index[k]][i2].y) * (contours[index[k]][i].y - contours[index[k]][i2].y));
  			
		 }
              
		if(sum < 100)
                continue;
          */    
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
      cout<<"j :"<<j<<endl;
/*	if(j>1)
	{
               Point2f quad_pts[4];
    	               Point2f squre_pts[4];
		if(p>=0)
		{          
                        cout<< "a"<<endl;
                       
                        cout<<"b"<<endl;         
                	Rect boundRect=boundingRect(contours[index[p]]);
	
                	quad_pts[0]=Point(contours[index[p]][0].x,contours[index[p]][0].y);
    			quad_pts[1]=Point(contours[index[p]][1].x,contours[index[p]][1].y);
    			quad_pts[2]=Point(contours[index[p]][2].x,contours[index[p]][2].y);
    			quad_pts[3]=Point(contours[index[p]][3].x,contours[index[p]][3].y); 
                        cout<<"c"<<endl;
                	squre_pts[0]=Point(boundRect.x,boundRect.y);
                        squre_pts[1]=Point(boundRect.x,boundRect.y+boundRect.height);
                        squre_pts[2]=Point(boundRect.x+boundRect.width,boundRect.y+boundRect.height);
                	squre_pts[3]=Point(boundRect.x+boundRect.width,boundRect.y);
                	
   			
    		 cout<<""<<endl;
               Mat transmtx = getPerspectiveTransform(quad_pts,squre_pts);  
              
    		 Mat transformed = Mat::zeros(threshold_id.rows, threshold_id.cols, CV_8UC1);	
 		warpPerspective(threshold_id, transformed, transmtx, threshold_id.size());               
                rectangle(transformed,boundRect,Scalar(0,255,0),1,8,0);
                //imshow("trsanformed",transformed);
                
		Mat marker=transformed(boundRect);
              // imshow("Marker",marker);
               




  
                for(int p = j-1;p>=0;p--)
		{
		
		Mat marker=threshold(Rect(Point(contours[index[p]][0].x,contours[index[p]][0].y),Point(contours[index[p]][2].x,contours[index[p]][2].y)));
		

		cv::Mat bitMatrix = cv::Mat::zeros(4,4,CV_8UC1);
                      
              int width = marker.cols / 4;
	      int height = marker.rows / 4;
              Mat cell;

		for(int y=0; y<=(marker.rows - height); y+=height)
		{
    			for(int x=0; x<=(marker.cols - width); x+=width)
   			 {
        			
				cell = marker(Rect(x, y, width, height));
        			int nZ = cv::countNonZero(cell);
				if (nZ> (width * height)/1.5)
				bitMatrix.at<uchar>(y,x) = 1;       			              
                                cout<<"bit Matrix "<<int(bitMatrix.at<uchar>(y,x))<<endl;
  			 }
		}


              			if(int(bitMatrix.at<uchar>(0,0)) == 1 && int(bitMatrix.at<uchar>(1,1)) == 0 && int(bitMatrix.at<uchar>(2,2)) == 0 && int(bitMatrix.at<uchar>(3,3)) == 1 )

             			 {

		
                                	for (int c=0;c<4;c++)
					{		
					preciseCorners[c] = contours[index[p]][c];
					}
         	
                			//cv::cornerSubPix(threshold,preciseCorners, cvSize(15,15),cvSize(-1,-1),  
					//TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
                                     
					cv::cornerSubPix(threshold, preciseCorners, cvSize(8,8),cvSize(-1,-1), 
					cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));
                						
				
                			for (int c=0;c<4;c++)
					{
					contours[index[p]][c] = preciseCorners[c];
					}
                         
      					imagePoints.push_back(Point2f(contours[index[p]][0].x,contours[index[p]][0].y));
    					imagePoints.push_back(Point2f(contours[index[p]][1].x,contours[index[p]][1].y));
    					imagePoints.push_back(Point2f(contours[index[p]][2].x,contours[index[p]][2].y));
    					imagePoints.push_back(Point2f(contours[index[p]][3].x,contours[index[p]][3].y));
		                       
                                       
          				Point P1=contours[index[p]][0];
    					Point P2=contours[index[p]][1];
    					Point P3=contours[index[p]][2];
   					Point P4=contours[index[p]][3];

    					line(src,P1,P2, Scalar(0,0,255),0,CV_AA,0);
			    		line(src,P2,P3, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P3,P4, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P4,P1, Scalar(0,0,255),0,CV_AA,0);
                
               				location=pose_estimation(objectPoints,imagePoints);
                                        
					return location;  
                		}
                     p=p-1;                      		              
        	}	   	
	
	}
*/

if(j>2)
	{
                
		
		for( int i = 0; i<j; i++ )
		{           
                    area_array[i]=contourArea( contours[index[i]],false);
                  
		}  
                
               for (int s=1 ; s < j ; s++)
                      
		{
                  
	              for (int r=s; r<=j-1; r++)
                        
                         {
                        
			 double ratio=area_array[j-s]/area_array[j-(r+1)];
                          
                            
                         	if((ratio> 3.8) && ratio < 4.3 )	
				{
				 
				   q=j-s;	
			
                                	for (int c=0;c<4;c++)
					{		
					preciseCorners[c] = contours[index[q]][c];
					}
         	
                			//cv::cornerSubPix(threshold,preciseCorners, cvSize(8,8),cvSize(-1,-1),  
					//TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
                                     
					cv::cornerSubPix(threshold, preciseCorners, cvSize(5,5),cvSize(-1,-1), 
					cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));
                						
				
                			for (int c=0;c<4;c++)
					{
					contours[index[q]][c] = preciseCorners[c];
					}
                         
      					imagePoints.push_back(Point2f(contours[index[q]][0].x,contours[index[q]][0].y));
    					imagePoints.push_back(Point2f(contours[index[q]][1].x,contours[index[q]][1].y));
    					imagePoints.push_back(Point2f(contours[index[q]][2].x,contours[index[q]][2].y));
    					imagePoints.push_back(Point2f(contours[index[q]][3].x,contours[index[q]][3].y));
		                       
                                        cout<<" X :"<< contours[index[q]][0].x <<  " Y : "<< contours[index[q]][0].y<<endl;
 					                                           
				   cout<<" X :"<< contours[index[q]][1].x <<  " Y : "<< contours[index[q]][1].y <<endl;			
					cout<<" X :"<< contours[index[q]][2].x <<  " Y : "<< contours[index[q]][2].y <<endl;
					cout<<" X :"<< contours[index[q]][3].x <<  " Y : "<< contours[index[q]][3].y <<endl;		
          				Point P1=contours[index[q]][0];
    					Point P2=contours[index[q]][1];
    					Point P3=contours[index[q]][2];
   					Point P4=contours[index[q]][3];

    					line(src,P1,P2, Scalar(0,0,255),0,CV_AA,0);
			    		line(src,P2,P3, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P3,P4, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P4,P1, Scalar(0,0,255),0,CV_AA,0);
                
               				location=pose_estimation(objectPoints,imagePoints);
                                        
					return location;  
                		}

			}
		}	
                                           		              
        }   		

return check;		
	            
}

double* Pose::pose_estimation(const std::vector<cv::Point3f> &objectPoints,const std::vector<cv::Point2f> &imagePoints)
{
       
        static double position[6];
	 
        Mat rvec,tvec,inliers;
	bool useExtrinsicGuess =false; 
        int method = CV_ITERATIVE ;
	
 cv::solvePnP(objectPoints,imagePoints, cameraIntrinsicParams,distCoeffs,rvec, tvec,useExtrinsicGuess,method);
/* int iterationsCount = 500;        // number of Ransac iterations.
   	float reprojectionError = 8;    // maximum allowed distance to consider it an inlier.
    	float confidence = 0.95;          // ransac successful confidence.
    	int flags=0;
	cv::solvePnPRansac( objectPoints, imagePoints,cameraIntrinsicParams,distCoeffs,rvec,tvec,
                            useExtrinsicGuess, iterationsCount, reprojectionError, confidence,
                        inliers, flags );
  */
      Mat distant=Mat(Size(3,3),CV_64FC1);
     	Mat jacobian=Mat(Size(3,1),CV_64FC1);

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






