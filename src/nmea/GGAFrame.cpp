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


// std
#include <vector>
#include <string>
#include <iostream>
#include <optional>

// romea
#include "romea_core_gps/nmea/GGAFrame.hpp"
#include "romea_core_gps/nmea/NMEAParsing.hpp"

namespace romea
{
namespace core
{

//--------------------------------------------------------------------------
GGAFrame::GGAFrame()
: talkerId(TalkerId::UNSUPPORTED),
  fixTime(),
  latitude(),
  longitude(),
  fixQuality(),
  numberSatellitesUsedToComputeFix(),
  horizontalDilutionOfPrecision(),
  altitudeAboveGeoid(),
  geoidHeight(),
  dgpsCorrectionAgeInSecond(),
  dgpsStationIdNumber()
{
}

//--------------------------------------------------------------------------
GGAFrame::GGAFrame(const std::string & nmeaGGASentence)
{
  assert(NMEAParsing::isNMEASentence(nmeaGGASentence));
  assert(nmeaGGASentence.substr(3, 3) == "GGA");

  // Split sentence in fields
  std::setlocale(LC_ALL, "C");
  std::vector<std::string> fields = NMEAParsing::splitInFields(nmeaGGASentence);

  // Decode GPS prefix ID
  talkerId = NMEAParsing::extractTalkerId(fields[0]);

  // Decode sentence
  // TODO(jean) c++ 20  nmeaGGASentence.start_with("GGA")
  if (fields.size() == 16 &&
    nmeaGGASentence.substr(3, 3) == "GGA" &&
    NMEAParsing::computeChecksum(nmeaGGASentence) == std::stoi(fields.back(), 0, 16))
  {
    // decode fix date
    if (!fields[1].empty()) {
      fixTime = NMEAParsing::stringToFixTime(fields[1]);
    }

    // decode latitude
    if (!fields[2].empty() && !fields[3].empty()) {
      latitude = NMEAParsing::stringToLatitude(fields[2], fields[3]);
    }

    // decode longitude
    if (!fields[4].empty() && !fields[5].empty()) {
      longitude = NMEAParsing::stringToLongitude(fields[4], fields[5]);
    }

    // Decode fix quality
    if (!fields[6].empty()) {
      fixQuality = static_cast<FixQuality>(std::stoi(fields[6]));
    }

    // Decode number of tracked satellites
    if (!fields[7].empty()) {
      numberSatellitesUsedToComputeFix = std::stoi(fields[7]);
    }

    // Decode horizontal dilution of precision
    if (!fields[8].empty()) {
      horizontalDilutionOfPrecision = std::stod(fields[8]);
    }

    // Decode altitude above geoid
    if (!fields[9].empty() && fields[10] == "M") {
      altitudeAboveGeoid = std::stod(fields[9]);
    }

    // Dedoce height of geoid above WGS84 ellipsoid
    if (!fields[11].empty() && fields[12] == "M") {
      geoidHeight = std::stod(fields[11]);
    }

    // Decode age of the dgps correction
    if (!fields[13].empty()) {
      dgpsCorrectionAgeInSecond = std::stod(fields[13]);
    }

    // Decode dgps station id number
    if (!fields[14].empty()) {
      dgpsStationIdNumber = std::stoi(fields[14]);
    }
  }
}

//-----------------------------------------------------------------------------
std::string GGAFrame::toNMEA() const
{
  std::stringstream ss;

  // encode prefix
  ss << "$" << NMEAParsing::talkerIdToString(talkerId) << "GGA" << ",";

  // encode fixtime
  if (fixTime) {
    ss << NMEAParsing::fixTimeToString(*fixTime);
  }
  ss << ",";


  // encode latitude
  if (latitude) {
    ss << NMEAParsing::latitudeToString(*latitude);
  } else {
    ss << ",";
  }
  ss << ",";


  // encode longitude
  if (longitude) {
    ss << NMEAParsing::longitudeToString(*longitude);
  } else {
    ss << ",";
  }
  ss << ",";

  // Encode fix quality
  if (fixQuality) {
    ss << int(*fixQuality);
  }
  ss << ",";

  // Encode number of tracked satellites
  if (numberSatellitesUsedToComputeFix) {
    ss << std::setfill('0') << std::setw(2) << *numberSatellitesUsedToComputeFix;
  }
  ss << ",";

  // Encode horizontal dilution of precision
  if (horizontalDilutionOfPrecision) {
    ss << *horizontalDilutionOfPrecision;
  }
  ss << std::fixed << std::setprecision(2) << ",";

  // Decode altitude above geoid
  if (altitudeAboveGeoid) {
    ss << std::fixed << std::setprecision(1) << *altitudeAboveGeoid;
  }
  ss << ",M,";

  // Encode height of geoid above WGS84 ellipsoid
  if (geoidHeight) {
    ss << std::fixed << std::setprecision(1) << *geoidHeight;
  }
  ss << ",M,";

  // Decode age of the dgps correction
  if (dgpsCorrectionAgeInSecond) {
    ss << *dgpsCorrectionAgeInSecond;
  }
  ss << ",";

  // Decode dgps station id number
  if (dgpsStationIdNumber) {
    ss << *dgpsStationIdNumber;
  }

  ss.seekp(0, std::ios::end);
  int checksum = NMEAParsing::computeChecksum(ss.str(), 1, ss.tellp());
  ss << "*" << std::hex << std::setfill('0') << std::setw(2) << checksum;

  return ss.str();
}

//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const GGAFrame & frame)
{
  os << "GGA frame " << std::endl;

  os << "GPS system = " << description(frame.talkerId) << std::endl;

  os << "fixTime : ";
  if (frame.fixTime) {
    os << *frame.fixTime;
  }
  os << std::endl;

  os << "latitude  : ";
  if (frame.latitude) {
    os << *frame.latitude;   // *180/PI;
  }
  os << std::endl;

  os << "longitude  : ";
  if (frame.longitude) {
    os << *frame.longitude;   // *180/PI;
  }
  os << std::endl;

  os << "fix quality  : ";
  if (frame.fixQuality) {
    os << static_cast<int>(*frame.fixQuality);
  }
  os << std::endl;

  os << "number of tracked satellites  : ";
  if (frame.numberSatellitesUsedToComputeFix) {
    os << *frame.numberSatellitesUsedToComputeFix;
  }
  os << std::endl;

  os << "horizontal dilution of precision :  ";
  if (frame.horizontalDilutionOfPrecision) {
    os << *frame.horizontalDilutionOfPrecision;
  }
  os << std::endl;

  os << "altitude above geoid  : ";
  if (frame.altitudeAboveGeoid) {
    os << *frame.altitudeAboveGeoid;
  }
  os << std::endl;

  os << "height of the geoid : ";
  if (frame.geoidHeight) {
    os << *frame.geoidHeight;
  }
  os << std::endl;

  os << "dgps correction age in seconds  : ";
  if (frame.dgpsCorrectionAgeInSecond) {
    os << *frame.dgpsCorrectionAgeInSecond;
  }
  os << std::endl;

  os << "dgps station id number  : ";
  if (frame.dgpsStationIdNumber) {
    os << *frame.dgpsStationIdNumber;
  }
  os << std::endl;

  return os;
}

}  // namespace core
}  // namespace romea
