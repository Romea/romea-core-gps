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


#ifndef ROMEA_CORE_GPS__NMEA__GSVFRAME_HPP_
#define ROMEA_CORE_GPS__NMEA__GSVFRAME_HPP_

// std
#include <optional>
#include <string>
#include <memory>
#include <deque>
#include <ostream>

// romea
#include "romea_core_gps/nmea/NMEATalker.hpp"


namespace romea
{


struct GSVFrame
{
  struct SatelliteInfo
  {
    SatelliteInfo();
    std::optional<unsigned short> PRNNumber;
    std::optional<unsigned short> elevation;
    std::optional<unsigned short> azimut;
    std::optional<unsigned short> SNR;
  };

  using Ptr = std::shared_ptr<GSVFrame>;

  GSVFrame();

  explicit GSVFrame(const std::string & nmeaGSVSentence);

  TalkerId talkerID;
  std::optional<unsigned short> numberOfSentences;
  std::optional<unsigned short> sentenceNumber;
  std::optional<unsigned short> numberOfSatellitesInView;
  std::optional<unsigned short> signalID;
  std::deque<SatelliteInfo> satellitesInfo;
};

std::ostream & operator<<(std::ostream & os, const GSVFrame & frame);

}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__GSVFRAME_HPP_
