// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <iomanip>
#include <cassert>
#include <string>

// romea
#include "romea_core_gps/nmea/NMEALongitude.hpp"


namespace romea
{

//-----------------------------------------------------------------------------
std::string toString(const LongitudeDirections &direction)
{
  if (direction == LongitudeDirections::EAST)
  {
    return "E";
  } else {
    return "W";
  }
}

//-----------------------------------------------------------------------------
LongitudeDirections toLongitudeDirection(const std::string & stringDirection)
{
  if (stringDirection.compare("E") == 0)
  {
    return LongitudeDirections::EAST;
  } else {
    assert(stringDirection.compare("W") == 0);
    return LongitudeDirections::WEST;
  }
}

}  // namespace romea
