#ifndef ROMEA_CORE_GPS__NMEA__HDTFRAME_HPP_
#define ROMEA_CORE_GPS__NMEA__HDTFRAME_HPP_

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
#include <optional>
#include <memory>
#include <ostream>
#include <string>

// romea
#include "romea_core_gps/nmea/NMEATalker.hpp"

namespace romea
{
namespace core
{

struct HDTFrame
{
  using Ptr = std::shared_ptr<HDTFrame>;

  HDTFrame() = default;

  explicit HDTFrame(const std::string & nmeaHDTSentence);

  TalkerId talkerId = TalkerId::UNSUPPORTED;
  std::optional<double> heading;
  std::optional<bool> trueNorth;

  std::string toNMEA() const;
};

std::ostream & operator<<(std::ostream & os, const HDTFrame & frame);

double headingToCourseAngle(double heading);

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__HDTFRAME_HPP_
