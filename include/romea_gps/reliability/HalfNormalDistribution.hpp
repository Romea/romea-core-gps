#ifndef romea_HalfNormalDistribution_hpp
#define romea_HalfNormalDistribution_hpp

namespace romea {

class HalfNormalDistribution {

public :

  HalfNormalDistribution(const double &snrMean, const double &snrVariance);

  double operator()(const double & snr) const;

protected :

  double mean_;
  double var2_;
};

}
#endif
