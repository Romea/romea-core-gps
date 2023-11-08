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


#ifndef ROMEA_CORE_GPS__GPSRECEIVER_HPP_
#define ROMEA_CORE_GPS__GPSRECEIVER_HPP_

// Eigen
#include <Eigen/Eigen>

// stl
#include <mutex>
#include <map>
#include <string>

// romea
#include "romea_core_gps/GPSReceiverEUREs.hpp"
#include "romea_core_gps/nmea/GGAFrame.hpp"
#include "romea_core_gps/nmea/RMCFrame.hpp"
#include "romea_core_gps/nmea/GSVFrame.hpp"
#include "romea_core_gps/nmea/HDTFrame.hpp"
#include "romea_core_gps/nmea/NMEAParsing.hpp"
#include "romea_core_gps/nmea/GSVFrameAggregator.hpp"
#include "romea_core_gps/reliability/GPSReliability.hpp"


namespace romea
{

class GPSReceiver
{
public:
  GPSReceiver();

  GPSReceiver(
    const double & GpsFixEure,
    const double & DGpsFixEure,
    const double & FloatRtkFixEure,
    const double & RtkGpsFixEure,
    const double & SimulationFixEure,
    const Eigen::Vector3d & antennaBodyPosition = Eigen::Vector3d::Zero());

public:
  void setAntennaBodyPosition(const Eigen::Vector3d & antennaBodyPosition);
  const Eigen::Vector3d & getAntennaBodyPosition() const;

  const double & getUERE(const FixQuality & fixQuality) const;

public:
  GGAFrame createFrameGGA(const std::string & nmeaGGASentence);

  RMCFrame createFrameRMC(const std::string & nmeaRMCSentence);

  HDTFrame createFrameHDT(const std::string & nmeaHDTSentence);

  bool updateSatellitesViews(const std::string & nmeaGSVFrame);

  SatellitesInView getSatellitesInView()const;

  double getReliability()const;

protected:
  GPSReceiverEUREs fixUEREs_;

  mutable std::mutex mutex_;
  GSVFrameAggregator gsvFrameAggregator_;
  SatellitesInView satellitesInView_;
  GPSReliability gpsReliability_;
  double reliability_;

  Eigen::Vector3d antennaBodyPosition_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS__GPSRECEIVER_HPP_
