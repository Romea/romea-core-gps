#ifndef romea_NMEALongitude_hpp
#define romea_NMEALongitude_hpp

//std
#include <string>

//romea
#include "NMEAAngle.hpp"

namespace romea
{

enum class LongitudeDirections : int
{
  EAST=1,
  WEST=-1
};

using Longitude = NmeaAngle<LongitudeDirections>;

std::string toString(const LongitudeDirections & direction);

LongitudeDirections toLongitudeDirection(const std::string & stringDirection);


}

#endif
