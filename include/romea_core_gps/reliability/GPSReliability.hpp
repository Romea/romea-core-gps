// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_GPS__RELIABILITY__GPSRELIABILITY_HPP_
#define ROMEA_CORE_GPS__RELIABILITY__GPSRELIABILITY_HPP_


// romea core
#include <romea_core_common/time/Time.hpp>

// std
#include <map>

#include "romea_core_gps/reliability/SNRDistribution.hpp"
#include "romea_core_gps/reliability/SatellitesInView.hpp"

namespace romea
{

class GPSReliability
{
public:
  GPSReliability();

  void setSNRDistribution(const TalkerId & talkerId, const SNRDistribution & snrDistribution);

  double computeReliabilty(const SatellitesInView & satellitesInView);

protected:
  std::map<TalkerId, SNRDistribution> snrDistributions_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS__RELIABILITY__GPSRELIABILITY_HPP_
