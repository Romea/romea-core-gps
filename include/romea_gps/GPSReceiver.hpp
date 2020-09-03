#ifndef romea_GPSReceiver_hpp
#define romea_GPSReceiver_hpp

//romea
//#include "../Sensor.hpp"
#include "nmea/GGAFrame.hpp"
#include "nmea/RMCFrame.hpp"
#include "nmea/GSVFrame.hpp"
#include "nmea/NMEAParsing.hpp"
#include "nmea/GSVFrameAggregator.hpp"
#include "reliability/GPSReliability.hpp"

//Eigen
#include <Eigen/Eigen>

//stl
#include <mutex>

namespace romea {

class GPSReceiver
{

public :

  GPSReceiver();

public :

  void setAntennaBodyPosition(const Eigen::Vector3d & antennaBodyPosition);
  const Eigen::Vector3d & getAntennaBodyPosition() const;

  void setUERE(const FixQuality & fixQuality,const double & UERE);
  const double & getUERE(const FixQuality & fixQuality) const;

public :

  GGAFrame createFrameGGA(const std::string & nmeaGGASentence);

  RMCFrame createFrameRMC(const std::string & nmeaRMCSentence);

  bool updateSatellitesViews(const std::string & nmeaGSVFrame);

  SatellitesInView getSatellitesInView()const;

  double getReliability()const;

protected:

  std::map<FixQuality,double> fixUEREs_;

  mutable std::mutex mutex_;
  GSVFrameAggregator gsvFrameAggregator_;
  SatellitesInView satellitesInView_;
  GPSReliability gpsReliability_;
  double reliability_;

  Eigen::Vector3d antennaBodyPosition_;
};

}

#endif
