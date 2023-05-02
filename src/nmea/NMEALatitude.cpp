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
