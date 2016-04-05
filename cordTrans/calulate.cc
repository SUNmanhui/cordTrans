#include "SphericalCoordinates.hh"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include "stdafx.h"
#include<vector>

using namespace std;
using namespace gazebo;

int main(int argc, char **argv)
{
    common::SphericalCoordinates::SurfaceType st =
    common::SphericalCoordinates::EARTH_WGS84;
	
    // local frame
    ignition::math::Vector3d xyz;
    // east, north, up
    //ignition::math::Vector3d enu;
   
    // spherical coordinates
    ignition::math::Vector3d sph;

    ignition::math::Vector3d osrf_s(28.226527, 112.996913, 41.0);
    ignition::math::Vector3d osrf_e(-2197.164, 5176.97, 2998.667);
    ignition::math::Vector3d goog_s(28.226527, 112.996913, 41.0);
    ignition::math::Vector3d goog_e(-2197.164, 5176.97, 2998.667);

    // Local tangent plane coordinates (ENU = GLOBAL) coordinates of
    // Google when OSRF is taken as the origin:
    // > proj +ellps=WGS84  +proj=tmerc hengzhoumokatuo
    // +lat_0=28.226527 +lon_0=112.996913 +k=1 +x_0=0 +y_0=0
    // > 28.226527, 112.996913 (LAT,LON)
    // > -1510.88 3766.64 (EAST,NORTH)
    ignition::math::Vector3d vec(0.0126737, 0.00357446, -9.7145);

    // Convert degrees to radians
    osrf_s.X() *= 0.0174532925;
    osrf_s.Y() *= 0.0174532925;

    // Set the ORIGIN to be the HPCL
    common::SphericalCoordinates sc(st, ignition::math::Angle(osrf_s.X()),
            ignition::math::Angle(osrf_s.Y()), osrf_s.Z(), 0.0);



    //test the distance between our lab and the XiangRiver
    //ignition::math::Angle latA, longA, latB, longB;
    //latA.Degree(28.226538);
    //longA.Degree(112.996913);
    //latB.Degree(28.230139);
    //longB.Degree(112.969812);
    //double d = common::SphericalCoordinates::Distance(latA, longA, latB, longB);

    //cout<<d<<endl;

    // No offset

    string temp1;
    char *char1;
    char *cb1;
    char *cb2;
    double x,y;
    vector<double> cord;

    const char find[]="	";

    cout<<"ready to covert the cordinate"<<endl;

    //Get the xyz of the points
    ifstream in("cordinate.txt");
    if (! in.is_open())
    { cout << "Error opening file"; exit (1); }

    while (getline(in,temp1))
    {


               char1 = new char[temp1.length() + 1];
               strcpy(char1,temp1.c_str());

               cb1 = strtok(char1, find);

               x = atof(cb1);

               cb2 = strtok(NULL, find);

               //cout<<x<<endl;

               y = atof(cb2);

               //cout<<y<<endl;

               xyz.Set(x*1000.0, y*1000.0, 0);

               // LOCAL -> SPHERICAL
               sph = sc.SphericalFromLocal(xyz);

               cord.push_back(sph.X());

               cord.push_back(sph.Y());
               cout<<sph.X()<<endl;
               cout<<sph.Y()<<endl;

    }

    cout<<"the covert is complete ! "<<endl;

    //print the cordinate in file
    ofstream out("out.txt");
           if (out.is_open())
               {
                    int count = 1;
                    for( int i = 0; i < cord.size(); i=i+2 )
                    {
                        out << count << "     "<< cord[ i ] << "    " << cord[ i+1 ] <<"\n";
                        count++;
                    }
                    out.close();
                }

    return 0;
}
