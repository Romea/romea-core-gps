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

#ifndef ROMEA_CORE_GPS__NMEA__RMCFRAME_HPP_
#define ROMEA_CORE_GPS__NMEA__RMCFRAME_HPP_

// std
#include <optional>
#include <string>
#include <memory>
#include <ostream>

// romea
#include "romea_core_gps/nmea/NMEALatitude.hpp"
#include "romea_core_gps/nmea/NMEALongitude.hpp"
#include "romea_core_gps/nmea/NMEAFixQuality.hpp"
#include "romea_core_gps/nmea/NMEAFixTime.hpp"
#include "romea_core_gps/nmea/NMEAFixDate.hpp"
#include "romea_core_gps/nmea/NMEATalker.hpp"


namespace romea
{

struct RMCFrame
{
  enum class Status
  {
    Active = 0,
    Void
  };

  using Ptr = std::shared_ptr<RMCFrame>;

  RMCFrame();

  explicit RMCFrame(const std::string & nmeaRMCSentence);

  TalkerId talkerId;
  std::optional<FixTime> fixTime;
  std::optional<Status> status;
  std::optional<Latitude> latitude;
  std::optional<Longitude> longitude;
  std::optional<double> speedOverGroundInMeterPerSecond;
  std::optional<double> trackAngleTrue;
  std::optional<FixDate> fixDate;
  std::optional<double> magneticDeviation;
  std::optional<FixQuality> fixQuality;

  std::string toNMEA() const;
};

std::ostream & operator<<(std::ostream & os, const RMCFrame & frame);


double trackAngleToCourseAngle(
  const double & trackAngle,
  const double & vehiclelLinearSpeed);


}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__RMCFRAME_HPP_
