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


#ifndef ROMEA_CORE__GPS__NMEA__GSVFRAMEAGGREGATOR_HPP_
#define ROMEA_CORE__GPS__NMEA__GSVFRAMEAGGREGATOR_HPP_

// stl
#include <deque>
#include <map>

// romea
#include "romea_core_gps/nmea/GSVFrame.hpp"


namespace romea
{

class GSVFrameAggregator
{
public:
  using SatellitesInfo = std::deque<GSVFrame::SatelliteInfo>;

public:
  GSVFrameAggregator();

  bool update(const GSVFrame & gsvFrame);

  const SatellitesInfo & getSatellitesInfo(const TalkerId & systemID)const;

private:
  std::map<TalkerId, SatellitesInfo> satellitesInfo_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS_NMEA_GSVFRAMEAGGREGATOR_HPP_
