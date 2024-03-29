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

// all bouy , path marker and shpae detction working

using namespace std;
using namespace cv;

double yawI = 0;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


/// Global variables
Mat  src, detect_r , detect_g , detect_y ,pathmark; //, final_image;
//vector<Point2i> cent_i(1);
vector<double> area1;

///////////////// tasks ///////////////////////////////
bool validation_gate_done = false;
bool b_detected = false;
bool bouy_done = false;
bool target_bouy_found = false;
bool red_bouy = false ;
bool green_bouy = false ;
bool yellow_bouy = false;
bool time_portal_started = false;
bool time_portal_finished = false;
////////////////////////////////////////////////////////



int main( int argc, char** argv )

{
    // this will be the main file for tesing computer vision and deploying in submarine
    //Bouy_Ramming
    //underwatertest
    //Front/Image651.png
    cout<<"Time at starting is 0 sec"<<endl;
    
    string filename =  "/Users/Somi/Desktop/_Recordings_/underwatertest.mp4";
    string filename2 = "/Users/Somi/Desktop/_Recordings_/pathmarkerTest480p.mp4";
    
    char imageName[48];
    
//    VideoCapture capture(filename);
    VideoCapture pathcap(filename2);
    //src = imread(filename);
    
//    pathcap.set(CV_CAP_PROP_FRAME_WIDTH,640);
//    pathcap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    
//    if( !capture.isOpened() )
//        cout<< "Error when reading steam_avi"<<endl;
    
    int framecounter = 0;
    
    
    
    for( ; ; )
    { //  Mat hello;
     //   capture >> hello;
        pathcap.read(pathmark);
        

      //  sprintf(imageName,"/Users/Somi/Desktop/_Recordings_/Bottom/Image%d.png",framecounter);
        
        cout<<"Framecounter "<<framecounter<<endl;
//        
//        
//        Rect myROI(20, 0, 440, 350);
//        Mat src( hello ,myROI);
        
    //    pathmark = imread(imageName);
        
        ////// ASK FOR CURRENT DEPTH /////////
        
        /// skipping 50 frames
        if( framecounter% 10 == 0){
            
//            if(!pathmark.data)                              // Check for invalid input
//            {
//                cout <<  "Could not open or find the image" << std::endl ;
//                return -1;
//            }
            struct timeval tv0,tv1;
            gettimeofday(&tv0 , 0);
            
            
//            Mat canny;
//            
//            canny = imread("/Users/Somi/Desktop/_Recordings_/circles.jpg");
//            cvtColor( canny, canny, CV_BGR2GRAY );
//            
//            //Canny(canny, canny, 1, 100);
//            
//            
//            vector<Vec3f> circles;
//            HoughCircles(canny, circles, CV_HOUGH_GRADIENT, 1, 1);
//            
//            Mat circle_img;
//            circle_img = canny.clone();
//            for( int i = 0 ; i < circles.size() ; i++){
//                circle(circle_img, Point(circles[i][0] , circles[i][1]), circles[i][2],  Scalar( 0 , 0, 255 ) );
//            }
//            cout<<"The size of the circle vector " <<circles.size() <<endl;
//            imshow("Canny " , canny);
//            imshow("Circles", circle_img);
            
            
            ////////////////////////////////////////// NOT SURE IF WE WILL BE DOING THIS ///////////
            /*
             if( !validation_gate_done)
             {
             
             validation_gate_done = true;
             
             }*/
            /////////////////////////////////////////////////////////////////////////////////////////////
            Size size = src.size();
            vector<Point2i> cent_i(1);
            
            
            cent_i[0].x=  (floor( size.width/2));
            cent_i[0].y = (floor( size.height/2));
//
//            cout<< cent_i << endl; 
//
//            
//            
//            
//            ///////////////////////////////////////////////////ALL BOUY DETECTION //////////////////////////////////////////////////////
//            validation_gate_done = true;
//            
//                    if( validation_gate_done && !bouy_done)
//                    {
                        detect_r = src.clone();
                        detect_g = src.clone();
                        detect_y = src.clone();
            
                        imshow("Source Front", src);
            
                        Size s = src.size();
            
                        vector<vector<Point> > contours;
            
            
                        gettimeofday(&tv1,0);
                        long elap = (tv1.tv_sec - tv0.tv_sec ) * 100000  + tv1.tv_usec - tv0.tv_usec;
            
                        cout<<"Time after initial thresholding : " << elap/1000.0f <<"millisec"<<endl;
            
                        // red 150 , 100 , 150
                        // green <  140 , 160 , 160
                        // helllo i am here
            
            
                        Mat final_image = Mat::zeros( src.size(), CV_8UC3 );
            
                        filterImageHSVRed(detect_r ,src, s.height, s.width, cent_i  );
                        fastNlMeansDenoising(detect_r , detect_r , 100, 3, 31);
                       imshow("After Hue red", detect_r);
                        vector<Point> red_vec = all_bouy(detect_r , final_image,   yawI ,  cent_i , area1 ,  thresh , max_thresh , rng , framecounter   , contours , 0);

                        
//                        filterImageHSVGreen(detect_g ,src, s.height, s.width, cent_i  );
//                        fastNlMeansDenoising(detect_g , detect_g , 100, 3, 31);
//                     //   imshow("After Hue Green", detect_g);
//                        vector<Point> green_vec = all_bouy(detect_g ,final_image,  yawI ,  cent_i , area1 ,  thresh , max_thresh , rng , framecounter   , contours , 1);
//
//                        
//                        filterImageHSVYellow(detect_y ,src, s.height, s.width, cent_i  );
//                        fastNlMeansDenoising(detect_y , detect_y , 100, 3, 31);
//                       // imshow("After Hue Yellow", detect_y);
//                        vector<Point> yellow_vec = all_bouy(detect_y , final_image,   yawI ,  cent_i , area1 ,  thresh , max_thresh , rng ,framecounter, contours , 2);
//
//                        
//                        
//                        imshow( "Final Detection" , final_image);
//                        
//                        
//                        
//                        
//
//                    }
            
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            
            
            //////////////////////////////////////////////////// PATH MARKER ///////////////////////////////////////////////////////////
            
            
            imshow("Source Forward", pathmark);
            Size p = pathmark.size();
            detect_r = pathmark.clone();
            cout << "width "  << p.width  << "height " << p.height << endl;
            
            Mat hsv;     // = src.clone();
            cvtColor(pathmark, hsv, CV_BGR2HSV);
            
            vector<Mat> channels;
            split(hsv, channels);
            
//            imshow("Hue", channels[0]);
//           imshow("Saturation", channels[1]);
//            imshow("Value", channels[2]);
            
           // flip(pathmark, pathmark, 0);
            
            threshold(channels[1], channels[1], 80 , 255, THRESH_BINARY);
            imshow("saturation" , channels[1]);
            //Mat path_image = Mat::zeros( pathmark.size(), CV_8UC3 );
            
            
       //    filterImageHSVOrange(detect_r ,pathmark, p.height, p.width, cent_i  );
            
            //fastNlMeansDenoising(detect_r , detect_r , 50, 3, 31);
            fastNlMeansDenoising(channels[1] , channels[1] , 50, 3, 31);

//            imshow( "Display red", channels[1] );
            
            
            
            Rect pathMarkerRect = path_marker(  channels[1] ,  yawI , cent_i ,  area1 ,  thresh,  max_thresh ,  rng ,  framecounter);
            
            imshow("pathmarker", channels[1]);
            
            
            
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            waitKey(100);
            
            
        }
        framecounter++;
    }
}



