#ifndef romea_SatellitesMultipleViews_hpp
#define romea_SatellitesMultipleViews_hpp

//romea
#include "../nmea/GSVFrameAggregator.hpp"

//std
#include <string>
#include <list>
#include <map>

namespace romea {


class SatellitesInView {

public :

  using SatellitesInfo =std::deque<GSVFrame::SatelliteInfo>;

public :

  SatellitesInView();

  void setSatellitesInfo(const TalkerId & gnssId, const std::deque<GSVFrame::SatelliteInfo> &satellitesInfo);

  const SatellitesInfo & getSatellitesInfo( const TalkerId & talkerId)const ;

  std::list<TalkerId> getTalkerIds() const;

private:

  std::map<TalkerId,SatellitesInfo> satellitesInfo_;

};

}
#endif
