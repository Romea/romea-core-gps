// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


// std
#include <cassert>
#include <vector>

// romea
#include "romea_core_gps/reliability/SNRDistribution.hpp"


namespace romea
{
namespace core
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
  const uint16_t & elevation,
  const uint16_t & snr) const
{
  assert(snrDistribution_.size() == 91);
  return elevation == 0 ? 0 : snrDistribution_[elevation](snr);
}

}  // namespace core
}  // namespace romea
