#ifndef romea_GSVFrameConcatenation_hpp
#define romea_GSVFrameConcatenation_hpp

//romea
#include "GSVFrame.hpp"

//stl
#include <deque>
#include <map>

namespace romea {

class GSVFrameAggregator {

public:

  using SatellitesInfo = std::deque<GSVFrame::SatelliteInfo>;

public:

  GSVFrameAggregator();

  bool update(const GSVFrame & gsvFrame);

  const SatellitesInfo & getSatellitesInfo(const TalkerId & systemID)const;

private :

  std::map<TalkerId,SatellitesInfo> satellitesInfo_;
};

}
#endif
