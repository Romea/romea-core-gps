#include "romea_gps/nmea/NMEALongitude.hpp"
#include <iomanip>
#include <cassert>

namespace romea
{

//-----------------------------------------------------------------------------
std::string toString(const LongitudeDirections &direction)
{
  if(direction==LongitudeDirections::EAST)
  {
    return "E";
  }
  else
  {
    return "W";
  }
}

//-----------------------------------------------------------------------------
LongitudeDirections toLongitudeDirection(const std::string & stringDirection)
{
  if(stringDirection.compare("E")==0)
  {
    return LongitudeDirections::EAST;
  }
  else
  {
    assert(stringDirection.compare("W")==0);
    return LongitudeDirections::WEST;
  }
}

}
