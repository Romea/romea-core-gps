#ifndef INCLUDE_ROMEA_CORE_GPS_RELIABILITY_SNRDISTRIBUTION_HPP_
#define INCLUDE_ROMEA_CORE_GPS_RELIABILITY_SNRDISTRIBUTION_HPP_

// std
#include <vector>

// romea
#include "HalfNormalDistribution.hpp"


namespace romea {

class SNRDistribution
{
public :

  SNRDistribution();

  explicit SNRDistribution(const std::vector<HalfNormalDistribution> & snrDistribution);

  double computeSNRConfidence(const unsigned short & elevation, const unsigned short &snr) const;

protected :

  std::vector<HalfNormalDistribution> snrDistribution_;
};

}  // namespace romea

#endif  // INCLUDE_ROMEA_CORE_GPS_RELIABILITY_SNRDISTRIBUTION_HPP_