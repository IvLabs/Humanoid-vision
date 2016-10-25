



#include "Pose.h"


Pose::Pose(int flag)
    {
        if (flag==1) 
        {
        // world points for orientaion II quad anticlockwise 
        // points for 45 degree inclination 
        objectPoints1.push_back(cv::Point3f(-0.100f,0.0707106f,-0.0707106f));
	objectPoints1.push_back(cv::Point3f(-0.100f,-0.0707106f,0.0707106f));
 	objectPoints1.push_back(cv::Point3f(0.100f,-0.0707106f,0.0707106f));
  	objectPoints1.push_back(cv::Point3f(0.100f,0.0707106f,-0.0707106f));
  
        objectPoints2.push_back(cv::Point3f( 0.100f,0.0707106f,-0.0707106f));
	objectPoints2.push_back(cv::Point3f(-0.100f,0.0707106f,-0.0707106f));
 	objectPoints2.push_back(cv::Point3f(-0.100f,-0.0707106f,0.0707106f));
  	objectPoints2.push_back(cv::Point3f(0.100f,-0.0707106f,0.0707106f));

       

        }

        else{
         // world points for orientaion I quad anticlockwise 
         // points for 45 degree inclination 
        objectPoints1.push_back(cv::Point3f( -0.050f,0.0353553f,-0.0353553f));
	objectPoints1.push_back(cv::Point3f(-0.050f,-0.0353553f,0.0353553f));
 	objectPoints1.push_back(cv::Point3f(0.050f,-0.0353553f,0.0353553f));
  	objectPoints1.push_back(cv::Point3f(0.050f,0.0353553f,-0.0353553f));
  
        objectPoints2.push_back(cv::Point3f( 0.050f,0.0353553f,-0.0353553f));
	objectPoints2.push_back(cv::Point3f(-0.050f,0.0353553f,-0.0353553f));
 	objectPoints2.push_back(cv::Point3f(-0.050f,-0.0353553f,0.0353553f));
  	objectPoints2.push_back(cv::Point3f(0.050f,-0.0353553f,0.0353553f));

       }
        cameraIntrinsicParams=Mat(Size(3,3),CV_64FC1);
        // camera parameters 
        cameraIntrinsicParams.at<double>(0,0)= 733.0519551883676;
	cameraIntrinsicParams.at<double>(0,1)= 0.0;
	cameraIntrinsicParams.at<double>(0,2)= 308.59827311435;
	cameraIntrinsicParams.at<double>(1,0)= 0 ;
	cameraIntrinsicParams.at<double>(1,1)= 735.1820471505564;
	cameraIntrinsicParams.at<double>(1,2)= 228.4401120706685;
	cameraIntrinsicParams.at<double>(2,0)= 0.0 ;
	cameraIntrinsicParams.at<double>(2,1)= 0.0 ;
	cameraIntrinsicParams.at<double>(2,2)= 1.0 ;

     
//    distCoeffs=Mat::zeros(Size(1,5),CV_32FC1);
       // distortion coefficients
       distCoeffs=Mat(Size(1,5),CV_64FC1);
       distCoeffs.at<double>(0,0)=0.05473006817446581;
       distCoeffs.at<double>(0,1)=-0.4169723577175724;
       distCoeffs.at<double>(0,2)=0.0002363503817115325;
       distCoeffs.at<double>(0,3)=0.002502402742858189;
       distCoeffs.at<double>(0,4)=0.000000;

       
 
    }



