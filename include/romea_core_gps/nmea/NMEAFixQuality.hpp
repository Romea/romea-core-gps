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
