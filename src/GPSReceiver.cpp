#include "romea_gps/GPSReceiver.hpp"

namespace {
const double DEFAULT_UERE_GPS_FIX       = 3.0;
const double DEFAULT_UERE_DGPS_FIX      = 0.7;
const double DEFAULT_UERE_PPS_FIX       = 3.0;
const double DEFAULT_UERE_RTK_FIX       = 0.03;
const double DEFAULT_UERE_FLOAT_RTK_FIX = 0.25;
const double DEFAULT_UERE_INVALID_FIX   = std::numeric_limits<double>::max();
const double DEFAULT_UERE_SIMULATION_FIX=DEFAULT_UERE_RTK_FIX;
}


namespace romea {



//--------------------------------------------------------------------------
GPSReceiver::GPSReceiver() :
  fixUEREs_(),
  mutex_(),
  gsvFrameAggregator_(),
  satellitesInView_(),
  gpsReliability_(),
  antennaBodyPosition_(Eigen::Vector3d::Zero())
{

  fixUEREs_[FixQuality::GPS_FIX]=DEFAULT_UERE_GPS_FIX;
  fixUEREs_[FixQuality::DGPS_FIX]=DEFAULT_UERE_DGPS_FIX;
  fixUEREs_[FixQuality::PPS_FIX]=DEFAULT_UERE_PPS_FIX;
  fixUEREs_[FixQuality::RTK_FIX]=DEFAULT_UERE_RTK_FIX;
  fixUEREs_[FixQuality::FLOAT_RTK_FIX]=DEFAULT_UERE_FLOAT_RTK_FIX;
  fixUEREs_[FixQuality::INVALID_FIX]=DEFAULT_UERE_INVALID_FIX;
  fixUEREs_[FixQuality::SIMULATION_FIX]=DEFAULT_UERE_RTK_FIX;

}

//--------------------------------------------------------------------------
void GPSReceiver::setUERE(const FixQuality & fixQuality,const double & UERE)
{
  fixUEREs_[fixQuality]=UERE;
}

//--------------------------------------------------------------------------
const double & GPSReceiver::getUERE(const FixQuality & fixQuality) const
{
  //c++20 replace by fixUEREs_.contains
  auto it=fixUEREs_.find(fixQuality);
  assert(it!=fixUEREs_.end());
  return (*it).second;
}

//--------------------------------------------------------------------------
void GPSReceiver::setAntennaBodyPosition(const Eigen::Vector3d & antennaBodyPosition)
{
  antennaBodyPosition_=antennaBodyPosition;
}

//--------------------------------------------------------------------------
const Eigen::Vector3d & GPSReceiver::getAntennaBodyPosition() const
{
  return antennaBodyPosition_;
}

//--------------------------------------------------------------------------
SatellitesInView GPSReceiver::getSatellitesInView()const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return satellitesInView_;
}

//--------------------------------------------------------------------------
double GPSReceiver::getReliability()const
{
  return reliability_;
}

//--------------------------------------------------------------------------
GGAFrame GPSReceiver::createFrameGGA(const std::string & nmeaGGASentence)
{
  return GGAFrame(nmeaGGASentence);
}

//--------------------------------------------------------------------------
RMCFrame GPSReceiver::createFrameRMC(const std::string & nmeaRMCSentence)
{

  return RMCFrame(nmeaRMCSentence);
}

//--------------------------------------------------------------------------
bool GPSReceiver::updateSatellitesViews(const std::string & nmeaGSVSentence)
{

  GSVFrame gsvFrame(nmeaGSVSentence);
  if(gsvFrameAggregator_.update(gsvFrame))
  {
    std::lock_guard<std::mutex> lock(mutex_);
    TalkerId id = gsvFrame.talkerID;
    satellitesInView_.setSatellitesInfo(id,gsvFrameAggregator_.getSatellitesInfo(id));
    reliability_=gpsReliability_.computeReliabilty(satellitesInView_);
    return true;
  }

  return false;
}

}
