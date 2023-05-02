// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


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
