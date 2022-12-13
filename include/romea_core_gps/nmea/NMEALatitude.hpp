#ifndef ROMEA_CORE_GPS_NMEA_NMEALATITUDE_HPP_
#define ROMEA_CORE_GPS_NMEA_NMEALATITUDE_HPP_

// std
#include <string>

// romea
#include "romea_core_gps/nmea/NMEAAngle.hpp"


namespace romea
{

enum class LatitudeDirections : int
{
  NORTH = 1,
  SOUTH = -1
};

using Latitude = NmeaAngle<LatitudeDirections>;

std::string toString(const LatitudeDirections &direction);

LatitudeDirections toLatitudeDirection(const std::string & stringDirection);

}  // namespace romea

#endif  // ROMEA_CORE_GPS_NMEA_NMEALATITUDE_HPP_
