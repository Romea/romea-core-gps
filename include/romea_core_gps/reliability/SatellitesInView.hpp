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


#ifndef ROMEA_CORE_GPS__RELIABILITY__SATELLITESINVIEW_HPP_
#define ROMEA_CORE_GPS__RELIABILITY__SATELLITESINVIEW_HPP_

// std
#include <deque>
#include <string>
#include <list>
#include <map>

// romea
#include "romea_core_gps/nmea/GSVFrameAggregator.hpp"


namespace romea
{

class SatellitesInView
{
public:
  using SatellitesInfo = std::deque<GSVFrame::SatelliteInfo>;

public:
  SatellitesInView();

  void setSatellitesInfo(
    const TalkerId & gnssId,
    const std::deque<GSVFrame::SatelliteInfo> & satellitesInfo);

  const SatellitesInfo & getSatellitesInfo(const TalkerId & talkerId)const;

  std::list<TalkerId> getTalkerIds() const;

private:
  std::map<TalkerId, SatellitesInfo> satellitesInfo_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS__RELIABILITY__SATELLITESINVIEW_HPP_
