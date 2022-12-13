#ifndef ROMEA_CORE_GPS_NMEA_GSVFRAMEAGGREGATOR_HPP_
#define ROMEA_CORE_GPS_NMEA_GSVFRAMEAGGREGATOR_HPP_

// stl
#include <deque>
#include <map>

// romea
#include "romea_core_gps/nmea/GSVFrame.hpp"


namespace romea {

class GSVFrameAggregator {
public:
  using SatellitesInfo = std::deque<GSVFrame::SatelliteInfo>;

public:
  GSVFrameAggregator();

  bool update(const GSVFrame & gsvFrame);

  const SatellitesInfo & getSatellitesInfo(const TalkerId & systemID)const;

private :

  std::map<TalkerId, SatellitesInfo> satellitesInfo_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS_NMEA_GSVFRAMEAGGREGATOR_HPP_
