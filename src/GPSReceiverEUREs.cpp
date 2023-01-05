// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <cassert>
#include <limits>
#include <sstream>
#include <exception>

// romea
#include "romea_core_gps/GPSReceiverEUREs.hpp"

namespace
{
const double DEFAULT_UERE_GPS_FIX = 3.0;
const double DEFAULT_UERE_DGPS_FIX = 0.7;
const double DEFAULT_UERE_PPS_FIX = DEFAULT_UERE_GPS_FIX;
const double DEFAULT_UERE_RTK_FIX = 0.03;
const double DEFAULT_UERE_FLOAT_RTK_FIX = 0.25;
const double DEFAULT_UERE_INVALID_FIX = std::numeric_limits<double>::max();
const double DEFAULT_UERE_SIMULATION_FIX = DEFAULT_UERE_RTK_FIX;
}  // namespace

namespace romea
{


GPSReceiverEUREs::GPSReceiverEUREs()
: GPSReceiverEUREs(DEFAULT_UERE_GPS_FIX, DEFAULT_UERE_DGPS_FIX, DEFAULT_UERE_FLOAT_RTK_FIX,
    DEFAULT_UERE_RTK_FIX, DEFAULT_UERE_SIMULATION_FIX)
{
}

GPSReceiverEUREs::GPSReceiverEUREs(
  const double & GpsFixEure,
  const double & DGpsFixEure,
  const double & FloatRtkFixEure,
  const double & RtkGpsFixEure,
  const double & SimulationFixEure)
{
  fixUEREs_[FixQuality::GPS_FIX] = GpsFixEure;
  fixUEREs_[FixQuality::DGPS_FIX] = DGpsFixEure;
  fixUEREs_[FixQuality::PPS_FIX] = GpsFixEure;
  fixUEREs_[FixQuality::RTK_FIX] = RtkGpsFixEure;
  fixUEREs_[FixQuality::FLOAT_RTK_FIX] = FloatRtkFixEure;
  fixUEREs_[FixQuality::INVALID_FIX] = DEFAULT_UERE_INVALID_FIX;
  fixUEREs_[FixQuality::SIMULATION_FIX] = SimulationFixEure;
}

const double & GPSReceiverEUREs::get(const FixQuality & fixQuality) const
{
  // TODO(jean) c++20 replace by fixUEREs_.contains
  auto it = fixUEREs_.find(fixQuality);

  if ( it == fixUEREs_.end() )
  {
    std::ostringstream msg;
    msg << " Fix quality : ";
    msg << fixQuality;
    msg << " is unsupported by GPSReceiverEUREs";
    throw std::runtime_error(msg.str());
  }

  return (*it).second;
}

}  // namespace romea
