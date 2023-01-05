// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <iomanip>
#include <cassert>
#include <string>

// romea
#include "romea_core_gps/nmea/NMEALatitude.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
std::string toString(const LatitudeDirections & direction)
{
  if (direction == LatitudeDirections::NORTH) {
    return "N";
  } else {
    return "S";
  }
}

//-----------------------------------------------------------------------------
LatitudeDirections toLatitudeDirection(const std::string & stringDirection)
{
  if (stringDirection.compare("N") == 0) {
    return LatitudeDirections::NORTH;
  } else {
    assert(stringDirection.compare("S") == 0);
    return LatitudeDirections::SOUTH;
  }
}

}  // namespace romea