double* Pose::contour_detection(Mat threshold_canny,Mat threshold_ostu ,Mat gray_src, Mat src,int *blue_centroid)
{
   	int flag =0;
   	double largest_area=0.0;  // largest area vaiable
   	int largest_contour_index=0;// largest contour index variable
        static double *location;  // return pose pointer 
        static double check[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0} ;//null array for black image
        int j=0;
        int index[500];//storing selected contours index
        double area_array[500];  //storing selected contours areas 
        int sum = 0;    
        double d;//distance
        int y=0;//sort
       	int q=0; // contour index passing all test
       
   	vector<Point>Points ;// for storing image points	
   	vector<Vec4i> hierarchy1;//hierarchy of contours
        vector< vector<Point> > contours; // Vector for storing selected contour
  	vector< vector<Point> > contours0;// Vector for storing original contour
     
        
       	Point2f quad_pts[4]; // image points for wrapping
    	Point2f squre_pts[4];// bounding rect co-ordinates
        findContours( threshold_canny, contours0, hierarchy1,CV_RETR_LIST,CV_CHAIN_APPROX_NONE); // Find the contours in the image
	

	contours.resize(contours0.size()); // size should be same for transfering conoturs *** after removing gives segementation fault
       
 	std::vector<Point2f> imagePoints; // vector for storing image points 
        std::vector<Point2f> preciseCorners(4);// vector for storing precise corners
      
        
      
        int k=0 ;   
        
      
    	for( k=0; k < contours0.size(); k++ )
        {    
               
               double eps = contours0[k].size() * 0.05; 
		approxPolyDP(contours0[k], contours[k],eps, true); // approximate the polygons 
          
              if (contours[k].size() != 4)            // 1st test must have 4 corners
		continue;

                if (!cv::isContourConvex(contours[k])) // 2nd test not to be convex
		continue;
                
                for(int m = 0; m < 4; m++)  
		{
                 d = (double)(contours[k][m].x - contours[k][(m + 1) % 4].x) *(double)(contours[k][m].x - contours[k][(m + 1) % 4].x) +
                       	   (double)(contours[k][m].y - contours[k][(m + 1) % 4].y) *(double)(contours[k][m].y - contours[k][(m + 1) % 4].y);
            
       		}
                
                if (d < 10)    // 3rd test minimum distance between alternative corners 
                continue;

		
    	/*	for (unsigned int i = 0; i < contours[index[k]].size(); i++) 
		{

       		 int i2 = (i + 1) % contours[index[k]].size();
		 sum += sqrt((contours[index[k]][i].x - contours[index[k]][i2].x) * (contours[index[k]][i].x - contours[index[k]][i2].x) +(contours[index[k]][i].y - contours[index[k]][i2].y) * (contours[index[k]][i].y - contours[index[k]][i2].y));
  			
		 }
              
		if(sum < 100)
                continue;

                // giving segementation fault **** need to check the loop
          */    
                if(contours[k].size()==4)
		{
		
		index[j]=k;            // storing index of contours which passes the test.
                j=j+1;
                 
		}
                
       }
     
		if (contours0.size()==0)
		{  
                         
		return check;
		}

//cout<<"J----"<<j<<endl;    // need to check the canny problem which solved by morphological filtering


//////// attempt to  solve the problem of +- in the pose becoz variation in precise corner ** failed to do that

/*                              	 Mat marker,black ;
                               		if(contours[index[q]].size()==4)	
                              		{
			      		Rect boundRect=boundingRect(contours[index[q]]);

                            		
	                                        if((boundRect.x - 10) >= 0 && (boundRect.y - 10) >= 0 && (boundRect.x + boundRect.width + 20) < threshold.cols && (boundRect.y+ boundRect.height + 20) < threshold.rows)
	                                         {

		              Point A(boundRect.x - 10 ,boundRect.y - 10) ;	
                              Point B(boundRect.x + boundRect.width + 20 ,boundRect.y+  boundRect.height + 20);                                
                              		marker=gray_src(Rect(A,B));
                                        black = Mat::ones(Size(src.cols, src.rows), CV_8UC1);
                                        marker.copyTo(black(Rect(A,B)));
                              //		imshow("marker", black);

			      		//cv::adaptiveThreshold(marker,marker,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,7,7);
            	              
                             		 Canny(marker,marker, lowThreshold, lowThreshold*ratio, kernel_size );
                              		dilate( marker,marker, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
                              		erode(marker,marker, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                                        Canny(black,black, lowThreshold, lowThreshold*ratio, kernel_size );
                              		dilate( black,black, getStructuringElement(MORPH_ELLIPSE,Size(5, 5)) );
                              		erode(black,black, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                                   //     imshow("black",black);
       		                   //     imshow("adaptive",marker);
       		                        findContours( marker, contours1, hierarchy2,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
                                      
                                        findContours(black, contours2, hierarchy3,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
                              
                            	//       cout<<" MARKER SIZE  "<< contours1.size() <<endl;

                                     for(int j=0; j< contours2.size();j++)

                                       {
                                      // area_array[j]=contourArea( contours2[j],false);
                                       
                                       ///cout<<"area contour black : "<< area_array[j]<< endl;
                                       cout<<" corners : "<< contours2[j].size() << endl;
                                       }
				
                            	       for( int i = 0; i<contours1.size(); i++ )
			         	{           
              		     	        area_array[i]=contourArea( contours1[i],false);
                                  	
						if(area_array[i] >largest_area)
	          			 	{
 		  		 		largest_area=area_array[i];
    		  		 		
                                		}
                                 
					//cout<<"area contour marker"<< area_array[i]<< endl;
					} 
                                        
                            
                        
                                         for (int l=0 ;l < contours2.size() ; l++)
					{
					 area_array[l]=contourArea( contours2[l],false);
 
                                        	if (largest_area == area_array[l])
                                           		largest_contour_index=l;
                                  		
					}

					
					// double eps1 = contours2[largest_contour_index].size() * 0.05; 
		                         approxPolyDP(contours2[largest_contour_index], contours2[largest_contour_index],9, true);
                                      
					cout<<" corner "<<contours2[largest_contour_index].size()<<endl;
                                         cout<<"index "<< largest_contour_index<< endl;          


					for (int c=0;c<4;c++)
					{		
					preciseCorners[c] = contours2[largest_contour_index][c];
					}
         	
                			//cv::cornerSubPix(threshold,preciseCorners, cvSize(8,8),cvSize(-1,-1),  
					//TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
                                     
					cv::cornerSubPix(gray_src, preciseCorners, cvSize(5,5),cvSize(-1,-1), 
					cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER,30,0.1));
                					
				      
                			for (int c=0;c<4;c++)
					{
					contours2[largest_contour_index][c] = preciseCorners[c];
					}
                         

                                        
                                       
      					imagePoints.push_back(Point2f(contours2[largest_contour_index][0].x,contours2[largest_contour_index][0].y));
    					imagePoints.push_back(Point2f(contours2[largest_contour_index][1].x,contours2[largest_contour_index][1].y));
    					imagePoints.push_back(Point2f(contours2[largest_contour_index][2].x,contours2[largest_contour_index][2].y));
    					imagePoints.push_back(Point2f(contours2[largest_contour_index][3].x,contours2[largest_contour_index][3].y));
		                       
                                        cout<<" X :"<< contours2[largest_contour_index][0].x <<  " Y : "<< contours2[largest_contour_index][0].y<<endl;
                                      
				        cout<<" X :"<< contours2[largest_contour_index][1].x <<  " Y : "<< contours2[largest_contour_index][1].y <<endl;			
					cout<<" X :"<< contours2[largest_contour_index][2].x <<  " Y : "<< contours2[largest_contour_index][2].y <<endl;
					cout<<" X :"<< contours2[largest_contour_index][3].x <<  " Y : "<< contours2[largest_contour_index][3].y <<endl;		
          				Point P1=contours2[largest_contour_index][0];
    					Point P2=contours2[largest_contour_index][1];
    					Point P3=contours2[largest_contour_index][2];
   					Point P4=contours2[largest_contour_index][3];

                                        

    					line(src,P1,P2, Scalar(0,0,255),0,CV_AA,0);
			    		line(src,P2,P3, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P3,P4, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P4,P1, Scalar(0,0,255),0,CV_AA,0);
                                         
                                      if (P2.y < P4.y)
                                        {
                                        cout<<"wrong"<<endl;
               				location=pose_estimation(objectPoints2,imagePoints); 
                                        return location;
                                        }
				     else 
                                       {

                                        cout<<"correct"<<endl;
					location=pose_estimation(objectPoints1,imagePoints); 
                                        return location;
					}
      
                                
                           
						 }
                                       else     
                                        return check;
                                        
					}
*/					
				
					

/// this works properly 

 

if(j>2)     // marker will have minimum 2 contours 
	{
                
		
		for( int i = 0; i<j; i++ )
		{           
                    area_array[i]=contourArea( contours[index[i]],false);    //// storing all the areas of selected contours
                 
		}  
                
               for (int s=1 ; s < j ; s++)
                      
		{
                  
	              for (int r=s; r<=j-1; r++)
                        
                         {
                        
			 double ratio=area_array[j-s]/area_array[j-(r+1)];    // calculating  ratio 
                           
                          // cout<<"ratio"<< ratio << endl;   
                         	if(ratio>3.5 && ratio <4.5 )	              // checking ratios test
                                 {
			       //  cout<<" area "<< area_array[j-s] << endl;
				// cout<<"ratio"<< ratio << endl;	
                             	 q=j-s;          /// index of passes the ratio test  

         		Rect boundRect=boundingRect(contours[index[q]]);          // calculating the bounding rect 
           // orientation of marker staring from II quadrant              
	                if(contours[index[q]][1].y < contours[index[q]][3].y)                      // image points
                        {
                	quad_pts[0]=Point(contours[index[q]][0].x,contours[index[q]][0].y);
    			quad_pts[1]=Point(contours[index[q]][1].x,contours[index[q]][1].y);
    			quad_pts[2]=Point(contours[index[q]][2].x,contours[index[q]][2].y); 
    			quad_pts[3]=Point(contours[index[q]][3].x,contours[index[q]][3].y); 
                       
                        squre_pts[0]=Point(boundRect.x+boundRect.width,boundRect.y);              // bounding rect points
                	squre_pts[1]=Point(boundRect.x,boundRect.y);
                        squre_pts[2]=Point(boundRect.x,boundRect.y+boundRect.height);
                        squre_pts[3]=Point(boundRect.x+boundRect.width,boundRect.y+boundRect.height);
                	
                	}
         // orientation of marker staring from I quadrant 
                       else
                       {
			quad_pts[0]=Point(contours[index[q]][0].x,contours[index[q]][0].y);
    			quad_pts[1]=Point(contours[index[q]][1].x,contours[index[q]][1].y);        // image points
    			quad_pts[2]=Point(contours[index[q]][2].x,contours[index[q]][2].y);
    			quad_pts[3]=Point(contours[index[q]][3].x,contours[index[q]][3].y); 
                       
                        
                	squre_pts[0]=Point(boundRect.x,boundRect.y);
                        squre_pts[1]=Point(boundRect.x,boundRect.y+boundRect.height);                // bounding rect points
                        squre_pts[2]=Point(boundRect.x+boundRect.width,boundRect.y+boundRect.height);
                	squre_pts[3]=Point(boundRect.x+boundRect.width,boundRect.y);
			}
             		 // transformation and wrapping 
			 Mat transmtx = getPerspectiveTransform(quad_pts,squre_pts);  
            	         Mat transformed = Mat::zeros(threshold_ostu.rows, threshold_ostu.cols,CV_8UC1);	
                         warpPerspective(threshold_ostu, transformed, transmtx, threshold_ostu.size());    // drawing rectange 
                   	 rectangle(transformed,boundRect,Scalar(0,255,0),1,8,0);
                
               		// imshow("trsanformed",transformed);
                
			 Mat marker=transformed(boundRect);   // cropping the marker from transformed thresholded image.
               		 //imshow("Marker",marker);
            
 
    	       		static int bitMatrix[20];	// storing marker id 		                  
             		int width = marker.cols / 4;          // marker width  
	     	 	int height = marker.rows / 4;      // marker height 
              		int count=0;  // index variable
              
             		Mat cell;  // corpped marker 

		for(int y=0; y<=(marker.rows - height); y+=height)          // dividing rectangles 
		{  
    
    			for(int x=0; x<=(marker.cols - width); x+=width)
   			 {
        			
				cell = marker(Rect(x, y, width, height));
                               
        			int nZ = cv::countNonZero(cell);        // countingg nonzero pixels
                                
				if (nZ> (((width * height)/3)*2))         // algo for marker ids 
				bitMatrix[count]=1 ;
                                else 
                                bitMatrix[count]=0;  
                      
                        //  cout<<"matrix "<<bitMatrix[count]<< endl;   			            
                                count++;
                                
  			 }
		}


             if((bitMatrix[0] == 1) && (bitMatrix[1] == 1) && (bitMatrix[2] == 1) && (bitMatrix[3] == 1) && 
               (bitMatrix[4] == 1) && (bitMatrix[5] == 0)&&(bitMatrix[6] == 0)&&(bitMatrix[7] == 1)&&
           (bitMatrix[8] == 1) && (bitMatrix[9] == 0)&&(bitMatrix[10] == 0)&&(bitMatrix[11] == 1)&&
                (bitMatrix[12] == 1)&&(bitMatrix[13] == 1)&&(bitMatrix[14] == 1)&&(bitMatrix[15] == 1))
	     // checking id 
               
                                   {


				    	for (int c=0;c<4;c++)
					{		
					preciseCorners[c] = contours[index[q]][c];     // storing in precise corner array
					}
         	
                			//cv::cornerSubPix(threshold,preciseCorners, cvSize(8,8),cvSize(-1,-1),  
					//TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
                                        // calculating precise corners
					cv::cornerSubPix(gray_src, preciseCorners, cvSize(5,5),cvSize(-1,-1),    
					cvTermCriteria(CV_TERMCRIT_ITER,30,0.1));
                					
				      
                			for (int c=0;c<4;c++)
					{
					contours[index[q]][c] = preciseCorners[c];   // storing precise corner in contours list 
					}
                         

                                        // final image points 
                                       
      					imagePoints.push_back(Point2f(contours[index[q]][0].x,contours[index[q]][0].y));
    					imagePoints.push_back(Point2f(contours[index[q]][1].x,contours[index[q]][1].y));
    					imagePoints.push_back(Point2f(contours[index[q]][2].x,contours[index[q]][2].y));
    					imagePoints.push_back(Point2f(contours[index[q]][3].x,contours[index[q]][3].y));
                                        // printing corner *** esential when pose is fluctating
		                       
 /*                                     cout<<" X :"<< contours[index[q]][0].x <<  " Y : "<< contours[index[q]][0].y<<endl;
 					                                           
				        cout<<" X :"<< contours[index[q]][1].x <<  " Y : "<< contours[index[q]][1].y <<endl;			
					cout<<" X :"<< contours[index[q]][2].x <<  " Y : "<< contours[index[q]][2].y <<endl;
					cout<<" X :"<< contours[index[q]][3].x <<  " Y : "<< contours[index[q]][3].y <<endl;		
   */       				Point P1=contours[index[q]][0];
    					Point P2=contours[index[q]][1];
    					Point P3=contours[index[q]][2];
   					Point P4=contours[index[q]][3];

                                        
                                        // drawing red color rectangle
    					line(src,P1,P2, Scalar(0,0,255),0,CV_AA,0);
			    		line(src,P2,P3, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P3,P4, Scalar(0,0,255),0,CV_AA,0);
    					line(src,P4,P1, Scalar(0,0,255),0,CV_AA,0);
                                         
                                      if (P2.y < P4.y)      // orientaion strating I quad 
                                        {
                                        //cout<<"wrong"<<endl;
               				location=pose_estimation(objectPoints2,imagePoints,blue_centroid); 
                                        return location;
                                        }
				     else 
                                       {
 					// orientaion strating II quad 
                                        //cout<<"correct"<<endl;
					location=pose_estimation(objectPoints1,imagePoints,blue_centroid); 
                                        return location;
					} 
 					
                                 }
	        		}

			}
		}	
                                           		              
        }   		

return check;	// null pose for empty image.	
	            
}

