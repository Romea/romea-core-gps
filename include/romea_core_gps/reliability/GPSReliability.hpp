#ifndef ROMEA_CORE_GPS_RELIABILITY_GPSRELIABILITY_HPP_
#define ROMEA_CORE_GPS_RELIABILITY_GPSRELIABILITY_HPP_

// std
#include <map>

// romea
#include <romea_core_common/time/Time.hpp>
#include "romea_core_gps/reliability/SNRDistribution.hpp"
#include "romea_core_gps/reliability/SatellitesInView.hpp"

namespace romea {

class GPSReliability
{
public:
  GPSReliability();

  void setSNRDistribution(const TalkerId & talkerId, const SNRDistribution & snrDistribution);

  double computeReliabilty(const SatellitesInView & satellitesInView);

protected :

  std::map<TalkerId, SNRDistribution> snrDistributions_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS_RELIABILITY_GPSRELIABILITY_HPP_
