// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_GPS__NMEA__NMEAFIXQUALITY_HPP_
#define ROMEA_CORE_GPS__NMEA__NMEAFIXQUALITY_HPP_

// std
#include <string>
#include <ostream>

namespace romea
{

enum class FixQuality
{
  INVALID_FIX = 0,
  GPS_FIX,
  DGPS_FIX,
  PPS_FIX,
  RTK_FIX,
  FLOAT_RTK_FIX,
  ESTIMATED_FIX,
  MANUAL_FIX,
  SIMULATION_FIX
};

FixQuality modeIndicatorToFixQuality(const std::string & modeIndicator);

std::string description(const FixQuality & FixQuality);

std::ostream & operator<<(std::ostream & os, const FixQuality & FixQuality);

bool operator>=(FixQuality fixQuality1, FixQuality fixQuality2);

}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__NMEAFIXQUALITY_HPP_
