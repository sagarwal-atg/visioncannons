//
//  pathmarker.cpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 6/20/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//

#include "pathmarker.hpp"
#include "bouydetection.hpp"

#define PI 3.14159265


Rect path_marker( Mat final_image , double yawI , vector<Point2i> cent_i , vector<double> area1 ,  int thresh, int max_thresh , RNG rng , int g)
{
    
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    double l_area = 0;
    int l_c_i = 0;
    double ang = 0;
    
    /// Detect edges using Threshold
    threshold( final_image, threshold_output, thresh, 255, THRESH_BINARY );
   // cvtColor(threshold_output, threshold_output, CV_BGR2GRAY);
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    if( contours.size() > 0  )  {  /// checking if any countour is detected
        
        /// Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly( contours.size() );
         vector<Rect> boundRect( contours.size() );
        
        for( int i = 0; i < contours.size(); i++ )
        {   approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
          //  minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        }
        
        //   double b = contourArea( contours[0],false);
        
        
        
        
        
        for( int i = 0; i< contours.size(); i++ ) // iterate through each contour.
        {
            double a = contourArea( contours_poly[i],false);  //  Find the area of contour
            if(a>l_area){
                l_area=a;
                l_c_i = i;                //Store the index of largest contour
            }
        }
        
        
        int rec_width =  boundRect[l_c_i].br().x - boundRect[l_c_i].tl().x ;
        int rec_len =  boundRect[l_c_i].br().y - boundRect[l_c_i].tl().y;
        
        
        int rect_area = rec_width * rec_len ;
        
        cout<<"The area of the rectangle"<< rect_area<<endl;
        
        /// Draw  bonding rects
        Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
        
        if( rect_area > 40000 && rect_area < 60000 )
        {
        
    
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        
        rectangle( final_image, boundRect[l_c_i].tl(), boundRect[l_c_i].br(), color, 2, 8, 0 );
           
        
        //    setLabel(drawing, "Target", contours[0]);
            
       // Mat fit_line_image = drawing.clone();

        int rec_top_w =  boundRect[l_c_i].tl().x + ( boundRect[l_c_i].br().x - boundRect[l_c_i].tl().x ) /2 ;

////////////////////////// Making the line at the center of the rectangle ////////////////////////////
        
     //   int rec_bot_w = rec_top_w + (boundRect[l_c_i].br().y - boundRect[l_c_i].tl().y);
        
        {   std::vector<cv::Point> rect_center;
            Point temp;
            
            temp.x = rec_top_w;
            temp.y = boundRect[l_c_i].tl().y;
            rect_center.push_back(temp);
            
            temp.x = rec_top_w;
            temp.y = boundRect[l_c_i].br().y;
            rect_center.push_back(temp);
            
         //   MyLine(drawing , rect_center[0] , rect_center[1]);
            
         //   MyLine(drawing , boundRect[l_c_i].tl(), boundRect[l_c_i].br());

            
        }
        
        
        vector<float> fit_line(4);
        
        fitLine(contours_poly[l_c_i], fit_line, CV_DIST_L2, 0, 0.01, 0.01);
        
       // cout<<"The size "
        
        Point fitline_start ;
        fitline_start.x = fit_line[2] - fit_line[0] * 200;
        fitline_start.y = fit_line[3] - fit_line[1] * 200;
        
        Point fitline_end ;
        
        fitline_end.x = fit_line[2] + fit_line[0] * 200;
        fitline_end.y = fit_line[3] + fit_line[1] * 200;
    
        
        
        line(final_image, fitline_start, fitline_end, color , 5 , 8 , 0  );
        
       // if( ang > 0 &&  ang ) {
        
        
        
        ///  fit_line[1] the y -axis angle and fit_line[0] x-axis. We make fit_line[0] -ve because in image processing the z values decrease as we go down
        ang = atan(-(fit_line[0]) /fit_line[1]) * 180 / PI;
            cout<<"The angle of the pathmarker is " << ang <<endl;
        
    }
    

///////////////////////////drawing line at the center of the image //////////////////////////////////////////////////////////////
//        
//        vector<Point2i> cent_k(1);
//        vector<Point2i> cent_j(1);
//        
//        cent_k[0] = cent_i[0];
//        cent_k[0].x = cent_i[0].x - 200;
//        
//        cent_j[0] = cent_i[0];
//        cent_j[0].x = cent_i[0].x + 200;
//        
//        
//        // Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//        circle( final_image , cent_i[0] ,  5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
//        //circle( drawing , cent_i[0] ,  2*5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
//        //circle( drawing , cent_i[0] ,  4*5 , Scalar( 72, 209, 51 ) , 2, 8 , 0);
//        MyLine(final_image , (cent_k[0] ), (cent_j[0]));
//        
//        cent_k[0] = cent_i[0];
//        cent_k[0].y = cent_i[0].y - 200;
//        
//        cent_j[0] = cent_i[0];
//        cent_j[0].y = cent_i[0].y + 200;
//        
//        MyLine(final_image , (cent_k[0] ), (cent_j[0]));
        
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        std::vector<cv::Point> c_print;
        
        Point temp;
        
        temp.x = 10;
        temp.y = 10;
        c_print.push_back(temp);
        
        temp.x = 100;
        temp.y = 10;
        c_print.push_back(temp);
        
        temp.x = 10;
        temp.y = 20;
        c_print.push_back(temp);
        temp.x = 100;
        temp.y = 20;
        c_print.push_back(temp);
        
        
        setLabel(final_image, "Property of SDCR" , c_print);
        
        stringstream ang_s;
        ang_s<< -ang;
        string ang_s1 = ang_s.str();
        string s = "The angle of the target from x-axis is " + ang_s1;
        
        temp.x = 10;
        temp.y = 30;
        c_print.push_back(temp);
        
        temp.x = 100;
        temp.y = 30;
        c_print.push_back(temp);
        
        temp.x = 10;
        temp.y = 40;
        c_print.push_back(temp);
        temp.x = 100;
        temp.y = 40;
        c_print.push_back(temp);
        
        setLabel(drawing, s , c_print);
        /// Show in a window
       // namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
      //  imshow( "Contours", final_image );
        
        return boundRect[l_c_i];
    }
    
   Rect nobouy;
    
    return  nobouy;

}