#include <math.h>
#include "Helper.hh"
#include "Angle.hh"

using namespace gazebo;
using namespace math;

const Angle Angle::Zero = math::Angle(0);
const Angle Angle::Pi = math::Angle(M_PI);
const Angle Angle::HalfPi = math::Angle(M_PI * 0.5);
const Angle Angle::TwoPi = math::Angle(M_PI * 2.0);

//////////////////////////////////////////////////
Angle::Angle()
{
  this->value = 0;
}

//////////////////////////////////////////////////
Angle::Angle(double _radian)
{
  this->value = _radian;
}

//////////////////////////////////////////////////
Angle::Angle(const Angle &_angle)
{
  this->value = _angle.value;
}

//////////////////////////////////////////////////
Angle::Angle(const ignition::math::Angle &_angle)
{
  this->value = _angle.Radian();
}

//////////////////////////////////////////////////
Angle::~Angle()
{
}

//////////////////////////////////////////////////
void Angle::SetFromRadian(double _radian)
{
  this->value = _radian;
}

//////////////////////////////////////////////////
void Angle::SetFromDegree(double _degree)
{
  this->value = _degree * M_PI / 180.0;
}

//////////////////////////////////////////////////
double Angle::Radian() const
{
  return this->value;
}

//////////////////////////////////////////////////
double Angle::Degree() const
{
  return this->value * 180.0 / M_PI;
}

//////////////////////////////////////////////////
void Angle::Normalize()
{
  this->value = atan2(sin(this->value), cos(this->value));
}

//////////////////////////////////////////////////
Angle Angle::operator-(const Angle &angle) const
{
  return Angle(this->value - angle.value);
}

//////////////////////////////////////////////////
Angle Angle::operator+(const Angle &angle) const
{
  return Angle(this->value + angle.value);
}

//////////////////////////////////////////////////
Angle Angle::operator*(const Angle &angle) const
{
  return Angle(this->value * angle.value);
}

//////////////////////////////////////////////////
Angle Angle::operator/(const Angle &angle) const
{
  return Angle(this->value / angle.value);
}

//////////////////////////////////////////////////
Angle Angle::operator-=(const Angle &angle)
{
  this->value -= angle.value;
  return *this;
}

//////////////////////////////////////////////////
Angle Angle::operator+=(const Angle &angle)
{
  this->value += angle.value;
  return *this;
}

//////////////////////////////////////////////////
Angle Angle::operator*=(const Angle &angle)
{
  this->value *= angle.value;
  return *this;
}

//////////////////////////////////////////////////
Angle Angle::operator/=(const Angle &angle)
{
  this->value /= angle.value;
  return *this;
}

//////////////////////////////////////////////////
bool Angle::operator ==(const Angle &angle) const
{
  return gazebo::math::equal(this->value, angle.value, 0.001);
}

//////////////////////////////////////////////////
bool Angle::operator!=(const Angle &angle) const
{
  return !(*this == angle);
}

//////////////////////////////////////////////////
bool Angle::operator<(const Angle &angle) const
{
  return this->value < angle.value;
}

//////////////////////////////////////////////////
bool Angle::operator<=(const Angle &angle) const
{
  return this->value < angle.value || math::equal(this->value, angle.value);
}

//////////////////////////////////////////////////
bool Angle::operator>(const Angle &angle) const
{
  return this->value > angle.value;
}

//////////////////////////////////////////////////
bool Angle::operator>=(const Angle &angle) const
{
  return this->value > angle.value || gazebo::math::equal(this->value, angle.value);
}

//////////////////////////////////////////////////
ignition::math::Angle Angle::Ign() const
{
  return ignition::math::Angle(this->value);
}

//////////////////////////////////////////////////
Angle &Angle::operator=(const double &_angle)
{
  this->value = _angle;
  return *this;
}

//////////////////////////////////////////////////
Angle &Angle::operator=(const ignition::math::Angle &_angle)
{
  this->value = _angle.Radian();
  return *this;
}
