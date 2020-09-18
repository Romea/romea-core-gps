#include "romea_gps/nmea/NMEATalker.hpp"

namespace romea {

//-----------------------------------------------------------------------------
std::string description(const TalkerId & talkerId)
{
  switch(talkerId){
    case TalkerId::GN :
      return "Global Navigation Satellite Systems";
      break;
    case TalkerId::GP :
      return "American Navstar Global Position System";
      break;
    case TalkerId::GL :
      return "Russian Glonass Global Position System";
      break;
    case TalkerId::GA :
      return "European Galileo Global Position System";
      break;
    case TalkerId::GB :
    case TalkerId::BD :
      return " Beidou Global Position System ";
      break;
    default:
      return "Unknown Global Position System";
  }
}

//-----------------------------------------------------------------------------
std::string acronym(const TalkerId & talkerId)
{
    switch(talkerId)
    {
    case TalkerId::GN :
      return "GNSS";
      break;
    case TalkerId::GA :
      return "GALILEO";
      break;
    case TalkerId::GP :
      return "NAVSTAR";
      break;
    case TalkerId::GL :
      return "GLONASS";
      break;
    case TalkerId::BD :
    case TalkerId::GB :
      return "BEIDOU";
      break;
    default:
      return "Unknown";
      break;
    }
}

//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream & os, const TalkerId & talkerId)
{
  os<<acronym(talkerId);
  return os;
}


}
