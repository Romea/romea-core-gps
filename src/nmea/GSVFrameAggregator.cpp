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
#include <deque>

// romea
#include "romea_core_gps/nmea/GSVFrameAggregator.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
GSVFrameAggregator::GSVFrameAggregator()
: satellitesInfo_()
{
}

//-----------------------------------------------------------------------------
bool GSVFrameAggregator::update(const GSVFrame & gsvFrame)
{
  if (gsvFrame.numberOfSentences &&
    gsvFrame.sentenceNumber &&
    gsvFrame.numberOfSatellitesInView)
  {
    std::deque<GSVFrame::SatelliteInfo> & satellitesData =
      satellitesInfo_[gsvFrame.talkerID];

    // Clear the view when the frame is received
    if (*gsvFrame.sentenceNumber == 1) {
      satellitesData.clear();
    }

    // Concate NMEA sentences
    satellitesData.insert(
      satellitesData.end(),
      gsvFrame.satellitesInfo.cbegin(),
      gsvFrame.satellitesInfo.cend());

    // Data is complete ?
    return *gsvFrame.sentenceNumber == *gsvFrame.numberOfSentences &&
           satellitesData.size() == *gsvFrame.numberOfSatellitesInView;
  }
  return false;
}

//-----------------------------------------------------------------------------
const std::deque<GSVFrame::SatelliteInfo> &
GSVFrameAggregator::getSatellitesInfo(const TalkerId & systemID)const
{
  // TODO(jean) c++20 replace by satellitesInfo_.contains
  auto I = satellitesInfo_.find(systemID);
  assert(I != satellitesInfo_.end());
  return (*I).second;
}

}  // namespace  romea
