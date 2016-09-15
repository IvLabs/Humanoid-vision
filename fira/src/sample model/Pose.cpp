#include "Pose.h"


Pose::Pose()
    {
        objectPoints.push_back(Point3f(240,680,715)); 
	objectPoints.push_back(Point3f(240,680,215));
	objectPoints.push_back(Point3f(615,680,215));
	objectPoints.push_back(Point3f(615,680,715));

        camera_matrix=Mat(Size(3,3),CV_32F);  
	camera_matrix.at<float>(0,0)= 727.957294 ;
	camera_matrix.at<float>(0,1)= 0.000000 ;
	camera_matrix.at<float>(0,2)= 304.729528 ;
	camera_matrix.at<float>(1,0)= 0.000000 ;
	camera_matrix.at<float>(1,1)= 726.232798 ;
	camera_matrix.at<float>(1,2)= 235.217420 ;
	camera_matrix.at<float>(2,0)= 0.000000 ;
	camera_matrix.at<float>(2,1)= 0.000000 ;
	camera_matrix.at<float>(2,2)= 1.000000 ;
	
   
        distCoeffs=Mat(Size(5,1),CV_32F);
	distCoeffs.at<float>(0,0) = 0.064654;
	distCoeffs.at<float>(0,1) = -0.451790;
	distCoeffs.at<float>(0,2) = 0.002167;
	distCoeffs.at<float>(0,3) = 0.000511;
	distCoeffs.at<float>(0,4) = 0.000000 ;

        
	 

        
    }

