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
#include <cmath>
#include <iostream>

// romea
#include "romea_core_common/math/EulerAngles.hpp"
#include "romea_core_gps/nmea/HDTFrame.hpp"
#include "romea_core_gps/nmea/NMEAParsing.hpp"


namespace romea
{

//-----------------------------------------------------------------------------
HDTFrame::HDTFrame(const std::string & nmeaHDTSentence)
{
  assert(NMEAParsing::isNMEASentence(nmeaHDTSentence));
  assert(nmeaHDTSentence.substr(3, 3) == "HDT");

  // split sentence in fields
  std::setlocale(LC_ALL, "C");
  std::vector<std::string> fields = NMEAParsing::splitInFields(nmeaHDTSentence);
  int checksum = std::stoi(fields.back(), 0, 16);

  // decode GPS prefix ID
  talkerId = NMEAParsing::extractTalkerId(fields.front());

  if (fields.size() < 3 || NMEAParsing::computeChecksum(nmeaHDTSentence) != checksum) {
    return;
  }

  // decode heading angle (in radian)
  if (fields[1].size()) {
    heading = std::stod(fields[1]) / 180. * M_PI;
  }

  // decode true north
  if (fields[2] == "T") {
    trueNorth = true;
  }
}

//-----------------------------------------------------------------------------
std::string HDTFrame::toNMEA() const
{
  std::stringstream ss;
  ss << "$" << NMEAParsing::talkerIdToString(talkerId) << "HDT,";

  if (heading) {
    ss << std::fixed << std::setprecision(3) << between0And2Pi(*heading) / M_PI * 180.;
  }

  ss << ',';

  if (trueNorth && *trueNorth) {
    ss << 'T';
  }

  ss.seekp(0, std::ios::end);
  int checksum = NMEAParsing::computeChecksum(ss.str(), 1, ss.tellp());
  ss << "*" << std::hex << std::setfill('0') << std::setw(2) << checksum;

  return ss.str();
}

//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const HDTFrame & frame)
{
  {
    os << "HDT frame " << std::endl;
    os << "  GPS system: " << description(frame.talkerId) << std::endl;

    os << "  heading: ";
    if (frame.heading) {os << *frame.heading / M_PI * 180.;}
    os << std::endl;

    os << "  true north: ";
    if (frame.trueNorth) {os << *frame.trueNorth;}
    os << std::endl;

    return os;
  }
}

//-----------------------------------------------------------------------------
double headingToCourseAngle(double heading)
{
  return M_PI_2 - heading;
}

}  // namespace romea
