// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license


#ifndef ROMEA_CORE_GPS__RELIABILITY__SNRDISTRIBUTION_HPP_
#define ROMEA_CORE_GPS__RELIABILITY__SNRDISTRIBUTION_HPP_

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

#endif  // ROMEA_CORE_GPS__RELIABILITY__SNRDISTRIBUTION_HPP_