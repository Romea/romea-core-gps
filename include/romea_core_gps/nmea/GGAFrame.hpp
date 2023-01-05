// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_GPS__NMEA__GGAFRAME_HPP_
#define ROMEA_CORE_GPS__NMEA__GGAFRAME_HPP_

// std
#include <optional>
#include <string>
#include <memory>
#include <ostream>

// romea
#include "romea_core_gps/nmea/NMEALatitude.hpp"
#include "romea_core_gps/nmea/NMEALongitude.hpp"
#include "romea_core_gps/nmea/NMEAFixTime.hpp"
#include "romea_core_gps/nmea/NMEAFixQuality.hpp"
#include "romea_core_gps/nmea/NMEATalker.hpp"


namespace romea
{

struct GGAFrame
{
  using Ptr = std::shared_ptr<GGAFrame>;

  GGAFrame();

  explicit GGAFrame(const std::string & nmeaGGASentence);

  TalkerId talkerId;
  std::optional<FixTime> fixTime;
  std::optional<Latitude> latitude;
  std::optional<Longitude> longitude;
  std::optional<FixQuality> fixQuality;
  std::optional<unsigned short> numberSatellitesUsedToComputeFix;
  std::optional<double> horizontalDilutionOfPrecision;
  std::optional<double> altitudeAboveGeoid;
  std::optional<double> geoidHeight;
  std::optional<double> dgpsCorrectionAgeInSecond;
  std::optional<unsigned short> dgpsStationIdNumber;

  std::string toNMEA() const;
};

std::ostream & operator<<(std::ostream & os, const GGAFrame & frame);

}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__GGAFRAME_HPP_
