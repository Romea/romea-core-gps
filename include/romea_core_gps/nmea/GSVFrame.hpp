// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_GPS__NMEA__GSVFRAME_HPP_
#define ROMEA_CORE_GPS__NMEA__GSVFRAME_HPP_

// std
#include <optional>
#include <string>
#include <memory>
#include <deque>
#include <ostream>

// romea
#include "romea_core_gps/nmea/NMEATalker.hpp"


namespace romea
{


struct GSVFrame
{
  struct SatelliteInfo
  {
    SatelliteInfo();
    std::optional<unsigned short> PRNNumber;
    std::optional<unsigned short> elevation;
    std::optional<unsigned short> azimut;
    std::optional<unsigned short> SNR;
  };

  using Ptr = std::shared_ptr<GSVFrame>;

  GSVFrame();

  explicit GSVFrame(const std::string & nmeaGSVSentence);

  TalkerId talkerID;
  std::optional<unsigned short> numberOfSentences;
  std::optional<unsigned short> sentenceNumber;
  std::optional<unsigned short> numberOfSatellitesInView;
  std::optional<unsigned short> signalID;
  std::deque<SatelliteInfo> satellitesInfo;
};

std::ostream & operator<<(std::ostream & os, const GSVFrame & frame);

}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__GSVFRAME_HPP_