double* Pose::pose_estimation(const std::vector<cv::Point3f> &objectPoints,const std::vector<cv::Point2f> &imagePoints,int *blue_centroid)
{
       
        static double position[8];  // pose storing array
        double imgcentroidx= 308.0; 
        double imgcentroidy= 228.0;
   	double focallength=733.0;
	static double check[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0} ;
       Mat rvec,tvec,inliers;
/*cv::Mat_<double> rvec(cv::Size(3, 1));
    cv::Mat_<double> tvec(cv::Size(3, 1));
    rvec=0.0f;
    tvec=0.0f;
*/	bool useExtrinsicGuess =false; 
        int method = CV_ITERATIVE ;
	
cv::solvePnP(objectPoints,imagePoints, cameraIntrinsicParams,distCoeffs,rvec, tvec,useExtrinsicGuess,method);//distCoeffs
/* int iterationsCount = 500;        // number of Ransac iterations.
   	float reprojectionError = 8;    // maximum allowed distance to consider it an inlier.
    	float confidence = 0.95;          // ransac successful confidence.
    	int flags=0;
	cv::solvePnPRansac( objectPoints, imagePoints,cameraIntrinsicParams,distCoeffs,rvec,tvec,
                            useExtrinsicGuess, iterationsCount, reprojectionError, confidence,
                        inliers, flags );
 */
 /*for(int i=0 ; i <3 ; i++)
       {
        cout<<" rvec["<< i << "] : " << rvec.at<double>(i,0) << endl;
        cout<<" tvec["<< i << "] : " << tvec.at<double>(i,0) << endl;
       }  
   */   
      
        Mat J;
	vector<Point2f> p(3);
	projectPoints(objectPoints,rvec,tvec, cameraIntrinsicParams,distCoeffs, p, J);//distCoeffs
        float sum = 0.;
  	for (size_t i = 0; i <p.size(); i++)
         {
          sum += ((p[i].x - imagePoints[i].x)* (p[i].x - imagePoints[i].x)+(p[i].y - imagePoints[i].y)* (p[i].y - imagePoints[i].y));
         }
       
        Mat Sigma = Mat(J.t() * J, Rect(0,0,6,6)).inv();

// Compute standard deviation
	Mat std_dev;
	sqrt(Sigma.diag(), std_dev);
	//cout << "rvec, tvec standard deviation:" << endl << std_dev << endl;
 
   /*  for(int i =0;i<3 ;i++)
        {
        rvec.at<double>(i,0)=rvec.at<double>(i,0) - std_dev.at<double>(0,i) ;
        tvec.at<double>(i,0)=tvec.at<double>(i,0) - std_dev.at<double>(0,i+3) ;
       }
*/

       Mat distant=Mat(Size(3,3),CV_64FC1);
     	Mat jacobian=Mat(Size(3,1),CV_64FC1);

	Rodrigues(rvec,distant,jacobian);
        Mat R= distant.t(); 
    	
     	
               Mat T = -R * tvec ;
               
               
              
              
               position[0] =T.at<double>(0,0);  // x 
               position[1]=T.at<double>(1,0);   // y
               position[2]=T.at<double>(2,0);   // z 
               position[3] = ((atan2(-R.at<double>(2,1), R.at<double>(2,2)))*180)/3.142;  //roll
	       position[4] = ((asin(R.at<double>(2,0)))*180)/3.142;                       //pitch
	       position[5] = ((atan2(-R.at<double>(1,0), R.at<double>(0,0)))*180)/3.142;   //yaw


               if (position[2] >0  ) 
               {
                 cout << "error =" << sum << endl;
        	double imgdistortation= position[4] * 12; // 20 is distort param.
       		double imgaccurate= (double)blue_centroid[0] + imgdistortation;
       		imgaccurate=imgcentroidx - imgaccurate;
                 
        	double xactual = (imgaccurate * position[2])/focallength;
        	double theta= atan2(xactual,position[2]);
       		double totalangle=theta + position[4]; 
                position[6]=totalangle;  // final angle.
                position[7]=xactual; // x value tells i m in 1st quad or 2nd quad.           
	        return position;

               }   
              else
              return check;     
        
}






