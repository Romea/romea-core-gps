#ifndef romea_NmeaLatitude_hpp
#define romea_NmeaLatitude_hpp

//romea
#include "NMEAAngle.hpp"

//std
#include <string>

namespace romea
{



enum class LatitudeDirections : int
{
  NORTH=1,
  SOUTH=-1
};

using Latitude = NmeaAngle<LatitudeDirections>;

std::string toString(const LatitudeDirections &direction);

LatitudeDirections toLatitudeDirection(const std::string & stringDirection);


}

#endif
