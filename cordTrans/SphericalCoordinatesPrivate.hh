#ifndef _GAZEBO_SPHERICALCOORDINATES_PRIVATE_HH_
#define _GAZEBO_SPHERICALCOORDINATES_PRIVATE_HH_
#include <ignition/math/Angle.hh>
#include <ignition/math/Matrix3.hh>
#include <ignition/math/Vector3.hh>

#include "SphericalCoordinates.hh"
#include "system.hh"

namespace gazebo
{
  namespace common
  {
    class SphericalCoordinates;

    /// \addtogroup gazebo_common
    /// \{

    /// \class SphericalCoordinatesPrivate SphericalCoordinatesPrivate.hh
    ///        commmon/common.hh
    /// \brief Private data for the SphericalCoordinates class.
    class GZ_COMMON_VISIBLE SphericalCoordinatesPrivate
    {
      /// \brief Type of surface being used.
      public: SphericalCoordinates::SurfaceType surfaceType;

      /// \brief Latitude of reference point.
      public: ignition::math::Angle latitudeReference;

      /// \brief Longitude of reference point.
      public: ignition::math::Angle longitudeReference;

      /// \brief Elevation of reference point relative to sea level in meters.
      public: double elevationReference;

      /// \brief Heading offset, expressed as angle from East to
      ///        gazebo x-axis, or equivalently from North to gazebo y-axis.
      public: ignition::math::Angle headingOffset;

      /// \brief Semi-major axis ellipse parameter
      public: double ellA;

      /// \brief Semi-minor axis ellipse parameter
      public: double ellB;

      /// \brief Flattening ellipse parameter
      public: double ellF;

      /// \brief First eccentricity ellipse parameter
      public: double ellE;

      /// \brief Second eccentricity ellipse parameter
      public: double ellP;

      /// \brief Rotation matrix that moves ECEF to GLOBAL
      public: ignition::math::Matrix3d rotECEFToGlobal;

      /// \brief Rotation matrix that moves GLOBAL to ECEF
      public: ignition::math::Matrix3d rotGlobalToECEF;

      /// \brief Cache the ECEF position of the the origin
      public: ignition::math::Vector3d origin;

      /// \brief Cache cosine head transform
      public: double cosHea;

      /// \brief Cache sine head transform
      public: double sinHea;
    };
    /// \}
  }
}
#endif