double* Pose::contour_detection(Mat threshold, Mat src)
{
   	int flag =0;
   	int largest_area=0;
   	int largest_contour_index;
   	int lowThreshold;
   	int ratio=3;
  	int kernel_size=3;
        int const max_lowThreshold = 100;
        static double position[3];

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
        findContours( detected_edges, contours0, hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image
	/*for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
		{
  		  double a=contourArea( contours[i],false); // Find the area of contour
		  if(a>largest_area)
	          {
 		  largest_area=a;
    		  largest_contour_index=i; //Store the index of largest contour
		   box = minAreaRect(contours[i]); // Find the bounding rectangle for biggest contour
                   
	          }
		}

	int k=largest_contour_index;
        


  	/*cv::Point2f vertices[4];
  	box.points(vertices);
  
  	for(int i = 0; i < 4; ++i)
      	{
       	cout<< "coordinates : x : "<< int (vertices[i].x) <<" y :"<< int(vertices[i].y)<<endl;
      	}
       
   	Scalar color( 255,255,255);
 	drawContours( dst, contours,largest_contour_index, color, CV_FILLED, 8, hierarchy ); // Draw the largest contour using previously 	 	stored index.
 	for(int i = 0; i < 4; ++i)
  	cv::line(src, vertices[i], vertices[(i + 1) % 4], cv::Scalar(255, 0, 0), 1, CV_AA);
 
  	imshow("dst",dst);*/


	contours.resize(contours0.size());
 	std::vector<Point2f> imagePoints;
         //vector<Point2f> preciseCorners(4);
    	for( size_t k = 0; k < contours0.size(); k++ )
        {
          double a=contourArea( contours0[k],false); // Find the area of contour
		if(a>largest_area)
	        {
 		largest_area=a;
    		largest_contour_index=k ;
        	approxPolyDP(Mat(contours0[largest_contour_index]), contours[largest_contour_index],9, true);
        	if(contours[k].size()==4)
         	{
 /*                  for (int c=0;c<4;c++)
		{		
		preciseCorners[c] = contours[largest_contour_index][c];
		}
         	
                 cv::cornerSubPix(threshold, preciseCorners, cvSize(5,5),cvSize(-1,-1),  TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 ));
              //  cv::cornerSubPix(threshold, preciseCorners, cvSize(5,5),cvSize(-1,-1), cvTermCriteria(CV_TERMCRIT_ITER,30,0.1));
                
                for (int c=0;c<4;c++)
		{
		contours[largest_contour_index][c] = preciseCorners[c];
		}
   */		  
                imagePoints.push_back(Point2f(contours[largest_contour_index][0].x,contours[largest_contour_index][0].y));
    		imagePoints.push_back(Point2f(contours[largest_contour_index][1].x,contours[largest_contour_index][1].y));
    		imagePoints.push_back(Point2f(contours[largest_contour_index][2].x,contours[largest_contour_index][2].y));
    		imagePoints.push_back(Point2f(contours[largest_contour_index][3].x,contours[largest_contour_index][3].y));
         	
		cout<< " X1 : " <<contours[largest_contour_index][0].x << " Y1 : "<< contours[largest_contour_index][0].y<< endl;
         	cout<< " X2 : " <<contours[largest_contour_index][1].x << " Y2 : "<< contours[largest_contour_index][1].y<< endl;
         	cout<< " X3 : " <<contours[largest_contour_index][2].x << " Y3 : "<< contours[largest_contour_index][2].y<< endl;
         	cout<< " X4 : " <<contours[largest_contour_index][3].x << " Y4 : "<< contours[largest_contour_index][3].y<< endl;
               
                Point P1=contours[largest_contour_index][0];
    		Point P2=contours[largest_contour_index][1];
    		Point P3=contours[largest_contour_index][2];
    		Point P4=contours[largest_contour_index][3];


    		line(src,P1,P2, Scalar(0,255,0),1,CV_AA,0);
    		line(src,P2,P3, Scalar(0,255,0),1,CV_AA,0);
    		line(src,P3,P4, Scalar(0,255,0),1,CV_AA,0);
    		line(src,P4,P1, Scalar(0,255,0),1,CV_AA,0);

                flag =1;
          	}
        	}
      }

	

// Pose estimation. 

if(flag==1)
{
	
       
        
//      for(int i = 0; i < 4; ++i)
//	imagePoints.push_back(Point2f(int(vertices[i].x),int(vertices[i].y)));
       
//	Mat rvec(3,1,DataType<double>::type);
//	Mat tvec(3,1,DataType<double>::type);

        Mat rvec=Mat(Size(3,1),CV_64F);
	Mat tvec=Mat(Size(3,1),CV_64F);
        int method = CV_ITERATIVE;
        bool use_extrinsic_guess = false;
	solvePnP(objectPoints,imagePoints, camera_matrix, distCoeffs,rvec,tvec,use_extrinsic_guess,method);
			 
        
	double val;
/*      cout<<"translation vector "<<endl;
	for(int i=0;i<tvec.rows ;i++)S
	{
		for(int j=0;j<tvec.cols;j++)
		{
		val=tvec.at<double>(i,j);
		cout<< "tvec : " << val <<endl ;	
		}
	}
        cout<<"rotation vector "<<endl;
	for(int i=0;i<rvec.rows ;i++)
	{
		for(int j=0;j<rvec.cols;j++)
		{
		val=rvec.at<double>(i,j);
		cout<< "   " << val ;
		}
	}
        cout<<""<<endl;
*/ 
//	Mat distant(3,3,DataType<double>::type);
//	Mat jacobian(3,1,DataType<double>::type);
        Mat distant=Mat(Size(3,3),CV_64F);
	Mat jacobian=Mat(Size(3,1),CV_64F);
	Rodrigues(rvec,distant,jacobian);

/*        cout<<"rotation Matrix "<<endl;
        for(int i=0;i<distant.rows ;i++)
	{
		for(int j=0;j<distant.cols;j++)
		{
		val=distant.at<double>(i,j);
		cout<< "   " << val ;
		}
         cout<<""<<endl;
           
	}m
         cout<<""<<endl;
*/      cout<< "transpose"<<endl;
        Mat R= distant.t(); 
/*         for(int i=0;i<R.rows ;i++)
	{
		for(int j=0;j<R.cols;j++)
		{
		val=R.at<double>(i,j);
		cout << "   " << val ;
		}
         cout<<""<<endl;
           
	}  
*/ 
       cout<<""<<endl;
     
               Mat T = -R * tvec ;
               position[0] =T.at<double>(0,0);
               position[1]=T.at<double>(1,0);
               position[2]=T.at<double>(2,0);
                
             
   
    
      
        
/*	double x = tvec.at<double>(0,0);
	double y = tvec.at<double>(2,0);
	double t = asin(-distant.at<double>(0,2));

	cout<<"  X :  "<< x << "  Y :  "<< y<< endl ;
        cout <<" Angle :  "<< t <<endl;
	cout <<" 90-t : " << (3.142/2) - t <<endl;
	double Rx = y * (cos((3.142/2) - t)) ;
	double Ry = y * (sin((3.142/2) - t)) ;
	cout<<" rx : "<< Rx << " ry : "<< Ry <<endl;
*/
        flag =0;
}

return position;
}


