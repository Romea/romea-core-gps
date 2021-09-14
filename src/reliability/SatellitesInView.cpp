//romea
#include "romea_gps/reliability/SatellitesInView.hpp"

//std
#include <typeinfo>
#include <cassert>

namespace romea {


//--------------------------------------------------------------------------
SatellitesInView::SatellitesInView():
  satellitesInfo_()
{

}

//--------------------------------------------------------------------------
void SatellitesInView::setSatellitesInfo(const TalkerId & gnssId,
    const std::deque<GSVFrame::SatelliteInfo> &satellitesInfo)
{
  satellitesInfo_[gnssId]=satellitesInfo;
}

//--------------------------------------------------------------------------
 std::list<TalkerId> SatellitesInView::getTalkerIds() const
{
  std::list<TalkerId> gpsIds;
  for (auto & mappair : satellitesInfo_)
    gpsIds.push_back(mappair.first);

  return gpsIds;
}

//--------------------------------------------------------------------------
const std::deque<GSVFrame::SatelliteInfo> & SatellitesInView::getSatellitesInfo(
    const TalkerId & globalPositioningID)const
{
  //c++20 replace by satellitesInfo_.contains
  auto I = satellitesInfo_.find(globalPositioningID);
  assert(I!=satellitesInfo_.end());
  return (*I).second;
}

}
