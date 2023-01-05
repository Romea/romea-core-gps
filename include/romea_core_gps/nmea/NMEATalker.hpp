// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_GPS__NMEA__NMEATALKER_HPP_
#define ROMEA_CORE_GPS__NMEA__NMEATALKER_HPP_

// std
#include <string>
#include <ostream>

namespace romea
{

enum class TalkerId
{
  GN = 0,
  GP,
  GL,
  GA,
  GB,
  BD,
  UNSUPPORTED
};

std::string description(const TalkerId & talkerId);

std::string acronym(const TalkerId & talkerId);

std::ostream & operator<<(std::ostream & os, const TalkerId & talkerId);

}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__NMEATALKER_HPP_
