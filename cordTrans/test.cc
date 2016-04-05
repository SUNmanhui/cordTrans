#include "SphericalCoordinates.hh"

#include <iostream>


using namespace std;
using namespace gazebo;

int main(int argc, char **argv)
{
    
	common::SphericalCoordinates::SurfaceType st =
    common::SphericalCoordinates::EARTH_WGS84;
	
	//common::SphericalCoordinates sc;

    //test the transform
	ignition::math::Angle lat(28.226538), lon(112.996913),heading(0.5);
    double elev = 60;
    //sc.SetSurfaceType(st);
    //sc.SetLatitudeReference(lat);
    //sc.SetLongitudeReference(lon);
    //sc.SetHeadingOffset(heading);
    //sc.SetElevationReference(elev);
	
	common::SphericalCoordinates sc(st, lat, lon, elev, heading);

    // Check GlobalFromLocal with heading offset of 90 degrees
    
    // local frame
    ignition::math::Vector3d xyz;
    // east, north, up
    ignition::math::Vector3d enu;

    //xyz.Set(-37.531,197,0.5);
    //enu = sc.GlobalFromLocal(xyz);
    //cout<<enu.X()<<"\t"<<xyz.X()<<endl;
	//cout<<enu.Y()<<"\t"<<xyz.Y()<<endl;
	//cout<<enu.Z()<<"\t"<<xyz.Z()<<endl; 
    //xyz = sc.LocalFromGlobal(enu);
	//cout<<enu.X()<<"\t"<<xyz.X()<<endl;
	//cout<<enu.Y()<<"\t"<<xyz.Y()<<endl;
	//cout<<enu.Z()<<"\t"<<xyz.Z()<<endl; 
      

   
    // spherical coordinates
    ignition::math::Vector3d sph;

    // No offset
    xyz.Set(0, 0, 0);
    sph = sc.SphericalFromLocal(xyz);


    // latitude
    cout<<sph.X()<<"\t"<<lat.Degree()<<endl;
    // longitude
    cout<<sph.Y()<<"\t"<<lon.Degree()<<endl;
    // elevation
    cout<<sph.Z()<<"\t"<<elev<<endl;

    // 200 km offset in x (pi/2 heading offset means North). We use
    // SphericalFromLocal, which means that xyz is a linear movement on
    // a plane (not along the curvature of Earth). This will result in
    // a large height offset.
    //xyz.Set(2e5, 0, 0);
    //sph = sc.SphericalFromLocal(xyz);
    // increase in latitude about 1.8 degrees
    //cout<<sph.X()<<"\t"<<lat.Degree() + 1.8<<endl;
    // no change in longitude
    //cout<<sph.Z()<<"\t"<<3507.024791<<endl;

    //ignition::math::Vector3d xyz2 = sc.LocalFromSpherical(sph);
    //if(xyz==xyz2)
	//	cout<<"the result is right"<<endl;
	//else
	//	cout<<"there is something wrong with the transform"<<endl;
    

    // Check position projection
   
    // WGS84 coordinate obtained from online mapping software
    // > gdaltransform -s_srs WGS84 -t_srs EPSG:4978
    // > latitude longitude altitude(m)
    // > X Y Z Km
    ignition::math::Vector3d tmp;
    ignition::math::Vector3d osrf_s(28.226527, 112.996913, 41.0);
    ignition::math::Vector3d osrf_e(
            -2197.164, 5176.97, 2998.667);
    ignition::math::Vector3d goog_s(28.226527, 112.996913, 41.0);
    ignition::math::Vector3d goog_e(
            -2197.164, 5176.97, 2998.667);

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
    common::SphericalCoordinates sc2(st, ignition::math::Angle(osrf_s.X()),
            ignition::math::Angle(osrf_s.Y()), osrf_s.Z(), 0.0);

    // Check that SPHERICAL -> ECEF works
    tmp = sc2.PositionTransform(osrf_s,
            common::SphericalCoordinates::SPHERICAL,
            common::SphericalCoordinates::ECEF);
	cout<<tmp.X()<<"\t"<<osrf_e.X()<<endl;
	cout<<tmp.Y()<<"\t"<<osrf_e.Y()<<endl;
	cout<<tmp.Z()<<"\t"<<osrf_e.Z()<<endl;

    // Check that ECEF -> SPHERICAL works
    tmp = sc2.PositionTransform(tmp,
            common::SphericalCoordinates::ECEF,
            common::SphericalCoordinates::SPHERICAL);
	cout<<tmp.X()<<"\t"<<osrf_s.X()<<endl;
	cout<<tmp.Y()<<"\t"<<osrf_s.Y()<<endl;
	cout<<tmp.Z()<<"\t"<<osrf_s.Z()<<endl;

    // Check that SPHERICAL -> LOCAL works
    tmp = sc2.LocalFromSpherical(goog_s);
	cout<<tmp.X()<<"\t"<<vec.X()<<endl;
	cout<<tmp.Y()<<"\t"<<vec.Y()<<endl;
	cout<<tmp.Z()<<"\t"<<vec.Z()<<endl;

    // Check that SPHERICAL -> LOCAL -> SPHERICAL works
    tmp = sc2.SphericalFromLocal(tmp);
    cout<<tmp.X()<<"\t"<<goog_s.X()<<endl;
	cout<<tmp.Y()<<"\t"<<goog_s.Y()<<endl;
	cout<<tmp.Z()<<"\t"<<goog_s.Z()<<endl;
  
    //test the distance between our lab and the XiangRiver
    ignition::math::Angle latA, longA, latB, longB;
    latA.Degree(28.226538);
    longA.Degree(112.996913);
    latB.Degree(28.230139);
    longB.Degree(112.969812);
    double d = common::SphericalCoordinates::Distance(latA, longA, latB, longB);

    cout<<d<<endl;

    return 0;
}
