#ifndef romea_GSVFrame_hpp
#define romea_GSVFrame_hpp

//romea
#include "NMEATalker.hpp"

//std
#include <optional>
#include <string>
#include <memory>
#include <deque>
#include <ostream>

namespace romea {


struct GSVFrame
{
  struct SatelliteInfo {
    SatelliteInfo();
    std::optional<unsigned short> PRNNumber;
    std::optional<unsigned short> elevation;
    std::optional<unsigned short> azimut;
    std::optional<unsigned short> SNR;
  };


  using Ptr =std::shared_ptr<GSVFrame> ;

  GSVFrame();

  GSVFrame(const std::string & nmeaGSVSentence);

  TalkerId talkerID;
  std::optional<unsigned short> numberOfSentences;
  std::optional<unsigned short> sentenceNumber;
  std::optional<unsigned short> numberOfSatellitesInView;
  std::optional<unsigned short> signalID;
  std::deque<SatelliteInfo> satellitesInfo;

};

std::ostream& operator<<(std::ostream & os, const GSVFrame & frame);

}

#endif
