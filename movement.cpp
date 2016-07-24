//
//  movement.cpp
//  openLOL
//
//  Created by Shubhankar Agarwal on 7/17/16.
//  Copyright © 2016 Shubhankar Agarwal. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include "movement.hpp"
#define PI 3.14159265

void direction(vector<Point>  target ,  double yawO , vector<Point2i> cent_i  , int framecounter , vector<double> area1 , double curr_depth){
    
    double ang = 0;
    
    double largest_area = contourArea( target , false);
    
    Point2f center;
    float   radius;
    //  vector<Point>  contours_poly( target.size() );
    
    // approxPolyDP( Mat(target), contours_poly , 3, true );
    minEnclosingCircle( target , center, radius);

    //////////////////////////////////////////////////////////////////////////////////
    /////////// FInding the angle ////////////////////////////////////////////////////
    
//    cout<<"Center of the image" << cent_i << endl;
//    cout<<"Center of the target" << center << endl;
    
    int dist_x = center.x - cent_i[0].x;
    int dist_y = center.y - cent_i[0].y;
    
    cout<< " dist_x = " << dist_x << " dist_y =" << dist_y <<endl;
    
     double camera_calib = 0.0005375 * min(2560/(cent_i[0].x * 2), 1440/(cent_i[0].y * 2));
    
    
 ////////////// Calculating the angle /////////////////////////////////////
    
    
    ////////// calculating the Yaw axis ///////////////
    
    ang = atan ( (dist_x) * camera_calib ) * 180 / PI;
    cout<< "The output yaw is "<<ang<<endl;

    
    ////////////////// calculating the PITCH ///////////////////////////////
    ang = - atan ( (dist_y) * camera_calib ) * 180 / PI;
     cout<< "The output pitch is "<<ang<<endl;
    


    
    int area = (int)largest_area;
    
    cout<<"area = "<<area<<endl;
    cout<< "frame no. = " << framecounter << endl;
    
    area1.push_back(area);
    
    
    
    double real_bouy_width = 0.1905 ; // in meters
    double dist = real_bouy_width/ (  camera_calib * (radius*2) );
    
    
    cout << "Distance to the bouy " << dist << endl;
    
    //////////////////////////////////////////////////////////////////////////////
    
    double depth , desired_depth;
    
    depth = dist * camera_calib * dist_y;
    
    desired_depth = curr_depth + depth;  /// the final desired depth 
    
    ///  vague description if we are going in correct direction
    /// comparing past 3 areas if the area has increased or not s
    
    if( framecounter > 3)
    {
        if( (area1[framecounter-2] + area1[framecounter-1] + area1[framecounter])/3 > area )
            cout<<"Wrong direction "<<endl;
        else
            cout<<"Right direction "<<endl;
    }
    
    
    ///////////////////////// STOP THE SUBMARINE////////////////
    
    cout<<endl;
    

//    return 1;
}

void changeaxis(Rect target , double yawO , vector<Point2i> cent_i  , int framecounter , vector<double> area1)
{
    
    
    
}

