#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
 #include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
    
   Mat src = imread("/home/aniket/catkin_wsp/m.png");
   imshow("src",src);
  // inRange(src, Scalar(120,80,15), Scalar(170,100,60), src);
  // imshow("thresh",src);

vector<Mat> regions;
Mat region_frame;
int width = src.cols * 0.05;
int heigth = src.rows * 0.05;
int count=0;
for(int y=0; y<=(src.rows - heigth); y+=heigth)
{
    for(int x=0; x<=(src.cols - width); x+=width)
    {
        Rect region = Rect(x, y, width, heigth);
        region_frame = src(region);
        regions.push_back(region_frame);
        count++;            
    }
}
for(int i=0;i<count;i++)
{
imshow("crop",regions[i]);
waitKey(0);
}

return 0;
}
