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
#include <typeinfo>
#include <cassert>

// romea
#include "romea_core_gps/reliability/SatellitesInView.hpp"


namespace romea
{


//--------------------------------------------------------------------------
SatellitesInView::SatellitesInView()
: satellitesInfo_()
{
}

//--------------------------------------------------------------------------
void SatellitesInView::setSatellitesInfo(
  const TalkerId & gnssId,
  const std::deque<GSVFrame::SatelliteInfo> & satellitesInfo)
{
  satellitesInfo_[gnssId] = satellitesInfo;
}

//--------------------------------------------------------------------------
std::list<TalkerId> SatellitesInView::getTalkerIds() const
{
  std::list<TalkerId> gpsIds;
  for (auto & mappair : satellitesInfo_) {
    gpsIds.push_back(mappair.first);
  }

  return gpsIds;
}

//--------------------------------------------------------------------------
const std::deque<GSVFrame::SatelliteInfo> & SatellitesInView::getSatellitesInfo(
  const TalkerId & globalPositioningID)const
{
  // TODO(jean) c++20 replace by satellitesInfo_.contains
  auto I = satellitesInfo_.find(globalPositioningID);
  assert(I != satellitesInfo_.end());
  return (*I).second;
}

}  // namespace romea
