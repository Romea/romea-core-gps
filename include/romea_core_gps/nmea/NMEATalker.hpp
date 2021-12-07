#ifndef romea_NMEATalker_hpp
#define romea_NMEATalker_hpp

//std
#include <string>
#include <ostream>

namespace romea {

enum class TalkerId{
  GN=0,
  GP,
  GL,
  GA,
  GB,
  BD,
  UNSUPPORTED
};


std::string description(const TalkerId & talkerId);

std::string acronym(const TalkerId & talkerId);

std::ostream& operator<<(std::ostream & os, const TalkerId & talkerId);

}

#endif
