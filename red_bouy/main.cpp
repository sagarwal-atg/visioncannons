#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <sys/time.h>
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/photo/photo.hpp"
#include "bouydetection.hpp"
#include "pathmarker.hpp"
#include "allbouy.hpp"
#include "movement.hpp"


using namespace std;
using namespace cv;

double yawI = 0;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


/// Global variables
Mat src, detect , final_image;
vector<Point2i> cent_i(1);
vector<double> area1;


int main( int argc, char** argv )

{
    
    //Bouy_Ramming
    //underwatertest
    //Front/Image651.png
    cout<<"Time at starting is 0 sec"<<endl;
    
    string filename = "/Users/Somi/Desktop/_Recordings_/Bouy_Ramming.mp4";
    VideoCapture capture(filename);
    Mat frame;
    
    if( !capture.isOpened() )
        cout<< "OPen Up Bitchhhh "<<endl;
    
    int framecounter = 0;
    
    
    for( ; ; )
    {
        struct timeval tv0,tv1;
        gettimeofday(&tv0 , 0);
        
        capture >> src;
        capture >> detect;
        if(src.empty())
            break;
        imshow("w", src);
        waitKey(20);
        
        Size s = src.size();
        
        
        filter_image(detect ,src, s.height, s.width, cent_i , 150  , 100 , 150 );
        
        
        
        
        gettimeofday(&tv1,0);
        long elap = (tv1.tv_sec - tv0.tv_sec ) * 100000  + tv1.tv_usec - tv0.tv_usec;
        
        cout<<"Time after initial thresholding : " << elap/1000.0f <<"millisec"<<endl;
        
        //  imshow( "Display window", detect );
        fastNlMeansDenoising(detect,final_image , 100, 3, 31);
        
        //imshow( "after denoising" , final_image);
        
        vector<Point> red =  thresh_callback(final_image ,  yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,  framecounter );
        direction(red , yawI ,  cent_i  , framecounter ,  area1);
        
        waitKey(1);
        
        framecounter++;
        
        //  cout<<"Time after denoising and finding the target:"<<"sec"<<endl;
        
        
    }
    waitKey();
    
    return 0;
}
