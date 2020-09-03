//romea
#include "HalfNormalDistribution.hpp"

//std
#include <vector>

namespace romea {

class SNRDistribution
{

public :

  SNRDistribution();

  SNRDistribution(const std::vector<HalfNormalDistribution> & snrDistribution);

  double computeSNRConfidence(const unsigned short & elevation, const unsigned short &snr) const;

protected :

  std::vector<HalfNormalDistribution> snrDistribution_;
};

}
