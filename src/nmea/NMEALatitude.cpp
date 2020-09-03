#include "romea_gps/nmea/NMEALatitude.hpp"
#include <iomanip>
#include <cassert>


namespace romea
{

//-----------------------------------------------------------------------------
std::string toString(const LatitudeDirections & direction)
{
  if(direction==LatitudeDirections::NORTH)
  {
    return "N";
  }
  else
  {
    return "S";
  }
}

//-----------------------------------------------------------------------------
LatitudeDirections toLatitudeDirection(const std::string & stringDirection)
{

  if(stringDirection.compare("N")==0)
  {
    return LatitudeDirections::NORTH;
  }
  else
  {
    assert(stringDirection.compare("S")==0);
    return LatitudeDirections::SOUTH;
  }
}

}
