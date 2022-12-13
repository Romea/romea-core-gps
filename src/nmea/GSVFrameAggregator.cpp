// std
#include <cassert>

// romea
#include "romea_core_gps/nmea/GSVFrameAggregator.hpp"

namespace romea {

//-----------------------------------------------------------------------------
GSVFrameAggregator::GSVFrameAggregator():
  satellitesInfo_()
{
}

//-----------------------------------------------------------------------------
bool GSVFrameAggregator::update(const GSVFrame &gsvFrame)
{
  if (gsvFrame.numberOfSentences &&
     gsvFrame.sentenceNumber &&
     gsvFrame.numberOfSatellitesInView)
  {
    std::deque<GSVFrame::SatelliteInfo> & satellitesData =
        satellitesInfo_[gsvFrame.talkerID];

    // Clear the view when the frame is received
    if (*gsvFrame.sentenceNumber == 1){
      satellitesData.clear();
    }

    // Concate NMEA sentences
    satellitesData.insert(satellitesData.end(),
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
GSVFrameAggregator::getSatellitesInfo(const TalkerId &systemID)const
{
  // TODO(jean) c++20 replace by satellitesInfo_.contains
  auto I = satellitesInfo_.find(systemID);
  assert(I != satellitesInfo_.end());
  return (*I).second;
}

}  // namespace  romea
