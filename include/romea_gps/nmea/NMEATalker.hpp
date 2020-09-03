#ifndef romea_NMEATalker_hpp
#define romea_NMEATalker_hpp

//std
#include <string>

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
}

#endif
