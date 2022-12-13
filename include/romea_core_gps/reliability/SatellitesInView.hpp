#ifndef ROMEA_CORE_GPS_RELIABILITY_SATELLITESINVIEW_HPP_ 
#define ROMEA_CORE_GPS_RELIABILITY_SATELLITESINVIEW_HPP_ 

// std
#include <deque>
#include <string>
#include <list>
#include <map>

// romea
#include "romea_core_gps/nmea/GSVFrameAggregator.hpp"


namespace romea {

class SatellitesInView
{
public :

  using SatellitesInfo  = std::deque<GSVFrame::SatelliteInfo>;

public :

  SatellitesInView();

  void setSatellitesInfo(const TalkerId & gnssId,
                         const std::deque<GSVFrame::SatelliteInfo> &satellitesInfo);

  const SatellitesInfo & getSatellitesInfo(const TalkerId & talkerId)const ;

  std::list<TalkerId> getTalkerIds() const;

private:
  std::map<TalkerId, SatellitesInfo> satellitesInfo_;
};

}  // namespace romea
#endif  // ROMEA_CORE_GPS_RELIABILITY_SATELLITESINVIEW_HPP_ 
