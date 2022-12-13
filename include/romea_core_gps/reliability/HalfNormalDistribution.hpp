#ifndef ROMEA_CORE_GPS_RELIABILITY_HALFNORMALDISTRIBUTION_HPP_
#define ROMEA_CORE_GPS_RELIABILITY_HALFNORMALDISTRIBUTION_HPP_

namespace romea {

class HalfNormalDistribution {
public :

  HalfNormalDistribution(const double &snrMean, const double &snrVariance);

  double operator()(const double & snr) const;

protected :

  double mean_;
  double var2_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS_RELIABILITY_HALFNORMALDISTRIBUTION_HPP_
