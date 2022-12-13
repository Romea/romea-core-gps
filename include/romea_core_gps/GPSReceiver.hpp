#ifndef ROMEA_CORE_GPS_GPSRECEIVER_HPP_
#define ROMEA_CORE_GPS_GPSRECEIVER_HPP_

// stl
#include <mutex>
#include <map>
#include <string>

// romea
#include "romea_core_gps/nmea/GGAFrame.hpp"
#include "romea_core_gps/nmea/RMCFrame.hpp"
#include "romea_core_gps/nmea/GSVFrame.hpp"
#include "romea_core_gps/nmea/NMEAParsing.hpp"
#include "romea_core_gps/nmea/GSVFrameAggregator.hpp"
#include "romea_core_gps/reliability/GPSReliability.hpp"

// Eigen
#include <Eigen/Eigen>

namespace romea {

class GPSReceiver
{
public :

  GPSReceiver();

  GPSReceiver(const double & GpsFixEure,
              const double & DGpsFixEure,
              const double & FloatRtkFixEure,
              const double & RtkGpsFixEure,
              const double & SimulationFixEure,
              const Eigen::Vector3d & antennaBodyPosition = Eigen::Vector3d::Zero());

public :

  void setAntennaBodyPosition(const Eigen::Vector3d & antennaBodyPosition);
  const Eigen::Vector3d & getAntennaBodyPosition() const;

  void setUERE(const FixQuality & fixQuality, const double & UERE);
  const double & getUERE(const FixQuality & fixQuality) const;

public :

  GGAFrame createFrameGGA(const std::string & nmeaGGASentence);

  RMCFrame createFrameRMC(const std::string & nmeaRMCSentence);

  bool updateSatellitesViews(const std::string & nmeaGSVFrame);

  SatellitesInView getSatellitesInView()const;

  double getReliability()const;

protected:

  std::map<FixQuality, double> fixUEREs_;

  mutable std::mutex mutex_;
  GSVFrameAggregator gsvFrameAggregator_;
  SatellitesInView satellitesInView_;
  GPSReliability gpsReliability_;
  double reliability_;

  Eigen::Vector3d antennaBodyPosition_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS_GPSRECEIVER_HPP_
