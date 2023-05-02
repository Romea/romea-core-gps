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


#ifndef ROMEA_CORE_GPS__NMEA__NMEALONGITUDE_HPP_
#define ROMEA_CORE_GPS__NMEA__NMEALONGITUDE_HPP_

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

#endif  // ROMEA_CORE_GPS__NMEA__NMEALONGITUDE_HPP_
