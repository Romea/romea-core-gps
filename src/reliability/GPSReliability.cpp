//romea
#include "romea_gps/reliability/GPSReliability.hpp"

//std
#include <cassert>
#include <cmath>

namespace{
const float MINIMAL_NUMBER_OF_SATELLITES_IN_VIEW= 6;
}

namespace romea {

//--------------------------------------------------------------------------
GPSReliability::GPSReliability():
  snrDistributions_()
{

}

//--------------------------------------------------------------------------
void GPSReliability::setSNRDistribution(const TalkerId & talkerId,
                                        const SNRDistribution &snrDistribution)
{
  snrDistributions_[talkerId]=snrDistribution;
}



//--------------------------------------------------------------------------
double  GPSReliability::computeReliabilty(const SatellitesInView & satellitesInView)
{

  unsigned short numberOfVisibleSatellites =0;
  unsigned short numberOfHiddenSatellites =0;
  float snrReliability =0;
  float occlusionReliability = 0;

  //Global position system used by the recevier
  std::list<TalkerId> talkerIds = satellitesInView.getTalkerIds();

  //Update the reliability according satellites constellations
  for(auto & talkerId : talkerIds){

    const auto & satellitesInfo = satellitesInView.getSatellitesInfo(talkerId);
    const auto numberOfSatellites = satellitesInfo.size();

    //Check snr distrbution exists
    auto it = snrDistributions_.find(talkerId);
    if(it!=snrDistributions_.end()){

      //Update snr reliability
      const SNRDistribution & snrDistributions =(*it).second;
      for(size_t n=0;n<numberOfSatellites;++n){
        const GSVFrame::SatelliteInfo & info = satellitesInfo[n];
        if(info.SNR && *info.SNR!=0){
          snrReliability+=snrDistributions.computeSNRConfidence(*info.elevation,*info.SNR);
          ++numberOfVisibleSatellites;
        }else{
          occlusionReliability+= !info.elevation ? 0 :std::cos(*info.elevation/180.*M_PI);
          ++numberOfHiddenSatellites;
        }
      }
    }else{

      for(size_t n=0;n<numberOfSatellites;++n){
        const GSVFrame::SatelliteInfo & info = satellitesInfo[n];
        if(info.SNR && *info.SNR!=0){
          snrReliability++;
          ++numberOfVisibleSatellites;
        }else{
          occlusionReliability+= !info.elevation ?0 :std::cos(*info.elevation/180.*M_PI);
          ++numberOfHiddenSatellites;
        }
      }
    }
  }

  if(numberOfVisibleSatellites +numberOfHiddenSatellites <MINIMAL_NUMBER_OF_SATELLITES_IN_VIEW)
  {
    return 0;
  }

  return snrReliability*occlusionReliability;
}

}
