// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_GPS__GPSRECEIVEREURES_HPP_
#define ROMEA_CORE_GPS__GPSRECEIVEREURES_HPP_

// stl
#include <map>

// romea
#include "romea_core_gps/nmea/NMEAFixQuality.hpp"

namespace romea {

class GPSReceiverEUREs
{
public :

  GPSReceiverEUREs();

  GPSReceiverEUREs(const double & GpsFixEure,
                   const double & DGpsFixEure,
                   const double & FloatRtkFixEure,
                   const double & RtkGpsFixEure,
                   const double & SimulationFixEure);

  const double & get(const FixQuality & fixQuality) const;

private :

  std::map<FixQuality, double> fixUEREs_;
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS__GPSRECEIVEREURES_HPP_
