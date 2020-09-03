//romea
#include "romea_gps/reliability/HalfNormalDistribution.hpp"

//std
#include <cmath>

namespace romea {

//--------------------------------------------------------------------------
HalfNormalDistribution::HalfNormalDistribution(const double &snrMean,
                                              const double &snrVariance):
  mean_(snrMean),
  var2_(2*snrVariance)
{
}

//--------------------------------------------------------------------------
double HalfNormalDistribution::operator()(const double & snr) const
{

  if(snr>mean_){
    return 1.0f;
  }

  return std::exp(-(snr-mean_)*(snr-mean_)/var2_);
}

}
