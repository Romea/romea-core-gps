// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <cassert>
#include <vector>

// romea
#include "romea_core_gps/reliability/SNRDistribution.hpp"


namespace romea
{

//--------------------------------------------------------------------------
SNRDistribution::SNRDistribution()
: snrDistribution_()
{
}

//--------------------------------------------------------------------------
SNRDistribution::SNRDistribution(const std::vector<HalfNormalDistribution> & snrDistribution)
: snrDistribution_(snrDistribution)
{
  assert(snrDistribution_.size() == 91);
}

//--------------------------------------------------------------------------
double SNRDistribution::computeSNRConfidence(
  const unsigned short & elevation,
  const unsigned short & snr) const
{
  assert(snrDistribution_.size() == 91);
  return elevation == 0 ? 0 : snrDistribution_[elevation](snr);
}

}  // namespace romea
