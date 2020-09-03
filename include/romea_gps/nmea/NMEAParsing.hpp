#ifndef romea_NMEAParsing_hpp
#define romea_NMEAParsing_hpp

//romea
#include "romea_common/time/Time.hpp"
#include "NMEAFixTime.hpp"
#include "NMEAFixDate.hpp"
#include "NMEATalker.hpp"
#include "NMEALatitude.hpp"
#include "NMEALongitude.hpp"

//std
#include <vector>
#include <string>


namespace romea {

class NMEAParsing {

public :

  enum class SentenceID{
    GGA=0,
    GSV,
    RMC,
    UNSUPPORTED,
    EMPTY
  };

  static void removeCRLF(std::string & sentence);

  static bool isNMEASentence(const std::string & sentence);

  static int computeChecksum(const std::string & sentence);

  static int computeChecksum(const std::string & sentence,
                             const size_t & firstCharacterPosition,
                             const size_t & lastCharacterPosition);

  static std::vector<std::string> splitInFields(const std::string & sentence);

  static TalkerId extractTalkerId( const std::string & sentence);

  static std::string talkerIdToString(const TalkerId & talkerId);

  static SentenceID extractSentenceId(const std::string & sentence);

  static std::string sentenceIdToString(const SentenceID & sentenceId);

  static FixTime stringToFixTime(const std::string & stringFixTime);

  static std::string fixTimeToString(const FixTime & fixTime);

  static FixDate stringToFixDate(const std::string & stringFixDate);

  static std::string fixDateToString(const FixDate & fixDate);


  static Latitude stringToLatitude(const std::string & stringAngle,
                                   const std::string & stringCardinalDirection);

  static std::string latitudeToString(const Latitude & latitude);

  static Longitude stringToLongitude(const std::string & stringAngle,
                                     const std::string & stringCardinalDirection);

  static std::string longitudeToString(const Longitude & longitude);

  static FixTime timePointToFixTime(const TimePoint &timepoint);

  static FixDate timePointToFixDate(const TimePoint & timepoint);


};


}
#endif
