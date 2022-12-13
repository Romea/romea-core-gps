//romea
#include "romea_core_gps/nmea/NMEAParsing.hpp"

//std
#include <algorithm>
#include <chrono>
#include <regex>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <regex>

namespace {

const std::string PREFIX = "$G";
const std::string COMMA =",";
const std::string WILDCARD ="*";

const size_t MINIMAL_NUMBER_OF_CHARACTERS_IN_SENTENCE =10;
const size_t CHECKSUM_BEGIN_POSITION = 1;
const size_t CHECKSUM_LENGTH_INCLUDING_WILDCARD = 3;

const std::vector<std::string> SENTENCE_IDS ={"GGA","GSV","RMC"};

}

namespace romea {

//-----------------------------------------------------------------------------
void NMEAParsing::removeCRLF(std::string & sentence)
{
  sentence.erase( std::remove(std::begin(sentence),std::end(sentence), '\r'), std::end(sentence) );
  sentence.erase( std::remove(std::begin(sentence), std::end(sentence), '\n'), std::end(sentence) );
}

//-----------------------------------------------------------------------------
bool NMEAParsing::isNMEASentence(const std::string &sentence)
{
  return sentence.size()>=MINIMAL_NUMBER_OF_CHARACTERS_IN_SENTENCE &&
      sentence.substr(0,2).compare(PREFIX) == 0 &&
      sentence[sentence.length()-CHECKSUM_LENGTH_INCLUDING_WILDCARD]=='*';
}


//-----------------------------------------------------------------------------
TalkerId NMEAParsing::extractTalkerId(const std::string & sentence )
{
  {
    size_t found=sentence.find("$GP");
    if (found!=std::string::npos)
      return TalkerId::GP;
  }

  {
    size_t found=sentence.find("$GL");
    if (found!=std::string::npos)
      return TalkerId::GL;
  }

  {
    size_t found=sentence.find("$GA");
    if (found!=std::string::npos)
      return TalkerId::GA;
  }

  {
    size_t found=sentence.find("$GB");
    if (found!=std::string::npos)
      return TalkerId::GB;
  }

  {
    size_t found=sentence.find("$GN");
    if (found!=std::string::npos)
      return TalkerId::GN;
  }

  {
    size_t found=sentence.find("$BD");
    if (found!=std::string::npos)
      return TalkerId::BD;
  }

  return TalkerId::UNSUPPORTED;

}

//-----------------------------------------------------------------------------
std::string NMEAParsing::talkerIdToString(const TalkerId & talkerId)
{
  switch (talkerId) {
  case TalkerId::GN:
    return "GN";
    break;
  case TalkerId::GP:
    return "GP";
    break;
  case TalkerId::GA:
    return "GA";
    break;
  case TalkerId::GL:
    return "GL";
    break;
  case TalkerId::GB:
    return "GB";
    break;
  case TalkerId::BD:
    return "BD";
    break;
  default:
    return "";
    break;
  }
}

//-----------------------------------------------------------------------------
NMEAParsing::SentenceID NMEAParsing::extractSentenceId(const std::string &sentence)
{
  if(sentence.empty())
  {
    return SentenceID::EMPTY;
  }

  std::string sentenceID = sentence.substr(3,3);

  auto it = std::find_if(std::cbegin(SENTENCE_IDS), std::cend(SENTENCE_IDS),
                         [&sentenceID](const std::string &id){return sentenceID.compare(id)==0;});

  if(it==std::cend(SENTENCE_IDS))
  {
    return SentenceID::UNSUPPORTED;
  }

  return static_cast<SentenceID>(std::distance(std::cbegin(SENTENCE_IDS),it));
}

//-----------------------------------------------------------------------------
std::string NMEAParsing::sentenceIdToString(const SentenceID & sentenceId)
{
  switch (sentenceId) {
  case SentenceID::GGA:
    return "GGA";
    break;
  case SentenceID::RMC:
    return "GGA";
    break;
  case SentenceID::GSV:
    return "GGA";
    break;
  default:
    return "";
    break;
  }
}

//-----------------------------------------------------------------------------
std::vector<std::string> NMEAParsing::splitInFields(const std::string & sentence) {

  std::regex regex{R"([\,\*])"};
  std::sregex_token_iterator it{std::cbegin(sentence), std::cend(sentence), regex, -1};
  return std::vector<std::string> {it, {}};
}

//-----------------------------------------------------------------------------
int NMEAParsing::computeChecksum(const std::string & sentence,
                                 const size_t & firstCharacterPosition,
                                 const size_t & lastCharacterPosition)
{
  unsigned char checksum_value = 0;
  for(size_t n=firstCharacterPosition;n<lastCharacterPosition;n++)
  {
    checksum_value ^= sentence[n];
  }

  return checksum_value;
}

//-----------------------------------------------------------------------------
int NMEAParsing::computeChecksum(const std::string &sentence) {

  return computeChecksum(sentence,
                         CHECKSUM_BEGIN_POSITION,
                         sentence.size()-CHECKSUM_LENGTH_INCLUDING_WILDCARD);
}

//-----------------------------------------------------------------------------
FixTime NMEAParsing::stringToFixTime(const std::string & stringFixtime)
{
  int hours = std::stoi(stringFixtime.substr(0,2));
  int minutes  = std::stoi(stringFixtime.substr(2,2));
  double seconds  = std::stod(stringFixtime.substr(4,stringFixtime.size()-4));
  return FixTime(hours,minutes,seconds);
}

//-----------------------------------------------------------------------------
std::string NMEAParsing::fixTimeToString(const FixTime & fixTime)
{
  int hours = fixTime.getHours();
  int minutes  = fixTime.getMinutes();
  int seconds = fixTime.getSeconds();
  int subseconds = (fixTime.getSeconds()*1000-seconds*1000);

  std::stringstream ss;
  ss<<std::setfill('0')<<std::setw(2)<<hours;
  ss<<std::setfill('0')<<std::setw(2)<<minutes;
  ss<<std::setfill('0')<<std::setw(2)<<seconds;
  ss<<".";
  ss<<std::setfill('0')<<std::setw(3)<<subseconds;
  return ss.str();
}

//-----------------------------------------------------------------------------
FixDate NMEAParsing::stringToFixDate(const std::string & stringFixDate)
{
  int day = std::stoi(stringFixDate.substr(0,2));
  int month = std::stoi(stringFixDate.substr(2,2));
  int year  = std::stod(stringFixDate.substr(4,2));
  return FixDate(year,month,day);
}

//-----------------------------------------------------------------------------
std::string NMEAParsing::fixDateToString(const FixDate & fixDate)
{
  int years = fixDate.getYears();
  int month  = fixDate.getMonths();
  int days = fixDate.getDays();

  std::stringstream ss;
  ss<<std::setfill('0')<<std::setw(2)<<days;
  ss<<std::setfill('0')<<std::setw(2)<<month;
  ss<<std::setfill('0')<<std::setw(2)<<years;
  return ss.str();

}

//-----------------------------------------------------------------------------
Latitude NMEAParsing::stringToLatitude(const std::string & stringAngle,
                                       const std::string & stringCardinalDirection)
{
  size_t n = stringAngle.find(".");
  int degrees = std::stoi(stringAngle.substr(0,n-2));
  int minutes = std::stoi(stringAngle.substr(n-2,2));
  double seconds = std::stod(stringAngle.substr(n))*60.;
  LatitudeDirections direction = toLatitudeDirection(stringCardinalDirection);
  return Latitude(degrees,minutes,seconds,direction);
}

//-----------------------------------------------------------------------------
Longitude NMEAParsing::stringToLongitude(const std::string & stringAngle,
                                         const std::string & stringCardinalDirection)
{
  size_t n = stringAngle.find(".");
  int degrees = std::stoi(stringAngle.substr(0,n-2));
  int minutes = std::stoi(stringAngle.substr(n-2,2));
  double seconds = std::stod(stringAngle.substr(n))*60.;
  LongitudeDirections direction = toLongitudeDirection(stringCardinalDirection);
  return Longitude(degrees,minutes,seconds,direction);
}

//-----------------------------------------------------------------------------
std::string NMEAParsing::latitudeToString(const Latitude & latitude)
{
  std::stringstream ss;
  ss<<std::setfill('0')<<std::setw(2)<<latitude.getDegrees();
  ss<<std::setfill('0')<<std::setw(2)<<latitude.getMinutes();
  ss<<".";
  ss<<std::setfill('0')<<std::setw(5)<<int(latitude.getSeconds()*100000/60.);
  ss<<",";
  ss<<toString(latitude.getDirection());
  return ss.str();

}

//-----------------------------------------------------------------------------
std::string NMEAParsing::longitudeToString(const Longitude & longitude)
{
  std::stringstream ss;
  ss<<std::setfill('0')<<std::setw(3)<<longitude.getDegrees();
  ss<<std::setfill('0')<<std::setw(2)<<longitude.getMinutes();
  ss<<".";
  ss<<std::setfill('0')<<std::setw(5)<<int(longitude.getSeconds()*100000/60.);
  ss<<",";
  ss<<toString(longitude.getDirection());
  return ss.str();
}


//-----------------------------------------------------------------------------
FixTime NMEAParsing::timePointToFixTime(const TimePoint & timepoint)
{
  std::time_t tt = std::chrono::system_clock::to_time_t(timepoint);
  double nsec = durationToNanoSecond(timepoint.time_since_epoch())%1000000000;
  double sec = nsec/1000000000.;

  struct std::tm tm = *std::gmtime ( &tt );
  return FixTime(tm.tm_hour,tm.tm_min,sec);
}

//-----------------------------------------------------------------------------
FixDate NMEAParsing::timePointToFixDate(const TimePoint &timepoint)
{
  std::time_t tt = std::chrono::system_clock::to_time_t(timepoint);
  struct std::tm tm = *std::gmtime ( &tt );
  return FixDate(tm.tm_year%100,tm.tm_mon+1,tm.tm_mday);

}

}
