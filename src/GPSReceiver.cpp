// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <string>

// romea
#include "romea_core_gps/GPSReceiver.hpp"


namespace romea
{


//--------------------------------------------------------------------------
GPSReceiver::GPSReceiver()
: fixUEREs_(),
  mutex_(),
  gsvFrameAggregator_(),
  satellitesInView_()
{
}

//--------------------------------------------------------------------------
GPSReceiver::GPSReceiver(
  const double & GpsFixEure,
  const double & DGpsFixEure,
  const double & FloatRtkFixEure,
  const double & RtkGpsFixEure,
  const double & SimulationFixEure,
  const Eigen::Vector3d & antennaBodyPosition)
: fixUEREs_(GpsFixEure, DGpsFixEure, FloatRtkFixEure, RtkGpsFixEure, SimulationFixEure),
  mutex_(),
  gsvFrameAggregator_(),
  satellitesInView_(),
  gpsReliability_(),
  antennaBodyPosition_(antennaBodyPosition)
{
}

//--------------------------------------------------------------------------
const double & GPSReceiver::getUERE(const FixQuality & fixQuality) const
{
  return fixUEREs_.get(fixQuality);
}

//--------------------------------------------------------------------------
void GPSReceiver::setAntennaBodyPosition(const Eigen::Vector3d & antennaBodyPosition)
{
  antennaBodyPosition_ = antennaBodyPosition;
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
  if (gsvFrameAggregator_.update(gsvFrame)) {
    std::lock_guard<std::mutex> lock(mutex_);
    TalkerId id = gsvFrame.talkerID;
    satellitesInView_.setSatellitesInfo(id, gsvFrameAggregator_.getSatellitesInfo(id));
    reliability_ = gpsReliability_.computeReliabilty(satellitesInView_);
    return true;
  }

  return false;
}

}  // namespace romea
