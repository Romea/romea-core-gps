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


#ifndef ROMEA_CORE_GPS__NMEA__NMEAPARSING_HPP_
#define ROMEA_CORE_GPS__NMEA__NMEAPARSING_HPP_

// std
#include <vector>
#include <string>

// romea
#include "romea_core_common/time/Time.hpp"
#include "romea_core_gps/nmea/NMEAFixTime.hpp"
#include "romea_core_gps/nmea/NMEAFixDate.hpp"
#include "romea_core_gps/nmea/NMEATalker.hpp"
#include "romea_core_gps/nmea/NMEALatitude.hpp"
#include "romea_core_gps/nmea/NMEALongitude.hpp"

namespace romea
{

class NMEAParsing
{
public:
  enum class SentenceID
  {
    GGA = 0,
    GSV,
    HDT,
    RMC,
    UNSUPPORTED,
    EMPTY
  };

  static void removeCRLF(std::string & sentence);

  static bool isNMEASentence(const std::string & sentence);

  static int computeChecksum(const std::string & sentence);

  static int computeChecksum(
    const std::string & sentence,
    const size_t & firstCharacterPosition,
    const size_t & lastCharacterPosition);

  static std::vector<std::string> splitInFields(const std::string & sentence);

  static TalkerId extractTalkerId(const std::string & sentence);

  static std::string talkerIdToString(const TalkerId & talkerId);

  static SentenceID extractSentenceId(const std::string & sentence);

  static std::string sentenceIdToString(const SentenceID & sentenceId);

  static FixTime stringToFixTime(const std::string & stringFixTime);

  static std::string fixTimeToString(const FixTime & fixTime);

  static FixDate stringToFixDate(const std::string & stringFixDate);

  static std::string fixDateToString(const FixDate & fixDate);

  static Latitude stringToLatitude(
    const std::string & stringAngle,
    const std::string & stringCardinalDirection);

  static std::string latitudeToString(const Latitude & latitude);

  static Longitude stringToLongitude(
    const std::string & stringAngle,
    const std::string & stringCardinalDirection);

  static std::string longitudeToString(const Longitude & longitude);

  static FixTime timePointToFixTime(const TimePoint & timepoint);

  static FixDate timePointToFixDate(const TimePoint & timepoint);
};

}  // namespace romea

#endif  // ROMEA_CORE_GPS__NMEA__NMEAPARSING_HPP_
