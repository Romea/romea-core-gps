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
#include <cassert>
#include <string>

// romea
#include "romea_core_gps/nmea/NMEAFixQuality.hpp"

namespace romea
{
namespace core
{

//-----------------------------------------------------------------------------
std::string description(const FixQuality & fixQuality)
{
  switch (fixQuality) {
    case FixQuality::INVALID_FIX:
      return "invalid fix (0)";
      break;
    case FixQuality::GPS_FIX:
      return "gps fix (1)";
      break;
    case FixQuality::DGPS_FIX:
      return "dgps fix (2)";
      break;
    case FixQuality::PPS_FIX:
      return "pps fix (3)";
      break;
    case FixQuality::RTK_FIX:
      return "rtk fix (4)";
      break;
    case FixQuality::FLOAT_RTK_FIX:
      return "float rtk fix (5)";
      break;
    case FixQuality::ESTIMATED_FIX:
      return "estimated fix (6)";
      break;
    case FixQuality::MANUAL_FIX:
      return "manual fix (7)";
      break;
    case FixQuality::SIMULATION_FIX:
      return "simulation fix (8)";
      break;
    default:
      return "Unknown fix";
  }
}

//-----------------------------------------------------------------------------
bool operator>=(FixQuality fixQuality1, FixQuality fixQuality2)
{
  switch (fixQuality2) {
    case FixQuality::RTK_FIX:
      return fixQuality1 == FixQuality::RTK_FIX;
      break;
    case FixQuality::FLOAT_RTK_FIX:
      return fixQuality1 == FixQuality::RTK_FIX ||
             fixQuality1 == FixQuality::FLOAT_RTK_FIX;
      break;
    case FixQuality::DGPS_FIX:
      return fixQuality1 == FixQuality::RTK_FIX ||
             fixQuality1 == FixQuality::FLOAT_RTK_FIX ||
             fixQuality1 == FixQuality::DGPS_FIX;
      break;
    case FixQuality::GPS_FIX:
      return fixQuality1 == FixQuality::RTK_FIX ||
             fixQuality1 == FixQuality::FLOAT_RTK_FIX ||
             fixQuality1 == FixQuality::DGPS_FIX ||
             fixQuality1 == FixQuality::GPS_FIX;
      break;
    case FixQuality::PPS_FIX:
      return fixQuality1 == FixQuality::RTK_FIX ||
             fixQuality1 == FixQuality::FLOAT_RTK_FIX ||
             fixQuality1 == FixQuality::DGPS_FIX ||
             fixQuality1 == FixQuality::GPS_FIX ||
             fixQuality1 == FixQuality::PPS_FIX;
    default:
      return false;
  }
}

//-----------------------------------------------------------------------------
FixQuality modeIndicatorToFixQuality(const std::string & modeIndicator)
{
  assert(modeIndicator.size() == 1);
  switch (modeIndicator[0]) {
    case 'A':
      return FixQuality::GPS_FIX;
      break;
    case 'D':
      return FixQuality::DGPS_FIX;
      break;
    case 'P':
      return FixQuality::PPS_FIX;
      break;
    case 'R':
      return FixQuality::RTK_FIX;
      break;
    case 'F':
      return FixQuality::FLOAT_RTK_FIX;
      break;
    case 'E':
      return FixQuality::ESTIMATED_FIX;
      break;
    case 'M':
      return FixQuality::MANUAL_FIX;
      break;
    case 'S':
      return FixQuality::SIMULATION_FIX;
      break;
    default:
      return FixQuality::INVALID_FIX;
      break;
  }
}

//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const FixQuality & FixQuality)
{
  os << description(FixQuality);
  return os;
}

}  // namespace core
}  // namespace romea
