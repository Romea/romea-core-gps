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
#include <iomanip>
#include <sstream>

// romea
#include "romea_core_gps/nmea/NMEAFixDate.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
FixDate::FixDate(
  int years,
  int months,
  int days)
: years_(years),
  months_(months),
  days_(days)
{
  assert(years_ < 100);
}

//-----------------------------------------------------------------------------
int FixDate::getYears()const
{
  return years_;
}

//-----------------------------------------------------------------------------
int FixDate::getMonths()const
{
  return months_;
}

//-----------------------------------------------------------------------------
double FixDate::getDays()const
{
  return days_;
}

//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const FixDate & fixDate)
{
  int years = fixDate.getYears();
  int month = fixDate.getMonths();
  int days = fixDate.getDays();

  os << std::setfill('0');
  os << std::setw(2) << days << "/";
  os << std::setw(2) << month << "/";
  os << std::setw(2) << years;
  return os;
}

}  // namespace romea
