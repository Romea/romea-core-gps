// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

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
