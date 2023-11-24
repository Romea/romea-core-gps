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
#include <string>

// romea
#include "romea_core_gps/nmea/NMEATalker.hpp"

namespace romea
{
namespace core
{

//-----------------------------------------------------------------------------
std::string description(const TalkerId & talkerId)
{
  switch (talkerId) {
    case TalkerId::GN:
      return "Global Navigation Satellite Systems";
      break;
    case TalkerId::GP:
      return "American Navstar Global Position System";
      break;
    case TalkerId::GL:
      return "Russian Glonass Global Position System";
      break;
    case TalkerId::GA:
      return "European Galileo Global Position System";
      break;
    case TalkerId::GB:
    case TalkerId::BD:
      return " Beidou Global Position System ";
      break;
    default:
      return "Unknown Global Position System";
  }
}

//-----------------------------------------------------------------------------
std::string acronym(const TalkerId & talkerId)
{
  switch (talkerId) {
    case TalkerId::GN:
      return "GNSS";
      break;
    case TalkerId::GA:
      return "GALILEO";
      break;
    case TalkerId::GP:
      return "NAVSTAR";
      break;
    case TalkerId::GL:
      return "GLONASS";
      break;
    case TalkerId::BD:
    case TalkerId::GB:
      return "BEIDOU";
      break;
    default:
      return "Unknown";
      break;
  }
}

//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const TalkerId & talkerId)
{
  os << acronym(talkerId);
  return os;
}

}  // namespace core
}  // namespace romea
