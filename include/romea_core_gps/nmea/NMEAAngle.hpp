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


#ifndef ROMEA_CORE_GPS__NMEA__NMEAANGLE_HPP_
#define ROMEA_CORE_GPS__NMEA__NMEAANGLE_HPP_

// std
#include <string>
#include <ostream>
#include <iomanip>

namespace romea
{

template<class CardinalDirections>
class NmeaAngle
{
public:
  explicit NmeaAngle(const double & angle);

  NmeaAngle(
    const int & degrees,
    const int & minutes,
    const double & microSeconds,
    const CardinalDirections & direction);

  virtual ~NmeaAngle() = default;

  const int & getDegrees()const;

  const int & getMinutes()const;

  const double & getSeconds()const;

  const CardinalDirections & getDirection()const;

  double toDouble()const;

protected:
  int degrees_;
  int minutes_;
  double seconds_;
  CardinalDirections direction_;
};

//-----------------------------------------------------------------------------
template<class CardinalDirections>
std::ostream & operator<<(std::ostream & os, const NmeaAngle<CardinalDirections> & mmeaAngle)
{
  int degrees = mmeaAngle.getDegrees();
  int minutes = mmeaAngle.getMinutes();
  double seconds = mmeaAngle.getSeconds();
  std::string direction = toString(mmeaAngle.getDirection());

  os << std::setfill('0');
  os << degrees << "d";
  os << std::setw(2) << minutes << "m";
  os << std::setw(2) << seconds << "s " << direction;
  return os;
}

}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__NMEAANGLE_HPP_
