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


#ifndef ROMEA_CORE_GPS__NMEA__GGAFRAME_HPP_
#define ROMEA_CORE_GPS__NMEA__GGAFRAME_HPP_

// std
#include <optional>
#include <string>
#include <memory>
#include <ostream>

// romea
#include "romea_core_gps/nmea/NMEALatitude.hpp"
#include "romea_core_gps/nmea/NMEALongitude.hpp"
#include "romea_core_gps/nmea/NMEAFixTime.hpp"
#include "romea_core_gps/nmea/NMEAFixQuality.hpp"
#include "romea_core_gps/nmea/NMEATalker.hpp"


namespace romea
{

struct GGAFrame
{
  using Ptr = std::shared_ptr<GGAFrame>;

  GGAFrame();

  explicit GGAFrame(const std::string & nmeaGGASentence);

  TalkerId talkerId;
  std::optional<FixTime> fixTime;
  std::optional<Latitude> latitude;
  std::optional<Longitude> longitude;
  std::optional<FixQuality> fixQuality;
  std::optional<unsigned short> numberSatellitesUsedToComputeFix;
  std::optional<double> horizontalDilutionOfPrecision;
  std::optional<double> altitudeAboveGeoid;
  std::optional<double> geoidHeight;
  std::optional<double> dgpsCorrectionAgeInSecond;
  std::optional<unsigned short> dgpsStationIdNumber;

  std::string toNMEA() const;
};

std::ostream & operator<<(std::ostream & os, const GGAFrame & frame);

}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__GGAFRAME_HPP_
