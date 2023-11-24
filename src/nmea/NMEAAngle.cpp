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


#include "romea_core_gps/nmea/NMEAAngle.hpp"
#include "romea_core_gps/nmea/NMEAParsing.hpp"
#include "romea_core_gps/nmea/NMEALatitude.hpp"
#include "romea_core_gps/nmea/NMEALongitude.hpp"
#include "romea_core_common/math/Algorithm.hpp"

namespace romea
{
namespace core
{

//-----------------------------------------------------------------------------
template<class CardinalDirections>
NmeaAngle<CardinalDirections>::NmeaAngle(
  const int & degrees,
  const int & minutes,
  const double & seconds,
  const CardinalDirections & direction)
: degrees_(degrees),
  minutes_(minutes),
  seconds_(seconds),
  direction_(direction)
{
}

//-----------------------------------------------------------------------------
template<class CardinalDirections>
NmeaAngle<CardinalDirections>::NmeaAngle(const double & angle)
: degrees_(0),
  minutes_(0),
  seconds_(0),
  direction_(static_cast<CardinalDirections>(int(sign(angle))))
{
  double angleInDegre = std::abs(180. * angle / M_PI);

  degrees_ = angleInDegre;
  minutes_ = (angleInDegre - degrees_) * 60;
  seconds_ = ((angleInDegre - degrees_) * 60 - minutes_) * 60;
}


//-----------------------------------------------------------------------------
template<class CardinalDirections>
const int & NmeaAngle<CardinalDirections>::getDegrees()const
{
  return degrees_;
}

//-----------------------------------------------------------------------------
template<class CardinalDirections>
const int & NmeaAngle<CardinalDirections>::getMinutes()const
{
  return minutes_;
}

//-----------------------------------------------------------------------------
template<class CardinalDirections>
const double & NmeaAngle<CardinalDirections>::getSeconds()const
{
  return seconds_;
}

//-----------------------------------------------------------------------------
template<class CardinalDirections>
const CardinalDirections & NmeaAngle<CardinalDirections>::getDirection()const
{
  return direction_;
}

//-----------------------------------------------------------------------------
template<class CardinalDirections>
double NmeaAngle<CardinalDirections>::toDouble()const
{
  return static_cast<int>(direction_) * (degrees_ + minutes_ / 60. + seconds_ / 3600.) / 180. *
         M_PI;
}

template class NmeaAngle<LatitudeDirections>;
template class NmeaAngle<LongitudeDirections>;

}  // namespace core
}  // namespace romea
