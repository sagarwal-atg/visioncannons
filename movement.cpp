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

void direction(vector<Point>  target , double yawO , vector<Point2i> cent_i  , int framecounter , vector<double> area1){
    
    double ang = 0;
    
    double largest_area = contourArea( target , false);
    
    Point2f center( target.size() );
    float   radius( target.size() );
    //  vector<Point>  contours_poly( target.size() );
    
    // approxPolyDP( Mat(target), contours_poly , 3, true );
    minEnclosingCircle( target , center, radius);

    //////////////////////////////////////////////////////////////////////////////////
    /////////// FInding the angle ////////////////////////////////////////////////////
    
    int dist_x = center.x - cent_i[0].x;
    int dist_y = center.y - cent_i[0].y;
    
    cout<< " dist_x = " << dist_x << " dist_y =" << dist_y <<endl;
    
    
    if ( center.x > cent_i[0].x) {
    
    }
    else {
    }
    //int ang = atan2 (dist_y,dist_x) * 180 / PI;
    
    ang = atan2 ( (dist_x) , (dist_y)) * 180 / PI;
    
    yawO =  -ang - 180;
    
    cout<< "The output yaw is "<<yawO<<endl;
    
    int area = (int)largest_area;
    
    cout<<"area = "<<area<<endl;
    cout<<endl;
    
    cout<< "frame no. = " << framecounter << endl;
    
    area1.push_back(area);
    
    if( framecounter > 3)
    {
        if( (area1[framecounter-2] + area1[framecounter-1] + area1[framecounter])/3 > area )
            cout<<" wrong direction "<<endl;
        else
            cout<<" right direction "<<endl;
    }
    

//    return 1;
}

void changeaxis(Rect target , double yawO , vector<Point2i> cent_i  , int framecounter , vector<double> area1)
{
    
    
    
}

