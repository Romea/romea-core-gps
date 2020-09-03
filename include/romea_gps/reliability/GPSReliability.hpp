#ifndef romea_GPSReliability_hpp
#define romea_GPSReliability_hpp

//romea
#include <romea_common/time/Time.hpp>
#include "SNRDistribution.hpp"
#include "SatellitesInView.hpp"

namespace romea {

class GPSReliability
{
public:

  GPSReliability();

  void setSNRDistribution(const TalkerId & talkerId, const SNRDistribution & snrDistribution);

  double computeReliabilty(const SatellitesInView & satellitesInView);

protected :

  std::map<TalkerId,SNRDistribution> snrDistributions_;

};

}

#endif
