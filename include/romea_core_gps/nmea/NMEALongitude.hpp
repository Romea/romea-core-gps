#ifndef ROMEA_CORE_GPS_NMEA_NMEALONGITUDE_HPP_
#define ROMEA_CORE_GPS_NMEA_NMEALONGITUDE_HPP_

// std
#include <string>

// romea
#include "romea_core_gps/nmea/NMEAAngle.hpp"

namespace romea
{

enum class LongitudeDirections : int
{
  EAST = 1,
  WEST = -1
};

using Longitude = NmeaAngle<LongitudeDirections>;

std::string toString(const LongitudeDirections & direction);

LongitudeDirections toLongitudeDirection(const std::string & stringDirection);

}  // namespace romea

#endif  // ROMEA_CORE_GPS_NMEA_NMEALONGITUDE_HPP_
